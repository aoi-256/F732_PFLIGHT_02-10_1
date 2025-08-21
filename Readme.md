## このリポジトリについて

STM32のプロジェクトとしてひらいてください

## Core のディレクトリ構成

```
├── Core/
│   ├── Inc/
│   │   ├── FlightManager.h
│   │   ├── wrapper.hpp
│   │   ├── FlightData/
│   │   │   ├── ControlData.hpp
│   │   │   ├── SbusData.hpp
│   │   │   └── SensorData.hpp
│   │   ├── State/
│   │   │   ├── Headers/
│   │   │   └── Interface/
│   │   ├── UserSetting/
│   │   │   ├── MotorSetting.hpp
│   │   │   └── PIDSetting.hpp
│   │   ├── Utils/
│   │   │   ├── ICM42688P_SPI_Util.hpp
│   │   │   ├── LED.hpp
│   │   │   ├── PIDInit.hpp
│   │   │   ├── PIDUtils.hpp
│   │   │   ├── PWM.hpp
│   │   │   └── SbusDecoder.hpp
│   │   └── [STM32CubeIDE自動生成コード]
│   │       └── adc.h, dma.h, gpio.h, spi.h, tim.h, usart.h, stm32f7xx_hal_conf.h, stm32f7xx_it.h など
│   ├── Src/
│   │   ├── FlightManager.cpp
│   │   ├── wrapper.cpp
│   │   ├── State/
│   │   │   ├── AutoFlyState.cpp
│   │   │   ├── DisarmingState.cpp
│   │   │   ├── EmergencyControlState.cpp
│   │   │   ├── FailSafeState.cpp
│   │   │   ├── FlyingState.cpp
│   │   │   ├── InitState.cpp
│   │   │   ├── PreArmingState.cpp
│   │   │   └── PreFlightState.cpp
│   │   ├── Utils/
│   │   │   ├── ICM42688P_SPI_Util.cpp
│   │   │   ├── PIDInit.cpp
│   │   │   └── PWM.cpp
│   │   └── [STM32CubeIDE自動生成コード]
│   │       └── adc.c, dma.c, gpio.c, spi.c, tim.c, usart.c, stm32f7xx_hal_msp.c, stm32f7xx_it.c, system_stm32f7xx.c, syscalls.c, sysmem.c など
│   └── Startup/
│       └── startup_stm32f732retx.s
```


