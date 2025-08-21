#include "State/Headers/FlightStates.h"

void PreArmingState::update(FlightManager& manager) {

	// Armスイッチをチェック
	if(manager.sbus_data.arm){

		//PreFlightStateに遷移
		manager.changeState(std::make_unique<PreFlightState>());
	}

	// Servo判定とPwm出力(abc_value = 0)
	PwmCalcServo(manager.sbus_data, 0, manager.control_data.servo_pwm);
	PwmGenerateServo(manager.control_data.servo_pwm);
}

void PreArmingState::enter(FlightManager& manager) {

	//None
}

void PreArmingState::exit(FlightManager& manager) {

	//ESCの初期化をすませておく
	PwmInit();

	//黄LEDをつける
	yellowLed(PinState::on);
}
