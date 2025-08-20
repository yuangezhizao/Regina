/**
 * @file shared.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "shared.h"

static SharedData::SharedData_t *_shared_data_instance = nullptr;

SharedData::SharedData_t &SharedData::Get()
{
    if (!_shared_data_instance)
    {
        _shared_data_instance = new SharedData::SharedData_t;
    }
    return *_shared_data_instance;
}

void SharedData::Destroy()
{
    if (_shared_data_instance)
    {
        delete _shared_data_instance;
        _shared_data_instance = nullptr;
    }
}
