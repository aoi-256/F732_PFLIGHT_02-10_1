#include "State/Headers/FlightStates.h"

void FailSafeState::update(FlightManager& manager) {

	//enterでループを使った強制停止をするため未実装

}

void FailSafeState::enter(FlightManager& manager) {

	while(1){

		for(volatile uint32_t i=0; i<1000000; i++);

		redLed(PinState::toggle);
		yellowLed(PinState::toggle);
		greenLed(PinState::toggle);
	}
}

void FailSafeState::exit(FlightManager& manager) {

	//failsafeからの復帰処理
	//実装予定なし
}
