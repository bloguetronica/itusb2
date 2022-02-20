#!/bin/sh

echo Obtaining required packages...
apt-get -qq update
apt-get -qq install build-essential
apt-get -qq install libusb-1.0-0-dev
echo Copying source code files...
mkdir -p /usr/local/src/itusb2
cp -f src/cp2130.cpp /usr/local/src/itusb2/.
cp -f src/cp2130.h /usr/local/src/itusb2/.
cp -f src/error.cpp /usr/local/src/itusb2/.
cp -f src/error.h /usr/local/src/itusb2/.
cp -f src/GPL.txt /usr/local/src/itusb2/.
cp -f src/itusb2-attach.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-detach.cpp /usr/local/src/itusb2/.
cp -f src/itusb2device.cpp /usr/local/src/itusb2/.
cp -f src/itusb2device.h /usr/local/src/itusb2/.
cp -f src/itusb2-enum.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-info.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-list.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-lockotp.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-reset.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-status.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-udoff.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-udon.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-upoff.cpp /usr/local/src/itusb2/.
cp -f src/itusb2-upon.cpp /usr/local/src/itusb2/.
cp -f src/LGPL.txt /usr/local/src/itusb2/.
cp -f src/libusb-extra.c /usr/local/src/itusb2/.
cp -f src/libusb-extra.h /usr/local/src/itusb2/.
cp -f src/Makefile /usr/local/src/itusb2/.
cp -f src/README.txt /usr/local/src/itusb2/.
echo Building and installing binaries...
make -C /usr/local/src/itusb2 all install clean
echo Installing man pages...
mkdir -p /usr/local/share/man/man1
cp -f man/itusb2-attach.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-detach.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-enum.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-info.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-list.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-lockotp.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-reset.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-status.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-udoff.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-udon.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-upoff.1.gz /usr/local/share/man/man1/.
cp -f man/itusb2-upon.1.gz /usr/local/share/man/man1/.
echo Applying configurations...
cat > /etc/udev/rules.d/70-bgtn-itusb2.rules << EOF
SUBSYSTEM=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="8cdf", MODE="0666"
SUBSYSTEM=="usb_device", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="8cdf", MODE="0666"
EOF
service udev restart
echo Done!
