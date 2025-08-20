/**
 * @file haptic_engine.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-11
 *
 * @copyright Copyright (c) 2024
 *
 */
// https://www.ti.com/cn/lit/ds/symlink/drv2605l.pdf
#pragma once
#include <vector>

namespace HapticEffect
{
    enum HapticEffect_t
    {
        StrongClick100 = 1,                     // 强力点击 - 100%
        StrongClick60,                          // 强力点击 - 60%
        StrongClick30,                          // 强力点击 - 30%
        SharpClick100,                          // 强力点击 - 30%
        SharpClick60,                           // 猛击 - 60%
        SharpClick30,                           // 猛击 - 30%
        SoftBump100,                            // 软冲击 - 100%
        SoftBump60,                             // 软冲击 - 60%
        SoftBump30,                             // 软冲击 - 30%
        DoubleClick100,                         // 双次点击 - 100%
        DoubleClick60,                          // 双次点击 - 60%
        TripleClick100,                         // 三次点击 - 100%
        SoftFuzz60,                             // 小毛刺 - 60%
        StrongBuzz100,                          // 剧烈蜂鸣 - 100%
        Alert750ms100,                          // 750ms 报警 100%
        Alert1000ms100,                         // 1000ms 报警 100%
        StrongClick1_100,                       // 强力点击 1 - 100%
        StrongClick2_80,                        // 强力点击 2 - 80%
        StrongClick3_60,                        // 强力点击 3 - 60%
        StrongClick4_30,                        // 强力点击 4 - 30%
        MediumClick1_100,                       // 中等力度点击 1 - 100%
        MediumClick2_80,                        // 中等力度点击 2 - 80%
        MediumClick3_60,                        // 中等力度点击 3 - 60%
        SharpTick1_100,                         // 猛击节拍 1 - 100%
        SharpTick2_80,                          // 猛击节拍 2 - 80%
        SharpTick3_60,                          // 猛击节拍 3 - 60%
        ShortDoubleClickStrong1_100,            // 短时间强力双击 1 – 100%
        ShortDoubleClickStrong2_80,             // 短时间强力双击 2 – 80%
        ShortDoubleClickStrong3_60,             // 短时间强力双击 3 – 60%
        ShortDoubleClickStrong4_30,             // 短时间强力双击 4 – 30%
        ShortDoubleClickMedium1_100,            // 短时间中等强度双击 1 – 100%
        ShortDoubleClickMedium2_80,             // 短时间中等强度双击 2 – 80%
        ShortDoubleClickMedium3_60,             // 短时间中等强度双击 3 – 60%
        ShortDoubleSharpTick1_100,              // 短时间双次猛击节拍 1 – 100%
        ShortDoubleSharpTick2_80,               // 短时间双次猛击节拍 2 – 80%
        ShortDoubleSharpTick3_60,               // 短时间双次猛击节拍 3 – 60%
        LongDoubleSharpClickStrong1_100,        // 长时间双次强力猛击 1 – 100%
        LongDoubleSharpClickStrong2_80,         // 长时间双次强力猛击 2 – 80%
        LongDoubleSharpClickStrong3_60,         // 长时间双次强力猛击 3 – 60%
        LongDoubleSharpClickStrong4_30,         // 长时间双次强力猛击 4 – 30%
        LongDoubleSharpClickMedium1_100,        // 长时间双次中度猛击 1 – 100%
        LongDoubleSharpClickMedium2_80,         // 长时间双次中度猛击 2 – 80%
        LongDoubleSharpClickMedium3_60,         // 长时间双次中度猛击 3 – 60%
        LongDoubleSharpTick1_100,               // 长时间双次猛击节拍 1 – 100%
        LongDoubleSharpTick2_80,                // 长时间双次猛击节拍 2 – 80%
        LongDoubleSharpTick3_60,                // 长时间双次猛击节拍 3 – 60%
        Buzz1_100,                              // 蜂鸣 1 – 100%
        Buzz2_80,                               // 蜂鸣 2 – 80%
        Buzz3_60,                               // 蜂鸣 3 – 60%
        Buzz4_40,                               // 蜂鸣 4 – 40%
        Buzz5_20,                               // 蜂鸣 5 – 20%
        PulsingStrong1_100,                     // 强脉冲 1 – 100%
        PulsingStrong2_60,                      // 强脉冲 2 – 60%
        PulsingMedium1_100,                     // 中等脉冲 1 – 100%
        PulsingMedium2_60,                      // 中等脉冲 2 – 60%
        PulsingSharp1_100,                      // 剧烈脉冲 1 – 100%
        PulsingSharp2_60,                       // 剧烈脉冲 2 – 60%
        TransitionClick1_100,                   // 转换点击 1 - 100%
        TransitionClick2_80,                    // 转换点击 1 - 100%
        TransitionClick3_60,                    // 转换点击 3 - 60%
        TransitionClick4_40,                    // 转换点击 4 - 40%
        TransitionClick5_20,                    // 转换点击 5 - 20%
        TransitionClick6_10,                    // 转换点击 6 - 10%
        TransitionHum1_100,                     // 转换噪声 1 - 100%
        TransitionHum2_80,                      // 转换噪声 2 - 80%
        TransitionHum3_60,                      // 转换噪声 3 - 60%
        TransitionHum4_40,                      // 转换噪声 4 - 40%
        TransitionHum5_20,                      // 转换噪声 5 - 20%
        TransitionHum6_10,                      // 转换噪声 6 - 10%
        TransitionRampDownLongSmooth1_100To0,   // 长时间平缓斜降转换 1 – 100 至 0%
        TransitionRampDownLongSmooth2_100To0,   // 长时间平缓斜降转换 2 – 100 至 0%
        TransitionRampDownMediumSmooth1_100To0, // 中等时间平缓斜降转换 1 – 100 至 0%
        TransitionRampDownMediumSmooth2_100To0, // 中等时间平缓斜降转换 2 – 100 至 0%
        TransitionRampDownShortSmooth1_100To0,  // 短时间平缓斜降转换 1 – 100 至 0%
        TransitionRampDownShortSmooth2_100To0,  // 短时间平缓斜降转换 2 – 100 至 0%
        TransitionRampDownLongSharp1_100To0,    // 长时间剧烈斜降转换 1 – 100 至 0%
        TransitionRampDownLongSharp2_100To0,    // 长时间剧烈斜降转换 2 – 100 至 0%
        TransitionRampDownMediumSharp1_100To0,  // 中等时间剧烈斜降转换 1 – 100 至 0%
        TransitionRampDownMediumSharp2_100To0,  // 中等时间剧烈斜降转换 2 – 100 至 0%
        TransitionRampDownShortSharp1_100To0,   // 短时间剧烈斜降转换 1 – 100 至 0%
        TransitionRampDownShortSharp2_100To0,   // 短时间剧烈斜降转换 2 – 100 至 0%
        TransitionRampUpLongSmooth1_0To100,     // 长时间平缓斜升转换 1 – 0 至 100%
        TransitionRampUpLongSmooth2_0To100,     // 长时间平缓斜升转换 2 – 0 至 100%
        TransitionRampUpMediumSmooth1_0To100,   // 中等时间平缓斜升转换 1 – 0 至 100%
        TransitionRampUpMediumSmooth2_0To100,   // 中等时间平缓斜升转换 2 – 0 至 100%
        TransitionRampUpShortSmooth1_0To100,    // 短时间平缓斜升转换 1 – 0 至 100%
        TransitionRampUpShortSmooth2_0To100,    // 短时间平缓斜升转换 2 – 0 至 100%
        TransitionRampUpLongSharp1_0To100,      // 长时间剧烈斜升转换 1 – 0 至 100%
        TransitionRampUpLongSharp2_0To100,      // 长时间剧烈斜升转换 2 – 0 至 100%
        TransitionRampUpMediumSharp1_0To100,    // 长时间剧烈斜升转换 2 – 0 至 100%
        TransitionRampUpMediumSharp2_0To100,    // 中等时间剧烈斜升转换 2 – 0 至 100%
        TransitionRampUpShortSharp1_0To100,     // 短时间剧烈斜升转换 1 – 0 至 100%
        TransitionRampUpShortSharp2_0To100,     // 短时间剧烈斜升转换 2 – 0 至 100%
        TransitionRampDownLongSmooth1_50To0,    // 长时间平缓斜降转换 1 – 50 至 0%
        TransitionRampDownLongSmooth2_50To0,    // 长时间平缓斜降转换 2 – 50 至 0%
        TransitionRampDownMediumSmooth1_50To0,  // 中等时间平缓斜降转换 1 – 50 至 0%
        TransitionRampDownMediumSmooth2_50To0,  // 中等时间平缓斜降转换 2 – 50 至 0%
        TransitionRampDownShortSmooth1_50To0,   // 短时间平缓斜降转换 1 – 50 至 0%
        TransitionRampDownShortSmooth2_50To0,   // 短时间平缓斜降转换 2 – 50 至 0%
        TransitionRampDownLongSharp1_50To0,     // 长时间剧烈斜降转换 1 – 50 至 0%
        TransitionRampDownLongSharp2_50To0,     // 长时间剧烈斜降转换 2 – 50 至 0%
        TransitionRampDownMediumSharp1_50To0,   // 中等时间剧烈斜降转换 1 – 50 至 0%
        TransitionRampDownMediumSharp2_50To0,   // 中等时间剧烈斜降转换 2 – 50 至 0%
        TransitionRampDownShortSharp1_50To0,    // 短时间剧烈斜降转换 1 – 50 至 0%
        TransitionRampDownShortSharp2_50To0,    // 短时间剧烈斜降转换 2 – 50 至 0%
        TransitionRampUpLongSmooth1_0To50,      // 长时间平缓斜升转换 1 – 0 至 50%
        TransitionRampUpLongSmooth2_0To50,      // 长时间平缓斜升转换 2 – 0 至 50%
        TransitionRampUpMediumSmooth1_0To50,    // 中等时间平缓斜升转换 1 – 0 至 50%
        TransitionRampUpMediumSmooth2_0To50,    // 中等时间平缓斜升转换 2 – 0 至 50%
        TransitionRampUpShortSmooth1_0To50,     // 短时间平缓斜升转换 1 – 0 至 50%
        TransitionRampUpShortSmooth2_0To50,     // 短时间平缓斜升转换 2 – 0 至 50%
        TransitionRampUpLongSharp1_0To50,       // 长时间剧烈斜升转换 1 – 0 至 50%
        TransitionRampUpLongSharp2_0To50,       // 长时间剧烈斜升转换 2 – 0 至 50%
        TransitionRampUpMediumSharp1_0To50,     // 中等时间剧烈斜升转换 1 – 0 至 50%
        TransitionRampUpMediumSharp2_0To50,     // 中等时间剧烈斜升转换 2 – 0 至 50%
        TransitionRampUpShortSharp1_0To50,      // 短时间剧烈斜升转换 1 – 0 至 50%
        TransitionRampUpShortSharp2_0To50,      // 短时间剧烈斜升转换 2 – 0 至 50%
        LongBuzzForProgrammaticStopping100,     // 编程停止导致长时间蜂鸣 – 100%
        SmoothHum1_NoKickOrBrakePulse_50,       // 平缓噪声 1（无回弹或制动脉冲） – 50%
        SmoothHum2_NoKickOrBrakePulse_40,       // 平缓噪声 2（无回弹或制动脉冲） – 40%
        SmoothHum3_NoKickOrBrakePulse_30,       // 平缓噪声 3（无回弹或制动脉冲） – 30%
        SmoothHum4_NoKickOrBrakePulse_20,       // 平缓噪声 4（无回弹或制动脉冲） – 20%
        SmoothHum5_NoKickOrBrakePulse_10        // 平缓噪声 5（无回弹或制动脉冲） – 10%
    };
}

namespace hal_components
{

    /**
     * @brief 触觉反馈（线性马达）组件基类
     *
     */
    class HapticEngineBase
    {
    public:
        virtual bool init()
        {
            return false;
        }

        virtual void enable() {}

        virtual void disable() {}

        /**
         * @brief 播放效果
         *
         * @param effect
         */
        virtual void playEffect(const HapticEffect::HapticEffect_t &effect) {}

        /**
         * @brief 播放效果序列
         *
         * @param effectSequence 效果序列，最多8个
         */
        virtual void playEffects(const std::vector<HapticEffect::HapticEffect_t> &effectSequence) {}

        virtual void stop() {}

        virtual bool isPlaying()
        {
            return false;
        }
    };

} // namespace hal_components
