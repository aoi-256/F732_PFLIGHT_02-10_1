/*
 * MotorSetting.hpp
 *
 *  Created on: Aug 21, 2025
 *      Author: Sezakiaoi
 */

#ifndef INC_MOTORSETTING_HPP_
#define INC_MOTORSETTING_HPP_

/* モーター配置（上が前）
 * 	1	2
 *
 * 	3	4
 */

//モーターのタイマー番号
struct MotorTim{

	TIM_HandleTypeDef* motor1 = &htim1;
	TIM_HandleTypeDef* motor2 = &htim1;
	TIM_HandleTypeDef* motor3 = &htim1;
	TIM_HandleTypeDef* motor4 = &htim1;
};

//モーターのチャンネル番号
struct MotorChannel{

	uint32_t motor1 = TIM_CHANNEL_1;
	uint32_t motor2 = TIM_CHANNEL_2;
	uint32_t motor3 = TIM_CHANNEL_3;
	uint32_t motor4 = TIM_CHANNEL_4;
};

//サーボのタイマー番号
struct ServoTim{

	TIM_HandleTypeDef* servo1 = &htim12;
	TIM_HandleTypeDef* servo2 = &htim12;
};

//モーターチャンネル番号
struct ServoChannel{

	uint32_t servo1 = TIM_CHANNEL_1;
	uint32_t servo2 = TIM_CHANNEL_2;
};

//モーター用のPWM値
struct MotorPWM{

	uint16_t counter_period = 2499 + 1;

	uint16_t max  = counter_period * 0.95;
	uint16_t min  = counter_period * 0.50;
	uint16_t init = counter_period * 0.40;
};

//サーボー用のPWM値
struct ServoPWM{

	uint16_t counter_period = 2499 + 1;

	uint16_t open   = counter_period * 0.68;
	uint16_t center = counter_period * 0.79;
	uint16_t close  = counter_period * 0.98;
};


#endif /* INC_MOTORSETTING_HPP_ */
