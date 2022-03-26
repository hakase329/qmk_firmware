// Copyright 2022 hakase329 (@hakase329)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    hakase329
#define PRODUCT         i2c_test
#define DESCRIPTION     I2C I/O Expander (PCF8574) operation check code.

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/* A Custom matrix.c is used to poll the port expander D5 shows that the pins are hardwired there */
#define MATRIX_ROW_PINS { D7, E6, B4, B5 } // Pro Micro Pin Name = 6,7,8,9
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN } // IOエキスパンダで使うので空で確保
#define UNUSED_PINS
#define PORT_EXPANDER_ADDRESS 0x20 // PCF8574 (A2=L, A1=L, A0=L)
#define MATRIX_IO_DELAY 30 // 30us,8*30us = 240us = 0.24ms

#define LED_NUM_LOCK_PIN B0    // RX LED
#define LED_CAPS_LOCK_PIN D5   // TX LED
//#define LED_SCROLL_LOCK_PIN B0 // RX LED
