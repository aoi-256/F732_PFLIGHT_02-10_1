#include "FlightManager.h"
#include "state/headers/FlightStates.h"
#include <iomanip>
#include <cstring>

// コンストラクタ
FlightManager::FlightManager() {

    // 初期状態をInitStateに設定
    currentState = std::make_unique<InitState>();
    currentState->enter(*this);
}

// 状態更新
void FlightManager::changeState(std::unique_ptr<FlightStateInterface> newState) {

    if (currentState) {
        currentState->exit(*this);
    }

    currentState = std::move(newState);
    
    // 状態名をprintfで出力
    if (currentState) {
        printf("[FlightManager] 状態遷移: %s\n", currentState->getStateName());
    }
    currentState->enter(*this);
}

// 状態呼び出し
void FlightManager::update() {

    // SBUS接続チェック（Init状態の時以外）
    if (currentState && std::strcmp(currentState->getStateName(), "InitState") != 0) {

        // SBUSのタイムアウトチェック用
        sbus_lost_count ++;

        if (!checkSbusConnect()) {

            changeState(std::make_unique<FailSafeState>());
            return;
        }
    }

    if (currentState) {
        currentState->update(*this);
    }
}

// SBUS更新
void FlightManager::sbusUpdate(SbusChannelData sbus_data){

	this->sbus_data = sbus_data;
	sbus_lost_count = 0;
}

// SBUS接続チェック
bool FlightManager::checkSbusConnect(){

	if(sbus_data.failsafe_bit || (sbus_lost_count > 1000)){

		return false;
	}

	return true;
}
