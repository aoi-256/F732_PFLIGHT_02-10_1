#ifndef INC_PID_USER_HPP_
#define INC_PID_USER_HPP_

#include <cstdint>
#include <array>
#include "PID/PID.h"  // 大文字に統一

// 実体は.cppで定義
extern PID angle_pitch;
extern PID angle_roll;

extern PID rate_pitch;
extern PID rate_roll;
extern PID rate_yaw;

inline void pidSetup(){
    // 設定は config.cpp の構造体初期値＋コンストラクタで行っています
}

// 角度PIDの計算
inline void anglePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target){
    angle_pitch.calc(target[0], current[0]);
    angle_roll.calc(target[1], current[1]);
}

// 角速度PIDの計算
inline void ratePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target){
    rate_pitch.calc(target[0], current[0]);
    rate_roll.calc(target[1], current[1]);
    rate_yaw.calc(target[2], current[2]);
}

// 角度PIDの値取得
inline void anglePIDGetData(std::array<float, 3>& target_rate){
    target_rate[0] = angle_pitch.getData();
    target_rate[1] = angle_roll.getData();
}

// 角速度PIDの値取得
inline void ratePIDGetData(std::array<float, 3>& rate){
    rate[0] = rate_pitch.getData();
    rate[1] = rate_roll.getData();
    rate[2] = rate_yaw.getData();
}

// PIDの初期化（積分・履歴のクリア）
inline void pidReset(){
    angle_pitch.reset();
    angle_roll.reset();

    rate_pitch.reset();
    rate_roll.reset();
    rate_yaw.reset();
}

#endif
