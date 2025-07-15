#include <iostream>
#include <tuple>

using namespace std;

enum class BatteryStatus {
    OK,
    TemperatureOutOfRange,
    SOCOutOfRange,
    ChargeRateOutOfRange
};

BatteryStatus checkBatteryStatus(float temperature, float soc, float chargeRate) {
    if (temperature < 0 || temperature > 45) {
        return BatteryStatus::TemperatureOutOfRange;
    }
    if (soc < 20 || soc > 80) {
        return BatteryStatus::SOCOutOfRange;
    }
    if (chargeRate > 0.8) {
        return BatteryStatus::ChargeRateOutOfRange;
    }
    return BatteryStatus::OK;
}

const char* statusToString(BatteryStatus status) {
    switch (status) {
        case BatteryStatus::OK: return "Battery is OK";
        case BatteryStatus::TemperatureOutOfRange: return "Temperature out of range!";
        case BatteryStatus::SOCOutOfRange: return "State of Charge out of range!";
        case BatteryStatus::ChargeRateOutOfRange: return "Charge Rate out of range!";
        default: return "Unknown status";
    }
}

int main() {
    auto status = checkBatteryStatus(25, 70, 0.7);
    cout << statusToString(status) << endl;

    status = checkBatteryStatus(50, 85, 0);
    cout << statusToString(status) << endl;

    return 0;
}
