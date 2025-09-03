/**
 * @file wear_levelling.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-03-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <stdint.h>
// https://github.com/espressif/esp-idf/blob/v5.1.4/examples/storage/wear_levelling/main/wear_levelling_example_main.c

uint8_t wl_fs_init(void);
uint8_t wl_fs_deinit(void);
uint8_t wl_fs_format(void);
const char *wl_fs_get_base_path();
void *wl_fs_get_wl_handler();
