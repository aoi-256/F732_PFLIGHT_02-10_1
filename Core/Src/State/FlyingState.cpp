#include "State/Headers/FlightStates.h"

void FlyingState::update(FlightManager& manager) {

    // 飛行状態の更新処理を実装
	if(!manager.sbus_data.arm){

		manager.changeState(std::make_unique<DisarmingState>());
	}

	static uint8_t loop_count = 0;

	// センサーデータの取得
	ImuGetData(manager.sensor_data.accel, manager.sensor_data.gyro);

    // Madgickフィルターによる姿勢推定
    madgwickUpdate(manager.sensor_data.accel, manager.sensor_data.gyro);
    madgwickGetAngle(manager.sensor_data.angle);

    // センサー向きの調整
    float buf = manager.sensor_data.gyro[0];
    manager.sensor_data.gyro[0]  = manager.sensor_data.gyro[1];
    manager.sensor_data.gyro[1]  = buf;
    manager.sensor_data.gyro[2] *= -1;


    // 100hz 角度制御(pitch, roll)
    if(loop_count % 4 == 0){

    	// 目標角と現在角から目標角速度を計算
		anglePIDCalc(manager.sensor_data.angle, manager.sbus_data.target_value);
    	anglePIDGetData(manager.control_data.target_rate);

    	// yaw軸はセンサーデータを使用
    	manager.control_data.target_rate[2] = manager.sbus_data.target_value[2];
    }

    // 400hz 角速度制御
	//目標角速度と現在角速度(センサーデータ）から制御量を計算
	ratePIDCalc(manager.sensor_data.gyro, manager.control_data.target_rate);
	ratePIDGetData(manager.control_data.pid_result);

	// PID結果を各モーターに分配
	calcMotorPwm(manager.sbus_data.throttle, manager.control_data.pid_result, manager.control_data.motor_pwm);

	// Servoのpwmを生成
	uint16_t adc_value = 0;

	// adcの値を読む
	calcServoPwm(manager.sbus_data, adc_value, manager.control_data.servo_pwm);

	// PWMを生成
	pwmGenerate(manager.control_data.motor_pwm, manager.control_data.servo_pwm);

	// デバック用コード
	//printf("sbus_yaw: %lf \n", manager.sbus_data.target_value[2]);
	//printf("motorPwm: %4u, %4u, %4u, %4u \n", manager.control_data.motor_pwm[0], manager.control_data.motor_pwm[1], manager.control_data.motor_pwm[2], manager.control_data.motor_pwm[3]);
}

void FlyingState::enter(FlightManager& manager) {
    // TODO: 飛行状態への入場処理を実装



}

void FlyingState::exit(FlightManager& manager) {
    // TODO: 飛行状態からの退場処理を実装
}
