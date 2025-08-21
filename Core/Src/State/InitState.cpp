#include "State/Headers/FlightStates.h"

void InitState::update(FlightManager& manager) {

	// SBUSの受信チェック
	if(!manager.sbus_data.is_receive){

		printf("SBUS_ERROR \n");
		return;
	}

	// IMUの通信チェック
	if (manager.imuUtil) {

		if (manager.imuUtil->init() != 0) {

			printf("IMU_ERROR \n");
			return;
		}
	}

	// PreArmStateへの遷移
	manager.changeState(std::make_unique<PreArmingState>());
}

void InitState::enter(FlightManager& manager) {

	printf("FC start \n");

	//PWMの停止（安全のため）
	PwmStop();
}

void InitState::exit(FlightManager& manager) {

	// 赤LEDをつける
	redLed(PinState::on);
}
