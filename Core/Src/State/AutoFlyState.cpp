#include "State/Headers/FlightStates.h"

void AutoFlyState::update(FlightManager& manager) {

    // ループカウント
	static uint32_t loop_count = 0;
	loop_count++;

    // Armのチェック
	if(!manager.sbus_data.arm){

		manager.changeState(std::make_unique<DisarmingState>());
	}

    // 通常飛行への復帰
    if(!manager.sbus_data.emergency_control){

		manager.changeState(std::make_unique<FlyingState>());
	}

    // 目標角データの取得(仮で0)
    // Todo: データ取得機構とデコードの機構の実装
    manager.sbus_data.target_value[0] = 0.0f; //target_angle_x
    manager.sbus_data.target_value[1] = 0.0f; //target_angle_y
    manager.sbus_data.target_value[2] = 0.0f; //target_rate_z

	// Madgwickフィルターでの姿勢推定
	manager.madgwick.updateIMU(

		manager.sensor_data.gyro[0], manager.sensor_data.gyro[1], manager.sensor_data.gyro[2],
		manager.sensor_data.accel[0], manager.sensor_data.accel[1], manager.sensor_data.accel[2]
	);

	// 推定データの取得
	manager.sensor_data.angle[0] = manager.madgwick.getPitch();
	manager.sensor_data.angle[1] = manager.madgwick.getRoll();
	manager.sensor_data.angle[2] = manager.madgwick.getYaw();

    // センサー向きの調整
    float buf = manager.sensor_data.gyro[0];
    manager.sensor_data.gyro[0]  = manager.sensor_data.gyro[1];
    manager.sensor_data.gyro[1]  = buf;
    manager.sensor_data.gyro[2] *= -1;


    // 100hz 角度制御(pitch, roll)
    if(loop_count % 4 == 0){

    	// 目標角と現在角から目標角速度を計算
		if (manager.threedofpid) {

			manager.threedofpid->anglePIDCalc(manager.sensor_data.angle, manager.sbus_data.target_value);
			manager.threedofpid->anglePIDGetData(manager.control_data.target_rate);
		}

    	// yaw軸はセンサーデータを使用
        manager.control_data.target_rate[2] = manager.sbus_data.target_value[2];
    }

    // 400hz 角速度制御
	//目標角速度と現在角速度(センサーデータ）から制御量を計算
	if (manager.threedofpid) {

		manager.threedofpid->ratePIDCalc(manager.sensor_data.gyro, manager.control_data.target_rate);
		manager.threedofpid->ratePIDGetData(manager.control_data.pid_result);
	}

	// PID結果を各モーターに分配
	PwmCalcMotor(manager.sbus_data.throttle, manager.control_data.pid_result, manager.control_data.motor_pwm);

	// PWMを生成
	PwmGenerate(manager.control_data.motor_pwm, manager.control_data.servo_pwm);
}

void AutoFlyState::enter(FlightManager& manager) {
    
    // Todo: LEDをつける
}

void AutoFlyState::exit(FlightManager& manager) {

    // Todo: LEDを消す
}
