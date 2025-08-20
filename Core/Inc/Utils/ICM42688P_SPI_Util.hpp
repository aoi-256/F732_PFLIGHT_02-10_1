#pragma once

#include <cstdint>
#include <array>
#include <gpio.h>
#include "ICM42688P/ICM42688P_HAL_SPI.h"

class ICM42688P_SPI_Util {
public:
    ICM42688P_SPI_Util(SPI_HandleTypeDef* hspi, GPIO_TypeDef* csPort, uint16_t csPin);

    uint8_t init();
    uint8_t getData(std::array<float, 3>& accel_data, std::array<float, 3>& gyro_data);

private:
    ICM42688P_HAL_SPI icm;
};