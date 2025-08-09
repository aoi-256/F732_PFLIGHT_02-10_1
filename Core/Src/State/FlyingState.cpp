#include "State/Headers/FlightStates.h"

void FlyingState::update(FlightManager& manager) {

    // TODO: 飛行状態の更新処理を実装
	if(!manager.sbus_data.arm){

		manager.changeState(std::unique_ptr<FlightStateInterface>(std::make_unique<DisarmingState>()));
	}
}

void FlyingState::enter(FlightManager& manager) {
    // TODO: 飛行状態への入場処理を実装



}

void FlyingState::exit(FlightManager& manager) {
    // TODO: 飛行状態からの退場処理を実装
}
