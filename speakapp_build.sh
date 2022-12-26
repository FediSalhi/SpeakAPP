#!/bin/bash
echo "[SpeakAPP Build Script] Updating the system..."
sudo add-apt-repository ppa:beineri/opt-qt-5.12.8-xenial
sudo apt update

echo "[SpeakAPP Build Script] System updated."
echo "[SpeakAPP Build Script] Installing Qt5"
sudo sudo apt install qt512-meta-full

sudo mkdir /etc/xdg/qtchooser

if [ -f "/etc/xdg/qtchooser/default.conf" ]; then
sudo rm /etc/xdg/qtchooser/default.conf
fi

sudo touch /etc/xdg/qtchooser/default.conf

echo "/opt/qt512/bin" >> /etc/xdg/qtchooser/default.conf
echo "/opt/qt511/lib" >> /etc/xdg/qtchooser/default.conf

echo "[SpeakAPP Build Script] Qt5 installed"

BUILD_DIR=build

cd ..

if [ -d "$BUILD_DIR" ]; then
echo "[SpeakAPP Build Script] Build directory already exists!"
else
mkdir build
echo "[SpeakAPP Build Script] Build directory created"
fi

cd $BUILD_DIR
qmake ../SpeakAPP
make

#echo "[SpeakAPP Build Script] Building SpeakAPP... Please wait"
#/usr/lib/qt5/bin/qmake ../SpeakAPP/SpeakAPP.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
#/usr/bin/make qmake_all
#/usr/bin/make

echo "[SpeakAPP Build Script] SpeakAPP built successfully"
