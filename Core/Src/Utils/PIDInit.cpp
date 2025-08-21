#include "Utils/PIDInit.hpp"

// 実体定義
PID angle_pitch;
PID angle_roll;
PID rate_pitch;
PID rate_roll;
PID rate_yaw;

void InitPIDFromUserSetting() {
    
    angle_pitch.setGain(angle_pitch_gain.kp, angle_pitch_gain.ki, angle_pitch_gain.kd);
    angle_pitch.setLimit(angle_pitch_limit.i_max, angle_pitch_limit.d_max);
    angle_pitch.setTime(angle_pitch_dt.dt);

    angle_roll.setGain(angle_roll_gain.kp, angle_roll_gain.ki, angle_roll_gain.kd);
    angle_roll.setLimit(angle_roll_limit.i_max, angle_roll_limit.d_max);
    angle_roll.setTime(angle_roll_dt.dt);

    rate_pitch.setGain(rate_pitch_gain.kp, rate_pitch_gain.ki, rate_pitch_gain.kd);
    rate_pitch.setLimit(rate_pitch_limit.i_max, rate_pitch_limit.d_max);
    rate_pitch.setTime(rate_pitch_dt.dt);

    rate_roll.setGain(rate_roll_gain.kp, rate_roll_gain.ki, rate_roll_gain.kd);
    rate_roll.setLimit(rate_roll_limit.i_max, rate_roll_limit.d_max);
    rate_roll.setTime(rate_roll_dt.dt);

    rate_yaw.setGain(rate_yaw_gain.kp, rate_yaw_gain.ki, rate_yaw_gain.kd);
    rate_yaw.setLimit(rate_yaw_limit.i_max, rate_yaw_limit.d_max);
    rate_yaw.setTime(rate_yaw_dt.dt);

    ThreeDoFPID::getInstance(&angle_pitch, &angle_roll, &rate_pitch, &rate_roll, &rate_yaw);
}