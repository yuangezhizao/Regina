/**
 * @file imu.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../utils/BMI270-Sensor-API/bmi270.h"
#include <hal/hal.h>

class ImuBmi270 : public hal_components::ImuBase
{
public:
    void init() override;
    void update() override;

private:
    struct bmi2_dev _bmi;

    static void bmi2_error_codes_print_result(int8_t rslt);
    static int8_t set_accel_gyro_config(struct bmi2_dev *bmi);
    static float lsb_to_mps2(int16_t val, float g_range, uint8_t bit_width);
    static float lsb_to_dps(int16_t val, float dps, uint8_t bit_width);

    /* ---------------------------------- Port ---------------------------------- */
    static int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
    static int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
    static void bmi2_delay_us(uint32_t period, void *intf_ptr);
};
