/**
 * @file mic.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class MicArduino : public hal_components::MicBase
{
public:
    void init() override;
    void start() override;
    void stop() override;
    bool isRunning() override;
    void printAllSamples() override;

private:
};
