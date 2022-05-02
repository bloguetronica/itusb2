This directory contains all source code files required for compiling the
commands for ITUSB2 USB Test Switch. A list of relevant files follows:
– cp2130.cpp;
– cp2130.h;
– error.cpp;
– error.h;
– itusb2-attach.cpp;
– itusb2-detach.cpp;
– itusb2device.cpp;
– itusb2device.h;
– itusb2-enum.cpp;
– itusb2-info.cpp;
– itusb2-list.cpp;
– itusb2-lockotp.cpp;
– itusb2-reset.cpp;
– itusb2-status.cpp;
– itusb2-udoff.cpp;
– itusb2-udon.cpp;
– itusb2-upoff.cpp;
– itusb2-upon.cpp;
– libusb-extra.c;
– libusb-extra.h;
– Makefile;
– man/itusb2-attach.1;
– man/itusb2-detach.1;
– man/itusb2-enum.1;
– man/itusb2-info.1;
– man/itusb2-list.1;
– man/itusb2-lockotp.1;
– man/itusb2-reset.1;
– man/itusb2-status.1;
– man/itusb2-udoff.1;
– man/itusb2-udon.1;
– man/itusb2-upoff.1;
– man/itusb2-upon.1.

In order to compile successfully all commands, you must have the packages
"build-essential" and "libusb-1.0-0-dev" installed. Given that, if you wish to
simply compile, change your working directory to the current one on a terminal
window, and simply invoke "make" or "make all". If you wish to install besides
compiling, run "sudo make install". Alternatively, if you wish to force a
rebuild, you should invoke "make clean all", or "sudo make clean install" if
you prefer to install after rebuilding.

It may be necessary to undo any previous operations. Invoking "make clean"
will delete all object code generated (binaries included) during earlier
compilations. You can also invoke "sudo make uninstall" to unistall the
binaries.

P.S.:
Notice that any make operation containing the targets "install" or "uninstall"
(e.g. "make all install" or "make uninstall") requires root permissions, or in
other words, must be run with sudo.
