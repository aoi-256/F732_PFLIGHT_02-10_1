#pragma once

#include "UserSetting/PIDSetting.hpp"
#include "PID/PID.h"
#include "Utils/PIDUtils.hpp"

// extern宣言のみ
extern PID angle_pitch;
extern PID angle_roll;
extern PID rate_pitch;
extern PID rate_roll;
extern PID rate_yaw;

using namespace UserSetting;

void InitPIDFromUserSetting();
