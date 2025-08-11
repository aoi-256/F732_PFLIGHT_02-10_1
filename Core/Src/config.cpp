// 各種設定とオブジェクトの作成

#include "PID_USER.hpp"
#include <array> // 構造体で使用

// ゲインや制御周期などの設定はここを変更
struct AnglePid {
    std::array<float, 3> pitch_gain = {2.2f, 0.05f, 0.20f}; // ピッチ軸のPIDゲイン
    std::array<float, 2> pitch_max  = {200.0f, 400.0f};     // {Imax, Dmax}

    std::array<float, 3> roll_gain  = {2.2f, 0.05f, 0.20f}; // ロール軸のPIDゲイン
    std::array<float, 2> roll_max   = {200.0f, 400.0f};     // {Imax, Dmax}

    float dt = 0.010f;                                       // 制御周期 [s]
} angle_pid;

struct RatePid {
    std::array<float, 3> pitch_gain = {0.8f, 0.0f, 0.001f};
    std::array<float, 2> pitch_max  = {200.0f, 400.0f};     // {Imax, Dmax}

    std::array<float, 3> roll_gain  = {0.8f, 0.0f, 0.001f};
    std::array<float, 2> roll_max   = {200.0f, 400.0f};     // {Imax, Dmax}

    std::array<float, 3> yaw_gain   = {0.8f, 0.0f, 0.001f};
    std::array<float, 2> yaw_max    = {200.0f, 400.0f};     // {Imax, Dmax}

    float dt = 0.0025f;                                      // 制御周期 [s]
} rate_pid;

// PIDのインスタンス作成
// コンストラクタ順序: (p, i, d, d_max, i_max, time)
PID angle_pitch(
    angle_pid.pitch_gain[0], angle_pid.pitch_gain[1], angle_pid.pitch_gain[2],
    angle_pid.pitch_max[1],  angle_pid.pitch_max[0],
    angle_pid.dt
);
PID angle_roll(
    angle_pid.roll_gain[0],  angle_pid.roll_gain[1],  angle_pid.roll_gain[2],
    angle_pid.roll_max[1],   angle_pid.roll_max[0],
    angle_pid.dt
);

PID rate_pitch(
    rate_pid.pitch_gain[0],  rate_pid.pitch_gain[1],  rate_pid.pitch_gain[2],
    rate_pid.pitch_max[1],   rate_pid.pitch_max[0],
    rate_pid.dt
);
PID rate_roll(
    rate_pid.roll_gain[0],   rate_pid.roll_gain[1],   rate_pid.roll_gain[2],
    rate_pid.roll_max[1],    rate_pid.roll_max[0],
    rate_pid.dt
);
PID rate_yaw(
    rate_pid.yaw_gain[0],    rate_pid.yaw_gain[1],    rate_pid.yaw_gain[2],
    rate_pid.yaw_max[1],     rate_pid.yaw_max[0],
    rate_pid.dt
);

// Madgwickフィルタ
#include "MadgwickAHRS_USER.hpp"

Madgwick madgwick;

// IMU
#include "IMU.hpp"
#include "spi.h"
#include "gpio.h"

// IMUインスタンス
ICM42688P_HAL_SPI icm(&hspi1, GPIOA, GPIO_PIN_4);
