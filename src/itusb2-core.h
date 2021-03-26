/* ITUSB2 core functions - Version 1.0
   Copyright (c) 2020-2021 Samuel Lourenço

   This library is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this library.  If not, see <https://www.gnu.org/licenses/>.


   Please feel free to contact me via e-mail: samuel.fmlourenco@gmail.com */


#ifndef ITUSB2_CORE_H_
#define ITUSB2_CORE_H_

// Includes
#include <stdbool.h>
#include <libusb-1.0/libusb.h>

// Defines
#define CFRQ1500K 0x03  // Value corresponding to a clock frequency of 1.5MHz, applicable to configure_spi_mode()
#define CPOL0 false     // Boolean corresponding to CPOL = 0, applicable to configure_spi_mode()
#define CPHA0 false     // Boolean corresponding to CPHA = 0, applicable to configure_spi_mode()
#define CSMODEPP true   // Boolean corresponding to chip select push-pull mode, applicable to configure_spi_mode()
#define VID 0x10C4      // USB vendor ID
#define PID 0x8CDF      // USB product ID

// Global external variables
extern int err_level;

// Function prototypes
void configure_spi_mode(libusb_device_handle *devhandle, uint8_t channel, bool csmode, uint8_t cfrq, bool cpol, bool cpha);
void disable_cs(libusb_device_handle *devhandle, uint8_t channel);
void disable_spi_delays(libusb_device_handle *devhandle, uint8_t channel);
uint16_t get_current(libusb_device_handle *devhandle);
bool get_gpio1(libusb_device_handle *devhandle);
bool get_gpio2(libusb_device_handle *devhandle);
bool get_gpio3(libusb_device_handle *devhandle);
bool get_gpio4(libusb_device_handle *devhandle);
bool get_gpio5(libusb_device_handle *devhandle);
bool is_otp_locked(libusb_device_handle *devhandle);
void lock_otp(libusb_device_handle *devhandle);
void reset(libusb_device_handle *devhandle);
void select_cs(libusb_device_handle *devhandle, uint8_t channel);
void set_gpio1(libusb_device_handle *devhandle, bool value);
void set_gpio2(libusb_device_handle *devhandle, bool value);

#endif
