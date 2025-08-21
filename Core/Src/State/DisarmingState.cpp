#include "State/Headers/FlightStates.h"

void DisarmingState::update(FlightManager& manager) {

	PwmStop();

	if (manager.pidUtils) {

		manager.pidUtils->pidReset();
	}

	manager.changeState(std::make_unique<PreArmingState>());
}

void DisarmingState::enter(FlightManager& manager) {



}

void DisarmingState::exit(FlightManager& manager) {

	yellowLed(PinState::off);
	greenLed(PinState::off);
}
