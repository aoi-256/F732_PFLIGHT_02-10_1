/*
 * MadgwickAHRS_USER.hpp
 *
 *  Created on: May 27, 2025
 *      Author: aoi25
 */

#ifndef INC_MADGWICKAHRS_USER_HPP_
#define INC_MADGWICKAHRS_USER_HPP_

#include <cstdint>     // uint8_t, uint16_t, uint32_t などを使用する場合
#include <array>
#include "MadgwickAHRS.h"

Madgwick madgwick;

void madgwickStart(float rate){

	madgwick.begin(rate);
}

void madgwickUpdate(const std::array<float, 3>& accel, const std::array<float, 3>& gyro){

	madgwick.updateIMU(gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2]);
}

void madgwickGetAngle(std::array<float, 3>& angle){

	angle[0] = madgwick.getPitch();
	angle[1] = madgwick.getRoll();
	angle[2] = madgwick.getYaw();
}

#endif /* INC_MADGWICKAHRS_USER_HPP_ */
