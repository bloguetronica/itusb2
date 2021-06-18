/* ITUSB2 core functions - Version 1.1
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


// Includes
#include <stdio.h>
#include <stdlib.h>
#include "itusb2-core.h"

// Defines
#define TR_TIMEOUT 100  // Transfer timeout in milliseconds

// Global variables
int err_level;

// Configures the given SPI channel in respect to its chip select mode, clock frequency, polarity and phase
void configure_spi_mode(libusb_device_handle *devhandle, uint8_t channel, bool csmode, uint8_t cfrq, bool cpol, bool cpha)
{
    unsigned char control_buf_out[2] = {
        channel,                                                        // Selected channel
        (uint8_t)(cpha << 5 | cpol << 4 | csmode << 3 | (0x07 & cfrq))  // Control word (specified chip select mode, clock frequency, polarity and phase)
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x31, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x31).\n");
        err_level = EXIT_FAILURE;
    }
}

// Disables the chip select corresponding to the target channel
void disable_cs(libusb_device_handle *devhandle, uint8_t channel)
{
    unsigned char control_buf_out[2] = {
        channel,  // Selected channel
        0x00      // Corresponding chip select disabled
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x25, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x25).\n");
        err_level = EXIT_FAILURE;
    }
}

// Disables all SPI delays for a given channel
void disable_spi_delays(libusb_device_handle *devhandle, uint8_t channel)
{
    unsigned char control_buf_out[8] = {
        channel,     // Selected channel
        0x00,        // All SPI delays disabled, no CS toggle
        0x00, 0x00,  // Inter-byte,
        0x00, 0x00,  // post-assert and
        0x00, 0x00   // pre-deassert delays all set to 0us
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x33, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x33).\n");
        err_level = EXIT_FAILURE;
    }
}

// Gets the current value of the GPIO.1 pin on the CP2130
bool get_gpio1(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x20, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x20).\n");
        err_level = EXIT_FAILURE;
    }
    return ((0x10 & control_buf_in[1]) != 0x00);  // Returns one if bit 4 of byte 1, which corresponds to the GPIO.1 pin, is not set to zero
}

// Gets the current value of the GPIO.2 pin on the CP2130
bool get_gpio2(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x20, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x20).\n");
        err_level = EXIT_FAILURE;
    }
    return ((0x20 & control_buf_in[1]) != 0x00);  // Returns one if bit 5 of byte 1, which corresponds to the GPIO.2 pin, is not set to zero
}

// Gets the current value of the GPIO.3 pin on the CP2130
bool get_gpio3(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x20, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x20).\n");
        err_level = EXIT_FAILURE;
    }
    return ((0x40 & control_buf_in[1]) != 0x00);  // Returns one if bit 6 of byte 1, which corresponds to the GPIO.3 pin, is not set to zero
}

// Gets the current value of the GPIO.4 pin on the CP2130
bool get_gpio4(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x20, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x20).\n");
        err_level = EXIT_FAILURE;
    }
    return ((0x80 & control_buf_in[1]) != 0x00);  // Returns one if bit 7 of byte 1, which corresponds to the GPIO.4 pin, is not set to zero
}

// Gets the current value of the GPIO.5 pin on the CP2130
bool get_gpio5(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x20, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x20).\n");
        err_level = EXIT_FAILURE;
    }
    return ((0x01 & control_buf_in[0]) != 0x00);  // Returns one if bit 0 of byte 0, which corresponds to the GPIO.5 pin, is not set to zero
}

// Gets the raw value, corresponding to the measured current, from the LTC2312 ADC
uint16_t get_raw_current(libusb_device_handle *devhandle)
{
    unsigned char read_command_buf[8] = {
        0x00, 0x00,             // Reserved
        0x00,                   // Read command
        0x00,                   // Reserved
        0x02, 0x00, 0x00, 0x00  // Two bytes to read
    };
    int bytes_written;
    if (libusb_bulk_transfer(devhandle, 0x01, read_command_buf, (int)sizeof(read_command_buf), &bytes_written, TR_TIMEOUT) != 0) {
        fprintf(stderr, "Error: Failed bulk OUT transfer to endpoint 1 (address 0x01).\n");
        err_level = EXIT_FAILURE;
    }
    unsigned char read_input_buf[2];
    int bytes_read;
    if (libusb_bulk_transfer(devhandle, 0x82, read_input_buf, (int)sizeof(read_input_buf), &bytes_read, TR_TIMEOUT) != 0) {  // This bulk transfer should be done regardless of the result of the previous one (version 1.1 fix)
        fprintf(stderr, "Error: Failed bulk IN transfer from endpoint 2 (address 0x82).\n");
        err_level = EXIT_FAILURE;
    }
    return (uint16_t)(read_input_buf[0] << 4 | read_input_buf[1] >> 4);
}

// Checks if the OTP ROM of the CP2130 is locked
bool is_otp_locked(libusb_device_handle *devhandle)
{
    unsigned char control_buf_in[2];
    uint16_t size = (uint16_t)sizeof(control_buf_in);
    if (libusb_control_transfer(devhandle, 0xC0, 0x6E, 0x0000, 0x0000, control_buf_in, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0xC0, 0x6E).\n");
        err_level = EXIT_FAILURE;
    }
    return (control_buf_in[0] == 0x00 && control_buf_in[1] == 0x00);  // Returns one if both lock bytes are set to zero, that is, the OPT ROM is locked
}

// Locks the OTP ROM on the CP2130
void lock_otp(libusb_device_handle *devhandle)
{
    unsigned char control_buf_out[2] = {
        0x00, 0x00  // Values to be written into the lock bytes, so that both are set to zero
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x6F, 0xA5F1, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x6F).\n");
        err_level = EXIT_FAILURE;
    }
}

// Issues a reset to the CP2130, which in effect resets the entire device
void reset(libusb_device_handle *devhandle)
{
    if (libusb_control_transfer(devhandle, 0x40, 0x10, 0x0000, 0x0000, NULL, 0, TR_TIMEOUT) != 0) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x10).\n");
        err_level = EXIT_FAILURE;
    }
}

// Enables the chip select of the target channel, disabling any others
void select_cs(libusb_device_handle *devhandle, uint8_t channel)
{
    unsigned char control_buf_out[2] = {
        channel,  // Selected channel
        0x02      // Only the corresponding chip select is enabled, all the others are disabled
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x25, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x25).\n");
        err_level = EXIT_FAILURE;
    }
}

// Sets the GPIO.1 pin on the CP2130 to a given value
void set_gpio1(libusb_device_handle *devhandle, bool value)
{
    unsigned char control_buf_out[4] = {
        0x00, (uint8_t)(value << 4),  // Set the value of GPIO.1 to the intended value
        0x00, 0x10                    // Set the mask so that only GPIO.1 is changed
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x21, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x21).\n");
        err_level = EXIT_FAILURE;
    }
}

// Sets the GPIO.2 pin on the CP2130 to a given value
void set_gpio2(libusb_device_handle *devhandle, bool value)
{
    unsigned char control_buf_out[4] = {
        0x00, (uint8_t)(value << 5),  // Set the value of GPIO.2 to the intended value
        0x00, 0x20                    // Set the mask so that only GPIO.2 is changed
    };
    uint16_t size = (uint16_t)sizeof(control_buf_out);
    if (libusb_control_transfer(devhandle, 0x40, 0x21, 0x0000, 0x0000, control_buf_out, size, TR_TIMEOUT) != size) {
        fprintf(stderr, "Error: Failed control transfer (0x40, 0x21).\n");
        err_level = EXIT_FAILURE;
    }
}
