/*
 * Strawberry Music Player
 * Copyright 2013, 2017-2021, Jonas Kvinge <jonas@jkvinge.net>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "config.h"

#include <utility>

#include <QDir>
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QIcon>
#include <QImageReader>
#include <QSize>
#include <QSettings>

#include <QPainter>
#include <QPolygonF>
#include <QRectF>

#include "logging.h"
#include "standardpaths.h"
#include "settings.h"
#include "includes/iconmapper.h"
#include "iconloader.h"
#include "constants/appearancesettings.h"

using namespace Qt::Literals::StringLiterals;

bool IconLoader::system_icons_ = false;
bool IconLoader::custom_icons_ = false;
bool IconLoader::svg_supported_ = false;

namespace {

QIcon CreateModernTransportIcon(const QString &name) {
  QIcon icon;
  for (int s : { 22, 32, 48, 64 }) {
    QPixmap pixmap(s, s);
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(245, 248, 255));

    const qreal sz = s;
    if (name == u"media-playback-start"_s) {
      QPolygonF triangle;
      triangle << QPointF(sz * 0.32, sz * 0.22)
               << QPointF(sz * 0.78, sz * 0.50)
               << QPointF(sz * 0.32, sz * 0.78);
      p.drawPolygon(triangle);
    }
    else if (name == u"media-playback-pause"_s) {
      const qreal barW = sz * 0.16;
      const qreal barH = sz * 0.54;
      const qreal barY = sz * 0.23;
      p.drawRoundedRect(QRectF(sz * 0.28, barY, barW, barH), 2.0, 2.0);
      p.drawRoundedRect(QRectF(sz * 0.56, barY, barW, barH), 2.0, 2.0);
    }
    else if (name == u"media-playback-stop"_s) {
      const qreal b = sz * 0.44;
      const qreal xy = (sz - b) / 2.0;
      p.drawRoundedRect(QRectF(xy, xy, b, b), 2.5, 2.5);
    }
    else if (name == u"media-skip-backward"_s) {
      p.drawRoundedRect(QRectF(sz * 0.20, sz * 0.25, sz * 0.10, sz * 0.50), 1.5, 1.5);
      QPolygonF triangle;
      triangle << QPointF(sz * 0.76, sz * 0.25)
               << QPointF(sz * 0.34, sz * 0.50)
               << QPointF(sz * 0.76, sz * 0.75);
      p.drawPolygon(triangle);
    }
    else if (name == u"media-skip-forward"_s) {
      QPolygonF triangle;
      triangle << QPointF(sz * 0.24, sz * 0.25)
               << QPointF(sz * 0.66, sz * 0.50)
               << QPointF(sz * 0.24, sz * 0.75);
      p.drawPolygon(triangle);
      p.drawRoundedRect(QRectF(sz * 0.70, sz * 0.25, sz * 0.10, sz * 0.50), 1.5, 1.5);
    }
    else {
      return QIcon();
    }
    icon.addPixmap(pixmap);
  }
  return icon;
}

}  // namespace

void IconLoader::Init() {

#if !defined(Q_OS_MACOS) && !defined(Q_OS_WIN32)
  Settings s;
  s.beginGroup(AppearanceSettings::kSettingsGroup);
  system_icons_ = s.value(AppearanceSettings::kSystemThemeIcons, AppearanceSettings::kDefaultSystemIcons).toBool();
  s.endGroup();
#endif

  QDir dir;
  if (dir.exists(StandardPaths::WritableLocation(StandardPaths::StandardLocation::AppLocalDataLocation) + u"/icons"_s)) {
    custom_icons_ = true;
  }

  svg_supported_ = QImageReader::supportedImageFormats().contains("svg");

}

QIcon IconLoader::Load(const QString &name, const bool system_icon, const int fixed_size, const int min_size, const int max_size) {

  QIcon ret;

  if (name.isEmpty()) {
    qLog(Error) << "Icon name is empty!";
    return ret;
  }

  if (name.startsWith(u"media-playback-"_s) || name.startsWith(u"media-skip-"_s)) {
    QIcon modern = CreateModernTransportIcon(name);
    if (!modern.isNull()) return modern;
  }

  QList<int> sizes;
  if (fixed_size == 0) {
    sizes << 22 << 32 << 48 << 64 << 128;
  }
  else {
    sizes << fixed_size;
  }

  // Custom icons take precedence over system theme icons: a user-provided icon set is an explicit choice and should be honored everywhere, with the system theme only used as a fallback for icons the user did not provide.
  if (custom_icons_) {
    const QString custom_icons_path = StandardPaths::WritableLocation(StandardPaths::StandardLocation::AppLocalDataLocation) + u"/icons"_s;

    // A single scalable SVG in icons/scalable is preferred when SVG is supported, since QIcon can render it at any requested size.
    if (svg_supported_) {
      const QString scalable_svg_filename = custom_icons_path + u"/scalable/"_s + name + u".svg"_s;
      if (QFile::exists(scalable_svg_filename)) {
        ret.addFile(scalable_svg_filename);
        if (!ret.isNull()) return ret;
      }
    }

    const QString custom_icon_path = custom_icons_path + u"/%1x%1/%2.%3"_s;
    for (int s : std::as_const(sizes)) {
      const QString png_filename = custom_icon_path.arg(s).arg(name, u"png"_s);
      if (QFile::exists(png_filename)) {
        ret.addFile(png_filename, QSize(s, s));
        continue;
      }
      if (svg_supported_) {
        const QString svg_filename = custom_icon_path.arg(s).arg(name, u"svg"_s);
        if (QFile::exists(svg_filename)) {
          ret.addFile(svg_filename, QSize(s, s));
        }
      }
    }
    if (!ret.isNull()) return ret;
    qLog(Warning) << "Couldn't load icon" << name << "from custom icons.";
  }

  if (system_icon && system_icons_) {
    IconMapper::IconProperties icon_prop;
    if (IconMapper::iconmapper_.contains(name)) {
      icon_prop = IconMapper::iconmapper_[name];
    }
    if (min_size != 0) icon_prop.min_size = min_size;
    if (max_size != 0) icon_prop.max_size = max_size;
    if (icon_prop.allow_system_icon) {
      ret = QIcon::fromTheme(name);
      if (ret.isNull()) {
        const QStringList alt_names = icon_prop.names;
        for (const QString &alt_name : alt_names) {
          ret = QIcon::fromTheme(alt_name);
          if (!ret.isNull()) break;
        }
        if (ret.isNull()) {
          qLog(Warning) << "Couldn't load icon" << name << "from system theme icons.";
        }
      }
      if (!ret.isNull()) {
        if (fixed_size != 0 && !ret.availableSizes().contains(QSize(fixed_size, fixed_size))) {
          qLog(Warning) << "Can't use system icon for" << name << "icon does not have fixed size." << fixed_size;
          ret = QIcon();
        }
        else {
          int size_smallest = 0;
          int size_largest = 0;
          const QList<QSize> available_sizes = ret.availableSizes();
          for (const QSize &s : available_sizes) {
            if (s.width() != s.height()) {
              qLog(Warning) << "Can't use system icon for" << name << "icon is not proportional.";
              ret = QIcon();
            }
            if (size_smallest == 0 || s.width() < size_smallest) size_smallest = s.width();
            if (s.width() > size_largest) size_largest = s.width();
          }
          if (size_smallest != 0 && icon_prop.min_size != 0 && size_smallest < icon_prop.min_size) {
            qLog(Warning) << "Can't use system icon for" << name << "icon too small." << size_smallest;
            ret = QIcon();
          }
          else if (size_largest != 0 && icon_prop.max_size != 0 && size_largest > icon_prop.max_size) {
            qLog(Warning) << "Can't use system icon for" << name << "icon too large." << size_largest;
            ret = QIcon();
          }
        }
      }
    }
    if (!ret.isNull()) return ret;
  }

  const QString path(u":/icons/%1x%2/%3.png"_s);
  for (int s : std::as_const(sizes)) {
    QString filename(path.arg(s).arg(s).arg(name));
    if (QFile::exists(filename)) ret.addFile(filename, QSize(s, s));
  }

  if (ret.isNull() && !system_icons_ && !custom_icons_) {
    qLog(Error) << "Couldn't load icon" << name;
  }

  return ret;

}
