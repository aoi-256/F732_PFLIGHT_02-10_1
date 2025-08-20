#include "State/Headers/FlightStates.h"

void PreFlightState::update(FlightManager& manager) {

	// Armスイッチの判定
	if(!manager.sbus_data.arm){

		manager.changeState(std::make_unique<DisarmingState>());
	}

	// Flightスイッチの判定
	if(manager.sbus_data.fly){

		manager.changeState(std::make_unique<FlyingState>());
	}
}

void PreFlightState::enter(FlightManager& manager) {


}

void PreFlightState::exit(FlightManager& manager) {

	//PIDの初期化
	if (manager.pidUtils) {
		manager.pidUtils->pidReset();
	}

	//Madgwickフィルターの初期化(400hz)
	manager.madgwick.begin(400.0f);

	//飛行用LEDをつける
	greenLed(PinState::on);
}
