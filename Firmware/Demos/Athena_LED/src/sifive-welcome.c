/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>      // Include Serial Library
#include <time.h>       // Time-related features
#include <metal/gpio.h> // SiFive’s GPIO library

#define STARTUP_DELAY_US (1000000)
#define DWELL_TIME_US (10000)

#define OUTPUT_DEV_15799_IO_0 (0)    // Label: "0"                 // (PWM 0-0)
#define OUTPUT_DEV_15799_IO_1 (1)    // Label: "1"                 // (PWM 0-1)
#define OUTPUT_DEV_15799_IO_2 (2)    // Label: "2"   (SPI 1 SS0)   // (PWM 0-2)
#define OUTPUT_DEV_15799_IO_SI (3)   // Label: "SI"  (SPI 1 MOSI)  // (PWM 0-3)
#define OUTPUT_DEV_15799_IO_SO (4)   // Label: "SO"  (SPI 1 MISO)  //
#define OUTPUT_DEV_15799_IO_SCK (5)  // Label: "SCK" (SPI 1 SCK)   // (Blue LED)
#define OUTPUT_DEV_15799_IO_9 (9)    // Label: "9"   (SPI 1 SS2)   //
#define OUTPUT_DEV_15799_IO_10 (10)  // Label: "10"  (SPI 1 SS3)   // (PWM 2-0)
#define OUTPUT_DEV_15799_IO_11 (11)  // Label: "11"  (SPI 1 SS*)   // (PWM 2-1)
#define OUTPUT_DEV_15799_IO_SDA (12) // Label: "SDA" (I2C 0 Data)  // (PWM 2-2)
#define OUTPUT_DEV_15799_IO_SCL (13) // Label: "SCL" (I2C 0 Clock) // (PWM 2-3)
#define OUTPUT_DEV_15799_IO_RXI (16) // Label: "RXI" (UART 0 In)   //
#define OUTPUT_DEV_15799_IO_TXO (17) // Label: "TXO" (UART 0 Out)  //
#define OUTPUT_DEV_15799_IO_18 (18)  // Label: "18"  (UART TXO)    //
#define OUTPUT_DEV_15799_IO_19 (19)  // Label: "19"                // (PWM 1-1)
#define OUTPUT_DEV_15799_IO_20 (20)  // Label: "20"                // (PWM 1-0)
#define OUTPUT_DEV_15799_IO_21 (21)  // Label: "21"                // (PWM 1-2)
#define OUTPUT_DEV_15799_IO_22 (22)  // Label: "22"                // (PWM 1-3)
#define OUTPUT_DEV_15799_IO_23 (23)  // Label: "23"  (UART RXI)    //
//----Pin Definitions for DEV-15594 (Experimental)
#define OUTPUT_DEV_15594_IO_RXI (17) // Label: "RXI" (UART 0 RXI)    //
#define OUTPUT_DEV_15594_IO_TXO (16) // Label: "TXO" (UART 0 TXO)    //
#define OUTPUT_DEV_15594_IO_2 (18)   // Label: "2"   (UART TXO)      //
#define OUTPUT_DEV_15594_IO_3 (19)   // Label: "~3"                  // (PWM 1-1)
#define OUTPUT_DEV_15594_IO_4 (20)   // Label: "4"                   // (PWM 1-0)
#define OUTPUT_DEV_15594_IO_5 (21)   // Label: "~5"                  // (PWM 1-2)
#define OUTPUT_DEV_15594_IO_6 (22)   // Label: "~6"                  // (PWM 1-3)
#define OUTPUT_DEV_15594_IO_7 (23)   // Label: "7"   (UART RXI)      //
#define OUTPUT_DEV_15594_IO_8 (0)    // Label: "8"                   // (PWM 0-0)
#define OUTPUT_DEV_15594_IO_9 (1)    // Label: "~9"                  // (PWM 0-1)
#define OUTPUT_DEV_15594_IO_10 (2)   // Label: "~10" (SPI 1-SS0)     // (PWM 0-2)
#define OUTPUT_DEV_15594_IO_11 (3)   // Label: "~11" (SPI 1 MOSI)    // (PWM 0-3)
#define OUTPUT_DEV_15594_IO_12 (4)   // Label: "12" (SPI 1 MISO)     //
#define OUTPUT_DEV_15594_IO_13 (5)   // Label: "13" (SPI 1 SCK)      // ( Blue LED)
#define OUTPUT_DEV_15594_IO_SDA (12) // Label: "~SDA/18" (I2C 0 SDA) // (PWM 2-2)
#define OUTPUT_DEV_15594_IO_SCL (13) // Label: "~SCL/19" (I2C 0 SCL) // (PWM 2-3)
#define OUTPUT_DEV_15594_IO_15 (9)   // Label: "15" (SPI 1 SS2)      // (PWM 2-0)
#define OUTPUT_DEV_15594_IO_16 (10)  // Label: "16" (SPI 1 SS3)      // (PWM 2-1)
#define OUTPUT_DEV_15594_IO_17 (11)  // Label: "~17" (SPI 1 SS3*)    // (PWM 2-2)
#define OUTPUT_DEV_15594_IO_18 (12)  // Is connected to: OUTPUT_DEV_15594_IO_SDA
#define OUTPUT_DEV_15594_IO_19 (13)  // Is connected to: OUTPUT_DEV_15594_IO_SCL

void delay_us(int delayTime_us) {
    // Covert the requested time to multiples of 100 nanoseconds
    int requestedDelay_us_mul_10 = 10 * delayTime_us;

    // Store the start time
    clock_t startTime_us = clock();

    // Loop until the required time delay is achieved
    while( clock() < startTime_us + requestedDelay_us_mul_10);
}

int main() {
    delay_us(STARTUP_DELAY_US);
    printf("[ OK ] Power-on reset\n");

    //---Bare Metal Library: GPIO Setup
    struct metal_gpio* gpio_device = metal_gpio_get_device(0);

    //---Initialize GPIO directions
    metal_gpio_enable_output(gpio_device, OUTPUT_DEV_15799_IO_0); // Red LED
    metal_gpio_enable_output(gpio_device, OUTPUT_DEV_15799_IO_1); // Green LED
    metal_gpio_enable_output(gpio_device, OUTPUT_DEV_15799_IO_SCK); // Blue LED
    metal_gpio_disable_pinmux(gpio_device, OUTPUT_DEV_15799_IO_SCK); // Disable SPI

    while(1)
    {
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_0, 1); // Red On
        delay_us(DWELL_TIME_US);
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_0, 0); // Red off
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_1, 1); // Green On
        delay_us(DWELL_TIME_US);
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_1, 0); // Green off
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_SCK, 1); // Blue On
        delay_us(DWELL_TIME_US);
        metal_gpio_set_pin(gpio_device, OUTPUT_DEV_15799_IO_SCK, 0); // Blue Off
        printf("[INFO] Cycle complete.\n");
    }

    return 0;
}
