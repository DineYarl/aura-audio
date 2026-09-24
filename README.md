<div align="center">

# 💎 Aura Audio Player

**Bit-Perfect Audiophile Precision Meets Modern Minimalist Glass Aesthetics**

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-informational.svg)](https://github.com)
[![Built with Qt 6](https://img.shields.io/badge/Framework-Qt%206.x-green.svg)](https://www.qt.io/)
[![Language](https://img.shields.io/badge/C%2B%2B-20-orange.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![Audio](https://img.shields.io/badge/Audio-Bit--Perfect%20Direct%20DAC-red.svg)](https://en.wikipedia.org/wiki/Direct_Stream_Digital)

<br/>

*Aura Audio* is a lightweight, cross-platform music player and collection organizer designed for audiophiles who refuse to compromise between **lossless sound fidelity** and **contemporary visual design**.

Built upon the rock-solid C++ engine of Strawberry, *Aura* replaces legacy skeuomorphism with a fluid, frosted-glass design system, dynamic album-adaptive ambient lighting, real-time hi-res resolution badges, and smooth typography.

---

</div>

## ✨ Key Highlights

### 🎨 Modern Minimalist Glass Design
* **Floating Island Playback Deck**: A floating glass player bar with smooth rounded corners, translucent backdrop, and glowing micro-interactions.
* **Elimination of Vintage Skeuomorphism**: No more 2000s beveled lines, hard divider shadows, or clunky gradients.
* **Rounded Artwork Display**: Album covers rendered with smooth antialiased rounded borders (`12px` large, `8px` compact).
* **Capsule Navigation**: Clean pill indicators for Library, Files, Radios, and Playlists.
* **Minimalist Controls**: Ultra-slim 4px rounded scrubbers, glowing handles, and custom scrollbars.

### 🌈 Dynamic Adaptive Ambient Glow
* Built-in C++ color extraction engine (`ImageUtils::ExtractDominantColor`) samples the primary vibrant tones of your currently playing album artwork.
* Casts a soft, radiant ambient gradient behind the floating playback bar in real time.
* 0% extra CPU footprint during playback; resets cleanly when playback stops.

### ⚡ Bit-Perfect Audiophile Engine
* **Direct Hardware DAC Passthrough**: Bypasses OS software resampling (ALSA `hw:X,Y` on Linux, WASAPI Exclusive / ASIO on Windows, CoreAudio on macOS).
* **Format Support**: Native playback for DSD (DSF/DSDIFF via DoP or direct), FLAC, ALAC, WAV, AIFF, WavPack, APE, Opus, and MP3.
* **Zero Resampling**: Ensures 192kHz/24-bit, 384kHz/32-bit, or DSD streams reach your DAC bit-for-bit bit-accurately.

### 🏷️ Real-Time Audiophile Resolution Badges
* Live playback resolution detector displaying dedicated pill badges on the playback deck:
  - `✨ DSD DIRECT • 5.6 MHz`
  - `✨ HI-RES • 24-BIT / 96 kHz FLAC`
  - `LOSSLESS • 16-BIT / 44.1 kHz FLAC`
  - `MP3 • 320 kbps`
* Dynamic styling: radiant amber/gold pill for Hi-Res & DSD, icy blue for CD Lossless.

### 🗄️ Relational SQLite Library Engine
* Effortlessly index, search, and group libraries with **100,000+ lossless tracks** in milliseconds.
* Hierarchical multi-tag sorting (Artist → Year → Album → Disc → Track).
* Smart playlists, dynamic queues, tag editing (TagLib), and ReplayGain normalization.

### 🎤 Centered Synchronized Lyrics View
* Clean centered layout with generous line spacing (`line-height: 1.8`).
* Instant lyrics fetching with synchronized LRC support via LRCLIB, Genius, and Musixmatch.

### 🪶 Ultra-Lightweight Native C++ Footprint
* Built natively with **C++ and Qt 6**.
* Typically consumes just **~70MB–120MB of RAM** (compared to 600MB–1GB+ in Electron/web-based music players) with virtually **0% idle CPU**.

---

## 📸 Comparison at a Glance

| Feature | Aura Audio Player | Typical Electron Players (Spotify, Tidal app) | Legacy Audiophile Players (Strawberry stock, Foobar) |
| :--- | :---: | :---: | :---: |
| **Bit-Perfect DAC Output** | ✅ **Yes (Hardware Direct)** | ❌ No (OS Resampled) | ✅ Yes |
| **Modern Minimalist UI** | ✅ **Yes (Glassmorphic)** | ✅ Yes | ❌ No (Dated 2000s look) |
| **Adaptive Ambient Lighting** | ✅ **Yes** | ❌ No | ❌ No |
| **Hi-Res Resolution Badges** | ✅ **Yes (Real-time)** | ⚠️ Limited | ❌ No |
| **RAM Consumption** | 🟢 **~70MB – 120MB** | 🔴 600MB – 1.2GB | 🟢 ~80MB |
| **100k+ Track Library Support** | ✅ **Instant (SQLite)** | ❌ Slow / Cloud dependent | ✅ Instant |
| **Multi-Platform (Win/Mac/Linux)**| ✅ **100% Free & Open** | ⚠️ Closed-source | ⚠️ Windows/Mac builds paywalled |

---

## 🛠️ Building from Source

### 1. Install Dependencies (Ubuntu / Debian)
```bash
sudo apt update && sudo apt install -y \
  git make cmake gcc g++ ninja-build \
  qt6-base-dev qt6-base-dev-tools qt6-tools-dev qt6-tools-dev-tools qt6-base-private-dev \
  libglib2.0-dev libdbus-1-dev libboost-dev libsqlite3-dev libgnutls28-dev libicu-dev \
  libasound2-dev libpulse-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
  libtag1-dev libchromaprint-dev libfftw3-dev libebur128-dev
```

### 2. Clone the Repository
```bash
git clone https://github.com/<your-username>/aura-audio.git
cd aura-audio
```

### 3. Build with CMake & Ninja
```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### 4. Run Aura
```bash
./build/src/strawberry
```

---

## 🤝 Acknowledgments & Heritage

*Aura Audio* is free and open-source software licensed under the **GNU General Public License v3.0 (GPLv3)**.

We proudly build upon the foundation created by:
* **Jonas Kvinge & the Strawberry Music Player contributors**: For the exceptional audiophile audio engine and TagLib collection architecture.
* **The Clementine and Amarok teams**: For the pioneering open-source Qt music player ecosystem.
* **The Tauon Music Box project (Taiko2k)**: For inspiring the clean, minimalist, album-centric design philosophy.

---

## 📜 License

Distributed under the **GNU General Public License v3.0**. See [COPYING](COPYING) for complete license terms.
