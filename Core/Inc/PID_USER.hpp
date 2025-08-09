#ifndef INC_PID_USER_HPP_
#define INC_PID_USER_HPP_

#include <cstdint>
#include <array>
#include "PID/pid.h"

// 実体は.cppで定義
extern PID angle_pitch;
extern PID angle_roll;

extern PID rate_pitch;
extern PID rate_roll;
extern PID rate_yaw;

extern const float angle_pid_time;
extern const float rate_pid_time;

inline void pidSetup(){

    //角度PID制御(100hz)
    angle_pitch.GainSet(2.2, 0.05, 0.2);
    angle_pitch.TimeSet(angle_pid_time);
    angle_pitch.LimitSet(200.0, 400.0); 

    angle_roll.GainSet(2.2, 0.05, 0.2);
    angle_roll.TimeSet(angle_pid_time);
    angle_roll.LimitSet(200.0, 400.0);  

    //角速度PD制御(400hz)
    rate_pitch.GainSet(0.8, 0.0, 0.001);
    rate_pitch.TimeSet(rate_pid_time);
    rate_pitch.LimitSet(200.0, 400.0);   

    rate_roll.GainSet(0.8, 0.0, 0.001);
    rate_roll.TimeSet(rate_pid_time);
    rate_roll.LimitSet(200.0, 400.0);     

    rate_yaw.GainSet(4, 0.0, 0.01);
    rate_yaw.TimeSet(rate_pid_time);
    rate_yaw.LimitSet(200.0, 400.0);
}

//角度PIDの計算
inline void anglePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target){

    angle_pitch.Calc(current[0], target[0]);
    angle_roll.Calc(current[1], target[1]);
}

//角速度PIDの計算
inline void ratePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target){

    rate_pitch.Calc(current[0], target[0]);
    rate_roll.Calc(current[1], target[1]);
    rate_yaw.Calc(current[2], target[2]);
}

//角度PIDの値取得
inline void anglePIDGetData(std::array<float, 3>& target_rate){

    target_rate[0] = angle_pitch.GetData();
    target_rate[1] = angle_roll.GetData();
}

//角速度PIDの値取得
inline void ratePIDGetData(std::array<float, 3>& rate){

    rate[0] = rate_pitch.GetData();
    rate[1] = rate_roll.GetData();
    rate[2] = rate_yaw.GetData();
}

//PIDの初期化
inline void pidReset(){

    angle_pitch.Reset();
    angle_roll.Reset();

    rate_pitch.Reset();
    rate_roll.Reset();
    rate_yaw.Reset();
}

#endif
