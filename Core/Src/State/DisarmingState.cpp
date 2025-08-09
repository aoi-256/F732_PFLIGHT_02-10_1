#include "../../Inc/State/Headers/FlightStates.h"
#include <memory>
#include "FlightManager.h"
#include "LED.hpp"
#include <stdio.h>

void DisarmingState::update(FlightManager& manager) {
    // TODO: ディスアーミング状態の更新処理を実装

	manager.changeState(std::make_unique<PreArmingState>());
}

void DisarmingState::enter(FlightManager& manager) {


}

void DisarmingState::exit(FlightManager& manager) {

	yellowLed(PinState::off);
	greenLed(PinState::off);
}
