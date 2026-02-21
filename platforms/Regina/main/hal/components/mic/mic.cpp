/**
 * @file mic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mic.h"
#include "../../hal_config.h"
#include <Arduino.h>
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>

// Define how many conversion per pin will happen and reading the data will be and average of all conversions
#define CONVERSIONS_PER_PIN 5

using namespace SmoothUIToolKit;

static const char *_tag = "mic";

static constexpr size_t _samples_num = 256;
static constexpr uint32_t _sample_rate = 44100;

static RingBuffer<int, _samples_num> *_sample_buffer = nullptr;
static adc_continuous_result_t *_result_buffer = nullptr;
static volatile int _sample_cycle_count = 0;
static volatile bool _sample_cycled_flag = false;
static volatile bool _is_running = false;

void ARDUINO_ISR_ATTR _adc_complete_isr()
{
    if (analogContinuousRead(&_result_buffer, 0))
    {
        // Push sample
        _sample_buffer->put(_result_buffer[0].avg_read_raw);

        _sample_cycle_count = _sample_cycle_count + 1;
        if (_sample_cycle_count > _samples_num)
        {
            _sample_cycle_count = 0;
            _sample_cycled_flag = true;
        }
    }
}

void MicArduino::init()
{
    mclog::tagInfo(_tag, "init");

    static uint8_t adc_pins[1] = {HAL_PIN_MIC};

    _sample_buffer = new RingBuffer<int, _samples_num>;

    analogContinuousSetWidth(12);
    // analogContinuousSetAtten(ADC_0db);
    analogContinuous(adc_pins, 1, CONVERSIONS_PER_PIN, _sample_rate, _adc_complete_isr);
}

void MicArduino::start()
{
    if (_is_running)
    {
        mclog::tagWarn(_tag, "already running");
        return;
    }

    mclog::tagInfo(_tag, "start sampling");

    _sample_cycle_count = 0;
    _sample_cycled_flag = false;

    analogContinuousStart();
    _is_running = true;
}

void MicArduino::stop()
{
    if (!_is_running)
    {
        mclog::tagWarn(_tag, "already stopped");
        return;
    }

    mclog::tagInfo(_tag, "stop sampling");

    analogContinuousStop();
    _is_running = false;
}

bool MicArduino::isRunning()
{
    return _is_running;
}

void MicArduino::printAllSamples()
{
    if (_sample_cycled_flag)
    {
        _sample_cycled_flag = false;
        analogContinuousStop();
        _sample_buffer->peekAll([](const int &sample)
                                { printf("m:%d\n", sample); });
        analogContinuousStart();
    }
}
