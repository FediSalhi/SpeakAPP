#
# @file speakapp_build.sh
# @brief build script
#
# This script installs Qt 5.12.8 using PPA for Ubuntu 16.04
# and then build the program. The build output is
# the ../build directory.
# This script will be modified in the future to add other platforms.
#
# @author Fedi Salhi
# @date December 25 2022
#
#

#!/bin/bash
echo "[SpeakAPP Build Script] Adding PPA Qt repository..."
sudo add-apt-repository ppa:beineri/opt-qt-5.12.8-xenial
echo "[SpeakAPP Build Script] PPA Qt repository added"
echo "[SpeakAPP Build Script] Updating the system..."
sudo apt update
echo "[SpeakAPP Build Script] System updated."
echo "[SpeakAPP Build Script] Installing Qt5"
sudo sudo apt install qt512-meta-full

sudo mkdir /etc/xdg/qtchooser

if [ -f "/etc/xdg/qtchooser/default.conf" ]; then
sudo rm /etc/xdg/qtchooser/default.conf
fi

sudo touch /etc/xdg/qtchooser/default.conf

sudo echo "/opt/qt512/bin" >> /etc/xdg/qtchooser/default.conf
sudo echo "/opt/qt512/lib" >> /etc/xdg/qtchooser/default.conf

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

echo "[SpeakAPP Build Script] SpeakAPP built successfully. The output is in this directory "
pwd 
echo "[SpeakAPP Build Script] Run using ./SpeakAPP from the build directory"
