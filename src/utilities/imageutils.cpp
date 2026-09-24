/*
 * Strawberry Music Player
 * Copyright 2019-2021, Jonas Kvinge <jonas@jkvinge.net>
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

#include <utility>

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QSize>

#include "imageutils.h"
#include "fileutils.h"
#include "mimeutils.h"

using namespace Qt::Literals::StringLiterals;

const QStringList &ImageUtils::SupportedImageMimeTypes() {

  static const QStringList supported_image_mimetypes = []() {
    const QList<QByteArray> imagereader_supported_mime_types = QImageReader::supportedMimeTypes();
    QStringList result;
    result.reserve(imagereader_supported_mime_types.count());
    for (const QByteArray &i : imagereader_supported_mime_types) {
      result << QString::fromUtf8(i);
    }
    return result;
  }();

  return supported_image_mimetypes;

}

const QStringList &ImageUtils::SupportedImageFormats() {

  static const QStringList supported_image_formats = []() {
    const QList<QByteArray> imagereader_supported_image_formats = QImageReader::supportedImageFormats();
    QStringList result;
    result.reserve(imagereader_supported_image_formats.count());
    for (const QByteArray &i : imagereader_supported_image_formats) {
      result << QString::fromUtf8(i);
    }
    return result;
  }();

  return supported_image_formats;

}

QByteArray ImageUtils::SaveImageToJpegData(const QImage &image) {

  if (image.isNull()) return QByteArray();

  QByteArray image_data;
  QBuffer buffer(&image_data);
  if (buffer.open(QIODevice::WriteOnly)) {
    image.save(&buffer, "JPEG");
    buffer.close();
  }

  return image_data;

}

QByteArray ImageUtils::FileToJpegData(const QString &filename) {

  if (filename.isEmpty()) return QByteArray();

  QByteArray image_data = Utilities::ReadDataFromFile(filename);
  if (Utilities::MimeTypeFromData(image_data) == u"image/jpeg"_s) {
    return image_data;
  }

  QImage image;
  if (image.loadFromData(image_data)) {
    if (!image.isNull()) {
      image_data = SaveImageToJpegData(image);
    }
  }

  return image_data;

}

QImage ImageUtils::ScaleImage(const QImage &image, const QSize desired_size, const qreal device_pixel_ratio, const bool pad) {

  if (image.isNull() || (image.width() == desired_size.width() && image.height() == desired_size.height())) {
    return image;
  }

  QSize scale_size(static_cast<int>(desired_size.width() * device_pixel_ratio), static_cast<int>(desired_size.height() * device_pixel_ratio));

  // Scale the image
  QImage image_scaled = image.scaled(scale_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  // Pad the image
  if (pad && image_scaled.width() != image_scaled.height()) {
    QImage image_padded(scale_size, QImage::Format_ARGB32);
    image_padded.fill(Qt::transparent);

    QPainter p(&image_padded);
    p.drawImage((image_padded.width() - image_scaled.width()) / 2, (image_padded.height() - image_scaled.height()) / 2, image_scaled);
    p.end();

    image_scaled = image_padded;
  }

  image_scaled.setDevicePixelRatio(device_pixel_ratio);

  return image_scaled;

}

QImage ImageUtils::GenerateNoCoverImage(const QSize size, const qreal device_pixel_ratio) {

  QImage image(u":/pictures/cdcase.png"_s);
  QSize scale_size(static_cast<int>(size.width() * device_pixel_ratio), static_cast<int>(size.height() * device_pixel_ratio));

  // Get a square version of the nocover image with some transparency:
  QImage image_scaled = image.scaled(scale_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  QImage image_square(scale_size, QImage::Format_ARGB32);
  image_square.fill(0);
  QPainter p(&image_square);
  p.setOpacity(0.4);
  p.drawImage((image_square.width() - image_scaled.width()) / 2, (image_square.height() - image_scaled.height()) / 2, image_scaled);
  p.end();

  image_square.setDevicePixelRatio(device_pixel_ratio);

  return image_square;

}

QColor ImageUtils::ExtractDominantColor(const QImage &image, const QColor &fallback) {

  if (image.isNull()) return fallback;

  // Scale down to a tiny 24x24 thumbnail for lightning-fast scanning (576 pixels)
  QImage thumb = image.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::FastTransformation);
  if (thumb.format() != QImage::Format_ARGB32 && thumb.format() != QImage::Format_RGB32) {
    thumb = thumb.convertToFormat(QImage::Format_ARGB32);
  }

  quint64 best_score = 0;
  QColor best_color = fallback;

  struct ColorBucket {
    quint64 r_sum = 0;
    quint64 g_sum = 0;
    quint64 b_sum = 0;
    quint32 count = 0;
    quint32 avg_sat = 0;
    quint32 avg_light = 0;
  };

  ColorBucket buckets[12];

  const int width = thumb.width();
  const int height = thumb.height();

  for (int y = 0; y < height; ++y) {
    const QRgb *scanline = reinterpret_cast<const QRgb*>(thumb.constScanLine(y));
    for (int x = 0; x < width; ++x) {
      const QRgb pixel = scanline[x];
      const int r = qRed(pixel);
      const int g = qGreen(pixel);
      const int b = qBlue(pixel);

      QColor col(r, g, b);
      int h, s, l;
      col.getHsl(&h, &s, &l);

      // Skip extreme darkness, extreme brightness, and desaturated grey
      if (l < 25 || l > 230 || s < 35 || h < 0) {
        continue;
      }

      int bucket_idx = (h % 360) / 30;
      buckets[bucket_idx].r_sum += r;
      buckets[bucket_idx].g_sum += g;
      buckets[bucket_idx].b_sum += b;
      buckets[bucket_idx].count++;
      buckets[bucket_idx].avg_sat += s;
      buckets[bucket_idx].avg_light += l;
    }
  }

  for (int i = 0; i < 12; ++i) {
    if (buckets[i].count > 0) {
      quint32 sat = buckets[i].avg_sat / buckets[i].count;
      quint64 score = static_cast<quint64>(buckets[i].count) * sat;
      if (score > best_score) {
        best_score = score;
        int r = static_cast<int>(buckets[i].r_sum / buckets[i].count);
        int g = static_cast<int>(buckets[i].g_sum / buckets[i].count);
        int b = static_cast<int>(buckets[i].b_sum / buckets[i].count);
        best_color = QColor(r, g, b);
      }
    }
  }

  return best_color;

}

