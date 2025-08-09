#include "../../Inc/State/Headers/FlightStates.h"

#include <memory>
#include <stdio.h>

#include "FlightManager.h"
#include "imu.hpp"
#include "LED.hpp"
#include "PWM.hpp"

void InitState::update(FlightManager& manager) {

	// TODO: SBUSの受信チェックをする

	// SBUSの受信チェック
	if(!manager.sbus_data.is_receive){

		printf("SBUS_ERROR \n");
		return;
	}

	// IMUの通信チェック
	if(ImuInit() != 0){

		printf("IMU_ERROR \n");
		return;
	}

	// PreArmStateへの遷移
	manager.changeState(std::unique_ptr<FlightStateInterface>(std::make_unique<PreArmingState>()));
}

void InitState::enter(FlightManager& manager) {

	printf("FC start \n");

	//PWMの停止（安全のため）
	pwmStop();
}

void InitState::exit(FlightManager& manager) {

	// 赤LEDをつける
	redLed(PinState::on);
}
