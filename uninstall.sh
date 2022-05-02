#!/bin/sh

echo Rolling back configurations...
rm -f /etc/udev/rules.d/70-bgtn-itusb2.rules
service udev restart
echo Removing binaries and man pages...
make -C /usr/local/src/itusb2 uninstall
echo Removing source code files...
rm -rf /usr/local/src/itusb2
echo Done!
