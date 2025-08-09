#include "PID_USER.hpp"

PID angle_pitch;
PID angle_roll;

PID rate_pitch;
PID rate_roll;
PID rate_yaw;

const float angle_pid_time = 0.010f;
const float rate_pid_time = 0.0025f;