/*
 * PWM.hpp
 *
 *  Created on: May 4, 2025
 *      Author: aoi25
 */

#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include <cstdint>
#include <array>
#include "tim.h"
#include "FlightData/SbusData.hpp"
#include "UserSetting/MotorSetting.hpp"

void calcMotorPwm(float throttle, std::array<float,3>& control, std::array<uint16_t,4>& motor);
void calcServoPwm(SbusChannelData sbus_data, uint16_t adc_value, std::array<uint16_t,2>& servo);
void pwmInit();
void pwmGenerate(std::array<uint16_t,4>& motor, std::array<uint16_t,2>& servo);
void pwmStop();
void testMotor();

#endif /* INC_PWM_HPP_ */
