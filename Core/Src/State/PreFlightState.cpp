#include "../../Inc/State/Headers/FlightStates.h"
#include <memory>
#include <stdio.h>

#include "FlightManager.h"
#include "LED.hpp"
#include "PID_USER.hpp"

void PreFlightState::update(FlightManager& manager) {

	// Armスイッチの判定
	if(!manager.sbus_data.arm){

		manager.changeState(std::unique_ptr<FlightStateInterface>(std::make_unique<DisarmingState>()));
	}

	// Flightスイッチの判定
	if(manager.sbus_data.fly){

		manager.changeState(std::unique_ptr<FlightStateInterface>(std::make_unique<FlyingState>()));
	}
}

void PreFlightState::enter(FlightManager& manager) {


}

void PreFlightState::exit(FlightManager& manager) {

	//PIDの初期化
	pidSetup();

	//

	//飛行用LEDをつける
	greenLed(PinState::on);

}
