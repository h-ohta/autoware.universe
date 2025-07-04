// Copyright 2020,2025 Tier IV, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file raspi_cpu_monitor.h
 * @brief Raspberry Pi CPU monitor class
 */

#ifndef SYSTEM_MONITOR__CPU_MONITOR__RASPI_CPU_MONITOR_HPP_
#define SYSTEM_MONITOR__CPU_MONITOR__RASPI_CPU_MONITOR_HPP_

#include "system_monitor/cpu_monitor/cpu_monitor_base.hpp"

#include <string>

#define raspiUnderVoltageDetected (1 << 0)              // 0x00001
#define raspiArmFrequencyCapped (1 << 1)                // 0x00002
#define raspiCurrentlyThrottled (1 << 2)                // 0x00004
#define raspiSoftTemperatureLimitActive (1 << 3)        // 0x00008
#define raspiUnderVoltageHasOccurred (1 << 16)          // 0x10000
#define raspiArmFrequencyCappedHasOccurred (1 << 17)    // 0x20000
#define raspiThrottlingHasOccurred (1 << 18)            // 0x40000
#define raspiSoftTemperatureLimitHasOccurred (1 << 19)  // 0x80000

#define raspiThermalThrottlingMask (raspiCurrentlyThrottled | raspiSoftTemperatureLimitActive)

#define throttledToString(X)                                                              \
  (((X) & raspiUnderVoltageDetected)              ? "Under-voltage detected"              \
   : ((X) & raspiArmFrequencyCapped)              ? "Arm frequency capped"                \
   : ((X) & raspiCurrentlyThrottled)              ? "Currently throttled"                 \
   : ((X) & raspiSoftTemperatureLimitActive)      ? "Soft temperature limit active"       \
   : ((X) & raspiUnderVoltageHasOccurred)         ? "Under-voltage has occurred"          \
   : ((X) & raspiArmFrequencyCappedHasOccurred)   ? "Arm frequency capped has occurred"   \
   : ((X) & raspiThrottlingHasOccurred)           ? "Throttling has occurred"             \
   : ((X) & raspiSoftTemperatureLimitHasOccurred) ? "Soft temperature limit has occurred" \
                                                  : "UNKNOWN")

class CPUMonitor : public CPUMonitorBase
{
public:
  /**
   * @brief constructor
   * @param [in] options Options associated with this node.
   */
  explicit CPUMonitor(const rclcpp::NodeOptions & options);

  /**
   * @brief constructor with node_name argument, required by TestCPUMonitor
   * @param [in] node_name The name of the node instance.
   * @param [in] options   Options associated with this node.
   */
  CPUMonitor(const std::string & node_name, const rclcpp::NodeOptions & options);

protected:
  /**
   * @brief get names for core temperature files
   */
  void getTemperatureFileNames() override;

  /**
   * @brief update CPU thermal throttling (implementation)
   */
  void checkThermalThrottling() override;

  /**
   * @brief update CPU thermal throttling (implementation)
   * @param [out] stat diagnostic message passed directly to diagnostic publish calls
   * @note NOLINT syntax is needed since diagnostic_updater asks for a non-const reference
   * to pass diagnostic message updated in this function to diagnostic publish calls.
   */
  void updateThermalThrottlingImpl(
    diagnostic_updater::DiagnosticStatusWrapper & stat) override;  // NOLINT(runtime/references)

  // The format of Thermal Throttling report depends on CPU model.
  // So, Thermal Throttling report is implemented in derived class.

  struct ThermalThrottlingData
  {
    float elapsed_ms;
    int summary_status;
    std::string summary_message;
    std::string error_key;
    std::string error_value;
    std::string status;

    void clear()
    {
      elapsed_ms = 0.0f;
      summary_status = 0;
      summary_message.clear();
      error_key.clear();
      error_value.clear();
      status.clear();
    }
  };

  ThermalThrottlingData thermal_throttling_data_;
};

#endif  // SYSTEM_MONITOR__CPU_MONITOR__RASPI_CPU_MONITOR_HPP_
