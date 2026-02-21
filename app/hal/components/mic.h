/**
 * @file mic.h
 * @author yuangezhizao
 * @brief
 * @version 0.1
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

namespace hal_components
{

    /**
     * @brief 麦克风组件基类
     *
     */
    class MicBase
    {
    public:
        virtual ~MicBase() = default;

        virtual void init() {}

        /**
         * @brief 开始麦克风采集
         *
         */
        virtual void start() {}

        /**
         * @brief 停止麦克风采集
         *
         */
        virtual void stop() {}

        /**
         * @brief 是否正在采集
         *
         * @return true
         * @return false
         */
        virtual bool isRunning()
        {
            return false;
        }

        /**
         * @brief 批量打印所有采样数据
         *
         */
        virtual void printAllSamples() {}
    };

} // namespace hal_components
