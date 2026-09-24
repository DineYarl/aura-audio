# 🎵 Modern Audiophile Player - Project Roadmap

> Combining bit-perfect audiophile fidelity with a minimalist, fluid modern design aesthetic.

---

## 🗺️ Master Roadmap

### Phase 1: Visual Design System & Glass Foundation *(COMPLETED)*
- [x] Translucent dark glass stylesheet in `data/style/strawberry.css`.
- [x] Elimination of retro beveled lines and skeuomorphic gradients.
- [x] Circular pill transport buttons with glowing hover states.
- [x] Modern 4px rounded scrubber and volume sliders.
- [x] Rounded antialiased album art clipping in `PlayingWidget`.
- [x] Capsule sidebar tabs in `FancyTabBar`.

### Phase 2: Dynamic Adaptive Ambient Glow Engine
- [ ] Implement fast palette extraction (`ImageUtils::ExtractDominantColor`).
- [ ] Ambient deck glow behind the floating playback bar (`player_controls`).
- [ ] Smooth color transition animations when tracks change.
- [ ] Appearance settings toggle for ambient glow.

### Phase 3: Modern Album Grid & Collection Views
- [ ] Modern album card tiles with rounded artwork and subtle elevation.
- [ ] Artwork hover elevation/zoom micro-interactions.
- [ ] 1-click hierarchical multi-tag sorting pills (Artist → Year → Album → Track).
- [ ] Instant-filter capsule search bar.

### Phase 4: Audiophile Hi-Res Badges & Waveform Scrubber
- [ ] Dynamic hi-res badge (e.g., `24-bit / 192 kHz FLAC`, `DSD128`, `Direct Bit-Perfect`).
- [ ] Technical pipeline details on badge hover.
- [ ] Seamless waveform seekbar integration.

### Phase 5: Minimalist Synchronized Lyrics
- [ ] Centered, uncluttered lyrics layout with generous line spacing.
- [ ] Active line highlighting with smooth opacity falloff.
- [ ] Smooth auto-scroll following track playback.

### Phase 6: Multi-Platform CI/CD & GitHub Launch
- [ ] Project name, logo, and identity.
- [ ] GitHub Actions CI for Linux (AppImage, deb), Windows (installer, zip), and macOS (dmg).
- [ ] High-impact GitHub README with screenshots, comparison tables, and quick-start guide.
- [ ] GPLv3 compliance and author attributions.
