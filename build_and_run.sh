#!/bin/bash
# ==============================================================
# Aura Audio Player - Local Build & Run Script
# ==============================================================

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "=========================================================="
echo "           💎 AURA AUDIO PLAYER BUILD & RUN               "
echo "=========================================================="

# Check if build directory exists, otherwise configure
if [ ! -f "$SCRIPT_DIR/build/build.ninja" ] && [ ! -f "$SCRIPT_DIR/build/Makefile" ]; then
    echo "[+] Configuring CMake..."
    cmake -B build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_WITH_QT6=ON \
        -DUSE_TAGLIB=ON
fi

echo "[+] Compiling Aura Audio..."
cmake --build build -j$(nproc)

echo "[+] Compilation successful! Launching Aura Audio..."
./build/src/strawberry "$@" &
disown
echo "[+] Aura Audio Player is now running."
