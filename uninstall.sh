#!/bin/sh

echo Rolling back configurations...
rm -f /etc/udev/rules.d/70-bgtn-itusb2.rules
service udev restart
echo Removing man pages...
rm -f /usr/local/share/man/man1/itusb2-attach.1.gz
rm -f /usr/local/share/man/man1/itusb2-detach.1.gz
rm -f /usr/local/share/man/man1/itusb2-enum.1.gz
rm -f /usr/local/share/man/man1/itusb2-list.1.gz
rm -f /usr/local/share/man/man1/itusb2-lockotp.1.gz
rm -f /usr/local/share/man/man1/itusb2-reset.1.gz
rm -f /usr/local/share/man/man1/itusb2-status.1.gz
rm -f /usr/local/share/man/man1/itusb2-udoff.1.gz
rm -f /usr/local/share/man/man1/itusb2-udon.1.gz
rm -f /usr/local/share/man/man1/itusb2-upoff.1.gz
rm -f /usr/local/share/man/man1/itusb2-upon.1.gz
rmdir --ignore-fail-on-non-empty /usr/local/share/man/man1
echo Removing binaries...
make -C /usr/local/src/itusb2 uninstall
echo Removing source code files...
rm -rf /usr/local/src/itusb2
echo Done!
