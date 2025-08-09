#include "../../Inc/State/Headers/FlightStates.h"
#include <memory>
#include "FlightManager.h"
#include "LED.hpp"
#include <stdio.h>

void FailSafeState::update(FlightManager& manager) {


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

}
