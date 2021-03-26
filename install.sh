#!/bin/sh

echo Obtaining required packages...
apt-get -qq update
apt-get -qq install build-essential
apt-get -qq install libusb-1.0-0-dev
echo Copying source code files...
mkdir -p /usr/local/src/itusb2
cp -f src/itusb2-attach.c /usr/local/src/itusb2/.
cp -f src/itusb2-core.c /usr/local/src/itusb2/.
cp -f src/itusb2-core.h /usr/local/src/itusb2/.
cp -f src/itusb2-detach.c /usr/local/src/itusb2/.
cp -f src/itusb2-enum.c /usr/local/src/itusb2/.
cp -f src/itusb2-list.c /usr/local/src/itusb2/.
cp -f src/itusb2-lockotp.c /usr/local/src/itusb2/.
cp -f src/itusb2-reset.c /usr/local/src/itusb2/.
cp -f src/itusb2-status.c /usr/local/src/itusb2/.
cp -f src/itusb2-udoff.c /usr/local/src/itusb2/.
cp -f src/itusb2-udon.c /usr/local/src/itusb2/.
cp -f src/itusb2-upoff.c /usr/local/src/itusb2/.
cp -f src/itusb2-upon.c /usr/local/src/itusb2/.
cp -f src/GPL.txt /usr/local/src/itusb2/.
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
