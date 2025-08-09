#include "IMU.hpp"

// HALのハンドル(hspi1)はCで定義されているのでCリンケージで参照
extern "C" {
#include "spi.h"
#include "gpio.h"
}

// IMUインスタンスの実体定義（CS: GPIOA PIN_4）
ICM42688P_HAL_SPI icm(&hspi1, GPIOA, GPIO_PIN_4);