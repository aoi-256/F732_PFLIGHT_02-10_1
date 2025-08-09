/*
 * LED.hpp
 *
 *  Created on: Jun 29, 2025
 *      Author: Sezakiaoi
 */

#ifndef INC_LED_HPP_
#define INC_LED_HPP_

#include <cstdint>
#include "gpio.h"

enum class PinState: uint8_t{

	off = 0,
	on,
	toggle
};

//Init
inline void redLed(PinState pin_state){

	if(pin_state == PinState::off){

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	}
	else if(pin_state == PinState::on){

		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	}
	else{

		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4);
	}
}

//Arm
inline void yellowLed(PinState pin_state){

	if(pin_state == PinState::off){

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	}
	else if(pin_state == PinState::on){

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	}
	else{

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	}
}

//Fly
inline void greenLed(PinState pin_state){

	if(pin_state == PinState::off){

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	else if(pin_state == PinState::on){

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else{

		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
	}
}

#endif /* INC_LED_HPP_ */
