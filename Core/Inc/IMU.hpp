#ifndef INC_IMU_HPP_
#define INC_IMU_HPP_

#include <cstdint>
#include <gpio.h>
#include "ICM42688P/ICM42688P_HAL_SPI.h"
#include <algorithm>  // std::copy用


ICM42688P_HAL_SPI icm(&hspi1, GPIOA, GPIO_PIN_4);

uint8_t ImuInit(){

	//通信チェック
	if(icm.Connection() == 1){

		return 1;
	}

	icm.AccelConfig(icm.ACCEL_Mode::LowNoize, icm.ACCEL_SCALE::SCALE02g, icm.ACCEL_ODR::ODR01000hz, icm.ACCEL_DLPF::ODR40);

	HAL_Delay(10);

	icm.GyroConfig(icm.GYRO_MODE::LowNoize, icm.GYRO_SCALE::Dps0250, icm.GYRO_ODR::ODR01000hz, icm.GYRO_DLPF::ODR40);

	HAL_Delay(10);

	uint8_t calibration_error = icm.Calibration(1000);

	//通信エラー
	if(calibration_error == 1){

		return 1;
	}
	//振動が大きすぎる場合
	else if(calibration_error == 2){

		return 2;
	}

	HAL_Delay(10);

	return 0;
}

uint8_t ImuGetData(std::array<float, 3>& accel_data, std::array<float, 3>& gyro_data){

    float accel[3] = {};
    float gyro[3]  = {};

    uint8_t result = icm.GetData(accel, gyro);

    for(uint8_t i = 0; i < 3; i++){
        accel_data[i] = accel[i];
        gyro_data[i] = gyro[i];
    }

    return result;
}

#endif
