#include <iostream>
#include <vector>
#include <functional>

using namespace std;

enum class BatteryStatus {
    OK,
    TemperatureOutOfRange,
    SOCOutOfRange,
    ChargeRateOutOfRange
};

struct BatteryCheck {
    function<bool(float, float, float)> condition;
    BatteryStatus status;
};

BatteryStatus checkBatteryStatus(float temperature, float soc, float chargeRate) {
    static const vector<BatteryCheck> checks = {
        { [](float t, float, float) { return t < 0 || t > 45; }, BatteryStatus::TemperatureOutOfRange },
        { [](float, float s, float) { return s < 20 || s > 80; }, BatteryStatus::SOCOutOfRange },
        { [](float, float, float c) { return c > 0.8; }, BatteryStatus::ChargeRateOutOfRange }
    };

    for (const auto& check : checks) {
        if (check.condition(temperature, soc, chargeRate)) {
            return check.status;
        }
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
