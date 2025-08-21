#include "State/Headers/FlightStates.h"

void DisarmingState::update(FlightManager& manager) {

	PwmStop();

	if (manager.threedofpid) {
		manager.threedofpid->pidReset(); // ThreeDoFPID型
	}

	manager.changeState(std::make_unique<PreArmingState>());
}

void DisarmingState::enter(FlightManager& manager) {



}

void DisarmingState::exit(FlightManager& manager) {

	yellowLed(PinState::off);
	greenLed(PinState::off);
}
