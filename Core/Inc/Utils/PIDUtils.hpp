#ifndef PIDUTILS_HPP
#define PIDUTILS_HPP

#include <array>
#include "PID/PID.h"

class PIDUtils {
public:

    // インスタンス取得（初回のみPIDをセット）
    static PIDUtils& getInstance(PID* angle_pitch = nullptr, PID* angle_roll = nullptr,
                                 PID* rate_pitch = nullptr, PID* rate_roll = nullptr, PID* rate_yaw = nullptr) {
        static PIDUtils instance;
        if (angle_pitch && angle_roll && rate_pitch && rate_roll && rate_yaw) {
            instance.angle_pitch_ = angle_pitch;
            instance.angle_roll_  = angle_roll;
            instance.rate_pitch_  = rate_pitch;
            instance.rate_roll_   = rate_roll;
            instance.rate_yaw_    = rate_yaw;
        }
        return instance;
    }

    PIDUtils(const PIDUtils&) = delete;
    PIDUtils& operator=(const PIDUtils&) = delete;

    // 角度PID計算
    void anglePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target) {
        if (angle_pitch_ && angle_roll_) {
            angle_pitch_->calc(target[0], current[0]);
            angle_roll_->calc(target[1], current[1]);
        }
    }

    // 角速度PID計算
    void ratePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target) {
        if (rate_pitch_ && rate_roll_ && rate_yaw_) {
            rate_pitch_->calc(target[0], current[0]);
            rate_roll_->calc(target[1], current[1]);
            rate_yaw_->calc(target[2], current[2]);
        }
    }

    // 角度PID値取得
    void anglePIDGetData(std::array<float, 3>& target_rate) {
        if (angle_pitch_ && angle_roll_) {
            target_rate[0] = angle_pitch_->getData();
            target_rate[1] = angle_roll_->getData();
        }
    }

    // 角速度PID値取得
    void ratePIDGetData(std::array<float, 3>& rate) {
        if (rate_pitch_ && rate_roll_ && rate_yaw_) {
            rate[0] = rate_pitch_->getData();
            rate[1] = rate_roll_->getData();
            rate[2] = rate_yaw_->getData();
        }
    }

    // PIDリセット
    void pidReset() {
        if (angle_pitch_) angle_pitch_->reset();
        if (angle_roll_)  angle_roll_->reset();
        if (rate_pitch_)  rate_pitch_->reset();
        if (rate_roll_)   rate_roll_->reset();
        if (rate_yaw_)    rate_yaw_->reset();
    }

private:
    PIDUtils() = default;

    PID* angle_pitch_ = nullptr;
    PID* angle_roll_  = nullptr;
    PID* rate_pitch_  = nullptr;
    PID* rate_roll_   = nullptr;
    PID* rate_yaw_    = nullptr;
};

#endif // PIDUTILS_HPP