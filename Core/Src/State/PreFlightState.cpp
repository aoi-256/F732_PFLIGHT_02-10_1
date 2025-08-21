#include "State/Headers/FlightStates.h"

void PreFlightState::update(FlightManager& manager) {

	// Armスイッチの判定
	if(!manager.sbus_data.arm){

		manager.changeState(std::make_unique<DisarmingState>());
	}

	// Servo判定とPwm出力(abc_value = 0)
	PwmCalcServo(manager.sbus_data, 0, manager.control_data.servo_pwm);
	PwmGenerateServo(manager.control_data.servo_pwm);

	// Flightスイッチの判定
	if(manager.sbus_data.fly){

		//PIDの初期化
		if (manager.threedofpid) {

			manager.threedofpid->pidReset(); // ThreeDoFPID型
		}

		//Madgwickフィルターの初期化(400hz)
		manager.madgwick.begin(UserSetting::MadgwickSampleFreq);

		//飛行用LEDをつける
		greenLed(PinState::on);

		manager.changeState(std::make_unique<FlyingState>());
	}
}

void PreFlightState::enter(FlightManager& manager) {


}

void PreFlightState::exit(FlightManager& manager) {

}
