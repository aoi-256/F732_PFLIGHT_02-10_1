#ifndef PIDSETTING_HPP
#define PIDSETTING_HPP

#include "PID/PID.h"

// ゲイン用構造体
struct PIDGain {
    float kp;
    float ki;
    float kd;
};

// 制限値用構造体（dtを除外）
struct PIDLimit {
    float d_max;
    float i_max;
};

// dt専用構造体（または定数）
struct PIDDt {
    float dt;
};

// PIDインスタンス生成用の設定
namespace UserSetting {
    // 角度PID設定
    constexpr PIDGain angle_pitch_gain = { 1.0f, 0.01f, 0.1f };
    constexpr PIDLimit angle_pitch_limit = { 100.0f, 10.0f };
    constexpr PIDDt angle_pitch_dt = { 0.01f };

    constexpr PIDGain angle_roll_gain = { 1.0f, 0.01f, 0.1f };
    constexpr PIDLimit angle_roll_limit = { 100.0f, 10.0f };
    constexpr PIDDt angle_roll_dt = { 0.01f };

    // 角速度PID設定
    constexpr PIDGain rate_pitch_gain = { 0.8f, 0.02f, 0.05f };
    constexpr PIDLimit rate_pitch_limit = { 80.0f, 8.0f };
    constexpr PIDDt rate_pitch_dt = { 0.01f };

    constexpr PIDGain rate_roll_gain = { 0.8f, 0.02f, 0.05f };
    constexpr PIDLimit rate_roll_limit = { 80.0f, 8.0f };
    constexpr PIDDt rate_roll_dt = { 0.01f };

    constexpr PIDGain rate_yaw_gain = { 0.5f, 0.01f, 0.02f };
    constexpr PIDLimit rate_yaw_limit = { 50.0f, 5.0f };
    constexpr PIDDt rate_yaw_dt = { 0.01f };
}

#endif // PIDSETTING_HPP