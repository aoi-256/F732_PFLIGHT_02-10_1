#include "../../Inc/State/Headers/FlightStates.h"
#include <memory>
#include "FlightManager.h"
#include <stdio.h>
#include "PWM.hpp"
#include "LED.hpp"

void PreArmingState::update(FlightManager& manager) {

	// Armスイッチをチェック
	if(manager.sbus_data.arm){

		//PreFlightStateに遷移
		manager.changeState(std::unique_ptr<FlightStateInterface>(std::make_unique<PreFlightState>()));
	}

}

void PreArmingState::enter(FlightManager& manager) {

	//None
}

void PreArmingState::exit(FlightManager& manager) {

	//ESCの初期化をすませておく
	pwmInit();

	//黄LEDをつける
	yellowLed(PinState::on);
}
