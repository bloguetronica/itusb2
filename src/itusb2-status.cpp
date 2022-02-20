/* ITUSB2 Status Command - Version 2.0 for Debian Linux
   Copyright (c) 2020-2022 Samuel Lourenço

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation, either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <https://www.gnu.org/licenses/>.


   Please feel free to contact me via e-mail: samuel.fmlourenco@gmail.com */


// Includes
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include "error.h"
#include "itusb2device.h"

int main(int argc, char **argv)
{
    int err, errlvl = EXIT_SUCCESS;
    ITUSB2Device device;
    if (argc < 2) {  // If the program was called without arguments
        err = device.open();  // Open a device and get the device handle
    } else {  // Serial number was specified as argument
        err = device.open(argv[1]);  // Open the device having the specified serial number, and get the device handle
    }
    if (err == ITUSB2Device::SUCCESS) {  // Device was successfully opened
        int errcnt = 0;
        std::string errstr;
        device.setup(errcnt, errstr);  // Prepare the device (SPI setup)
        bool up = device.getUSBPowerStatus(errcnt, errstr);  // Get VBUS status
        bool ud = device.getUSBDataStatus(errcnt, errstr);  // Data lines status
        bool cd = device.getDUTConnectionStatus(errcnt, errstr);  // Device connection status
        bool hs = device.getDUTSpeedStatus(errcnt, errstr);  // Device link speed status
        float curr = device.getCurrent(errcnt, errstr);  // VBUS current reading
        bool oc = device.getOvercurrentStatus(errcnt, errstr);  // Over-current flag
        if (errcnt > 0) {  // In case of error
            if (device.disconnected()) {  // If the device disconnected
                std::cerr << "Device disconnected.\n";
            } else {
                printErrors(errstr);
            }
            errlvl = EXIT_FAILURE;
        } else {  // Operation successful
            std::cout << "Status: Connection " << (up && ud ? "enabled" : "disabled") << std::endl;  // Print USB connection status
            std::cout << "USB power: " << (up ? "Enabled" : "Disabled") << std::endl;  // Print USB power status
            std::cout << "USB data: " << (ud ? "Enabled" : "Disabled") << std::endl;  // Print USB data status
            std::cout << "Device: " << (cd ? "Detected" : "Not detected") << std::endl;  // Print device detection status (note that a device can be detected even if the USB data lines are disabled)
            if (up && ud && cd) {  // If USB connection is fully enabled and a device is detected
                std::cout << "Link mode: "  << (hs ? "High speed" : "Full/low speed") << std::endl;  // Print USB link mode
            }
            std::cout << "Current: ";
            if (curr < 1000) {  // If the current reading is lesser than 1000mA
                std::cout << std::fixed << std::setprecision(1) << curr << "mA";  // Print the current reading
                if (curr > 500) {
                    std::cout << " (OC)";  // Print "(OC)" next to the value, to indicate that the current exceeds the 500mA limit established by the USB 2.0 specification (and also may cause a trip)
                }
            } else {  // Otherwise
                std::cout << "OL";  // Print "OL" to indicate an out of limits reading
            }
            std::cout << std::endl;
            if (oc) {
                std::cout << "Warning: Fault detected!" << std::endl;  // Over-current or over-temperature trip condition detected
            }
        }
        device.close();
    } else {  // Failed to open device
        if (err == ITUSB2Device::ERROR_INIT) {  // Failed to initialize libusb
            std::cerr << "Could not initialize libusb\n";
        } else if (err == ITUSB2Device::ERROR_NOT_FOUND) {  // Failed to find device
            std::cerr << "Could not find device.\n";
        } else if (err == ITUSB2Device::ERROR_BUSY) {  // Failed to claim interface
            std::cerr << "Device is currently unavailable.\n";
        }
        errlvl = EXIT_FAILURE;
    }
    return errlvl;
}
