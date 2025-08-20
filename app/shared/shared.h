/**
 * @file shared.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

/**
 * @brief 共享数据层，提供一个带互斥锁的全局共享数据单例
 *
 */
namespace SharedData
{

    /**
     * @brief 共享数据定义
     *
     */
    struct SharedData_t
    {
        std::mutex mutex;

        struct Notification_t
        {
        };
        Notification_t Notification;

        struct Weather_t
        {
            std::string weather = "SUNNY";
            int temperature = 26;
        };
        Weather_t Weather;

        struct Ble_t
        {
            std::vector<std::string> messageList;
        };
        Ble_t Ble;
    };

    /**
     * @brief 获取共享数据实例
     *
     * @return SharedData_t&
     */
    SharedData_t &Get();

    /**
     * @brief 销毁共享数据实例
     *
     */
    void Destroy();

    /**
     * @brief 借用共享数据（互斥上锁）
     *
     */
    inline void Borrow()
    {
        Get().mutex.lock();
    }

    /**
     * @brief 归还共享数据（互斥解锁）
     *
     */
    inline void Return()
    {
        Get().mutex.unlock();
    }

    // 封装一下不然长的一
    inline SharedData_t::Notification_t &Notification()
    {
        return Get().Notification;
    }
    inline SharedData_t::Weather_t &Weather()
    {
        return Get().Weather;
    }
    inline SharedData_t::Ble_t &Ble()
    {
        return Get().Ble;
    }

} // namespace SharedData
