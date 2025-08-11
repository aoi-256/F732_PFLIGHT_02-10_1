## このリポジトリについて

このリポジトリは STM32CubeIDE 用プロジェクトの「Core」ディレクトリのみを提供します。利用する際は、プロジェクト直下に `Core/` を配置してください（既存プロジェクトの `Core/` を置き換え）。

– 対象MCU: STM32F732RE（例）
– IDE: STM32CubeIDE

## 配置手順（簡易）

1. STM32CubeIDE で任意の STM32F7 プロジェクトを作成
2. 生成されたプロジェクト直下にある既存の `Core/` を削除（またはバックアップ）
3. 本リポジトリの `Core/` をプロジェクト直下へコピー
4. ピン設定が一致しているか確認（LED: PC4, PB0, PB1 など）

## Core のディレクトリ構成

```
├── Core/                           # メインソースコード
│   ├── Inc/                        # ヘッダファイル
│   │   ├── main.h                  # メイン関数のヘッダ
│   │   ├── FlightManager.h         # フライト管理システム
│   │   ├── IMU.hpp                 # IMU制御ラッパ
│   │   ├── MadgwickAHRS_USER.hpp   # Madgwick姿勢推定カスタム
│   │   ├── PID_USER.hpp            # PIDカスタム設定
│   │   ├── PWM.hpp                 # PWM信号制御
│   │   ├── LED.hpp                 # LED制御（PC4=赤, PB0=黄, PB1=緑）
│   │   ├── wrapper.hpp             # C/C++ラッパー関数
│   │   ├── adc.h                   # ADC制御
│   │   ├── dma.h                   # DMA制御
│   │   ├── gpio.h                  # GPIO制御
│   │   ├── spi.h                   # SPI通信
│   │   ├── tim.h                   # タイマー制御
│   │   ├── usart.h                 # UART通信
│   │   ├── stm32f7xx_hal_conf.h    # HALライブラリ設定
│   │   ├── stm32f7xx_it.h          # 割り込みハンドラ
│   │   ├── FlightData/             # フライト用データ構造体
│   │   │   ├── ControlData.hpp
│   │   │   ├── SbusData.hpp
│   │   │   └── SensorData.hpp
│   │   └── State/                  # 状態管理（宣言/IF）
│   │       ├── Headers/
│   │       └── Interface/
│   │
│   ├── Src/                        # ソースファイル
│   │   ├── main.c                  # メイン関数
│   │   ├── FlightManager.cpp       # フライト管理実装
│   │   ├── PWM.cpp                 # PWM制御実装
│   │   ├── config.cpp              # PID/IMU/Madgwick 初期化
│   │   ├── wrapper.cpp             # ループ/割り込みのエントリ
│   │   ├── adc.c                   # ADC制御実装
│   │   ├── dma.c                   # DMA制御実装
│   │   ├── gpio.c                  # GPIO制御実装
│   │   ├── spi.c                   # SPI通信実装
│   │   ├── tim.c                   # タイマー制御実装
│   │   ├── usart.c                 # UART通信実装
│   │   ├── stm32f7xx_hal_msp.c     # HAL MSP設定
│   │   ├── stm32f7xx_it.c          # 割り込みハンドラ実装
│   │   ├── system_stm32f7xx.c      # システム初期化
│   │   └── State/                  # 各状態の実装
│   │       ├── AutoFlyState.cpp
│   │       ├── DisarmingState.cpp
│   │       ├── EmergencyControlState.cpp
│   │       ├── FailSafeState.cpp
│   │       ├── FlyingState.cpp
│   │       ├── InitState.cpp
│   │       └── PreFlightState.cpp
│   │
│   ├── Library/                    # 外部/汎用ライブラリ
│   │   ├── ICM42688P/              # IMUドライバ
│   │   │   ├── ICM42688P.h
│   │   │   ├── ICM42688P.cpp
│   │   │   ├── ICM42688P_HAL_SPI.h
│   │   │   └── ICM42688P_HAL_SPI.cpp
│   │   ├── MadgwickAHRS/
│   │   │   ├── MadgwickAHRS.h
│   │   │   └── MadgwickAHRS.cpp
│   │   ├── PID/
│   │   │   ├── PID.h
│   │   │   └── PID.cpp
│   │   └── Sbus/
│   │       ├── sbus.h
│   │       ├── sbus.cpp
│   │       ├── sbus_decoder.hpp
│   │       └── ringBuffer.h
│   │
│   └── Startup/                    # スタートアップ
│       └── startup_stm32f732retx.s
```

## LED と状態の対応表

LED 配線（`LED.hpp` 定義）
- 赤: PC4
- 黄: PB0
- 緑: PB1

操作 API（`LED.hpp`）
- redLed(PinState), yellowLed(PinState), greenLed(PinState)
- PinState: off / on / toggle

状態ごとの点灯タイミング（コード実装に基づく）

| 状態                   | タイミング        | LED動作                                     |
|------------------------|-------------------|---------------------------------------------|
| InitState              | 終了時            | 赤 LED ON（初期化完了の合図）               |
| PreArmingState         | 終了時            | 黄 LED ON（ARM/ESC初期化完了の合図）        |
| PreFlightState         | 終了時            | 緑 LED ON（飛行開始の合図）                 |
| FlyingState            | 開始時            | 変更なし（緑ON維持）                        |
| DisarmingState         | 終了時            | 黄/緑 LED OFF（DISARMの合図）               |
| FailSafeState          | 開始時（ループ） 　 | 赤/黄/緑を周期的にトグル（フェイルセーフ） |
| AutoFlyState           | —                 | なし                                        |
| EmergencyControlState  | —                 | なし                                        |

注意
- 上記は現行コードの enter/exit 実装に基づく点灯タイミングです。実際の視覚挙動は状態遷移のタイミングに依存します。
- フェイルセーフ状態では無限ループで3色をトグルし続けます。

## 補足
- `wrapper.cpp` で TIM6 割り込み（400Hz）によりメインループを進行し、UART5(DMA) で SBUS を受信します。
- `FlightManager` が状態遷移を管理し、`config.cpp` で PID と Madgwick の設定・初期化を行います。

