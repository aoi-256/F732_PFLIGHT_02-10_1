#pragma once
#include "state/interface/FlightStateInterface.h"
#include "FlightData/ControlData.hpp"
#include "FlightData/SbusData.hpp"
#include "FlightData/SensorData.hpp"
#include "UserSetting/PIDSetting.hpp"
#include "Utils/PIDInit.hpp"
#include "Utils/PIDUtils.hpp"
#include "Utils/ICM42688P_SPI_Util.hpp"
#include "MadgwickAHRS/src/MadgwickAHRS.h"
#include <memory>
#include <iostream>

// ループ管理構造体

struct FlightLoopManager{

    public:

        void setWaitFlag() {

            is_wait = true;
        }

        void clearWaitFlag() {

            is_wait = false;
        }

        bool isWait() const {

            return is_wait;
        }

    private:

        bool is_wait = false;
};

// フライト管理クラス
class FlightManager {

    public:

        FlightManager();
        ~FlightManager() = default;

        // 状態遷移
        void changeState(std::unique_ptr<FlightStateInterface> newState);
        
        // メインループ
        void update();

        // SBUSデータの更新（割り込み受信時に動作）
        void sbusUpdate(SbusChannelData sbus_data);

        bool checkSbusConnect();

        SensorData sensor_data;
        SbusChannelData sbus_data;
        ControlData control_data;

		PIDUtils* pidUtils;
		ICM42688P_SPI_Util* imuUtil;
		Madgwick madgwick;

    private:

    std::unique_ptr<FlightStateInterface> current_state;
    uint16_t sbus_lost_count = 0;

};
