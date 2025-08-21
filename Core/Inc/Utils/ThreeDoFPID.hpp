#ifndef THREEDOFPID_HPP
#define THREEDOFPID_HPP

#include <array>
#include "PID/PID.h"

class ThreeDoFPID {
public:
    static ThreeDoFPID& getInstance(PID* angle_pitch = nullptr, PID* angle_roll = nullptr,
                                 PID* rate_pitch = nullptr, PID* rate_roll = nullptr, PID* rate_yaw = nullptr) {
        static ThreeDoFPID instance;
        if (angle_pitch && angle_roll && rate_pitch && rate_roll && rate_yaw) {
            instance.angle_pitch_ = angle_pitch;
            instance.angle_roll_  = angle_roll;
            instance.rate_pitch_  = rate_pitch;
            instance.rate_roll_   = rate_roll;
            instance.rate_yaw_    = rate_yaw;
        }
        return instance;
    }

    ThreeDoFPID(const ThreeDoFPID&) = delete;
    ThreeDoFPID& operator=(const ThreeDoFPID&) = delete;

    void anglePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target) {
        if (angle_pitch_ && angle_roll_) {
            angle_pitch_->calc(target[0], current[0]);
            angle_roll_->calc(target[1], current[1]);
        }
    }

    void ratePIDCalc(const std::array<float, 3>& current, const std::array<float, 3>& target) {
        if (rate_pitch_ && rate_roll_ && rate_yaw_) {
            rate_pitch_->calc(target[0], current[0]);
            rate_roll_->calc(target[1], current[1]);
            rate_yaw_->calc(target[2], current[2]);
        }
    }

    void anglePIDGetData(std::array<float, 3>& target_rate) {
        if (angle_pitch_ && angle_roll_) {
            target_rate[0] = angle_pitch_->getData();
            target_rate[1] = angle_roll_->getData();
        }
    }

    void ratePIDGetData(std::array<float, 3>& rate) {
        if (rate_pitch_ && rate_roll_ && rate_yaw_) {
            rate[0] = rate_pitch_->getData();
            rate[1] = rate_roll_->getData();
            rate[2] = rate_yaw_->getData();
        }
    }

    void pidReset() {
        if (angle_pitch_) angle_pitch_->reset();
        if (angle_roll_)  angle_roll_->reset();
        if (rate_pitch_)  rate_pitch_->reset();
        if (rate_roll_)   rate_roll_->reset();
        if (rate_yaw_)    rate_yaw_->reset();
    }

private:
    ThreeDoFPID() = default;
    PID* angle_pitch_ = nullptr;
    PID* angle_roll_  = nullptr;
    PID* rate_pitch_  = nullptr;
    PID* rate_roll_   = nullptr;
    PID* rate_yaw_    = nullptr;
};

#endif // THREEDOFPID_HPP
