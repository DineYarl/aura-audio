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

### Phase 2: Dynamic Adaptive Ambient Glow Engine *(COMPLETED)*
- [x] Implement fast palette extraction (`ImageUtils::ExtractDominantColor`).
- [x] Ambient deck glow behind the floating playback bar (`player_controls`).
- [x] Seamless color transitions and clean reset on stop.

### Phase 3: Modern Album Grid & Collection Views *(COMPLETED)*
- [x] Modern CollectionView layout with smooth padding and capsule selections.
- [x] Clean CollectionFilterWidget with translucent backdrop and capsule search.

### Phase 4: Audiophile Hi-Res Badges & Resolution Scrubber *(COMPLETED)*
- [x] Dynamic hi-res badge (e.g., `✨ DSD DIRECT`, `✨ HI-RES • 24-BIT / 96 kHz FLAC`, `LOSSLESS • 16-BIT / 44.1 kHz`).
- [x] Real-time codec & bit-depth detection engine.
- [x] Audiophile glowing pill styling in design system.

### Phase 5: Minimalist Synchronized Lyrics *(COMPLETED)*
- [x] Centered, uncluttered lyrics layout with generous line spacing.
- [x] Clean modern typography and high-contrast translucent styling.

### Phase 6: Multi-Platform CI/CD & GitHub Launch *(NEXT UP)*
- [ ] Project name, logo, and identity.
- [ ] GitHub Actions CI for Linux (AppImage, deb), Windows (installer, zip), and macOS (dmg).
- [ ] High-impact GitHub README with screenshots, comparison tables, and quick-start guide.
- [ ] GPLv3 compliance and author attributions.
