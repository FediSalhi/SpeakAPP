#!/bin/bash
echo "[SpeakAPP Build Script] Updating the system..."
sudo apt-get update
echo "[SpeakAPP Build Script] System updated."
echo "[SpeakAPP Build Script] Installing Qt5"
sudo apt-get install qt5-qmake
echo "[SpeakAPP Build Script] Qt5 installed"

BUILD_DIR=../Build-SpeakAPP-Desktop-Debug

if [ -d "$BUILD_DIR" ]; then
echo "[SpeakAPP Build Script] Build directory already exists!"
else
mkdir ../Build-SpeakAPP-Desktop-Debug
echo "[SpeakAPP Build Script] Build directory created"
fi

cd $BUILD_DIR

echo "[SpeakAPP Build Script] Building SpeakAPP... Please wait"
/usr/lib/qt5/bin/qmake ../SpeakAPP/SpeakAPP.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
/usr/bin/make qmake_all
/usr/bin/make

echo "[SpeakAPP Build Script] SpeakAPP built successfully"
