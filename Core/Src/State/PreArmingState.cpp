#include "State/Headers/FlightStates.h"

void PreArmingState::update(FlightManager& manager) {

	// Armスイッチをチェック
	if(manager.sbus_data.arm){

		//PreFlightStateに遷移
		manager.changeState(std::make_unique<PreFlightState>());
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
