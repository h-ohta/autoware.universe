// Copyright 2024 TIER IV, Inc.
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

#ifndef OUT_OF_LANE_MODULE_HPP_
#define OUT_OF_LANE_MODULE_HPP_

#include "types.hpp"

#include <autoware/motion_utils/marker/virtual_wall_marker_creator.hpp>
#include <autoware/motion_velocity_planner_common/plugin_module_interface.hpp>
#include <autoware/motion_velocity_planner_common/velocity_planning_result.hpp>
#include <rclcpp/rclcpp.hpp>

#include <autoware_perception_msgs/msg/predicted_objects.hpp>
#include <geometry_msgs/msg/pose.hpp>

#include <lanelet2_core/LaneletMap.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace autoware::motion_velocity_planner
{
class OutOfLaneModule : public PluginModuleInterface
{
public:
  void init(rclcpp::Node & node, const std::string & module_name) override;
  void publish_planning_factor() override { planning_factor_interface_->publish(); };
  void update_parameters(const std::vector<rclcpp::Parameter> & parameters) override;
  VelocityPlanningResult plan(
    const std::vector<autoware_planning_msgs::msg::TrajectoryPoint> & raw_trajectory_points,
    const std::vector<autoware_planning_msgs::msg::TrajectoryPoint> & smoothed_trajectory_points,
    const std::shared_ptr<const PlannerData> planner_data) override;
  std::string get_module_name() const override { return module_name_; }
  RequiredSubscriptionInfo getRequiredSubscriptions() const override
  {
    RequiredSubscriptionInfo required_subscription_info;
    required_subscription_info.predicted_objects = true;
    return required_subscription_info;
  }

private:
  void init_parameters(rclcpp::Node & node);
  /// @brief resize the trajectory to start from the segment closest to ego and to have at most the
  /// given length
  static void limit_trajectory_size(
    out_of_lane::EgoData & ego_data,
    const std::vector<autoware_planning_msgs::msg::TrajectoryPoint> & smoothed_trajectory_points,
    const double max_arc_length);
  /// @brief calculate the first slowdown pose (if any)
  std::optional<geometry_msgs::msg::Pose> calculate_slowdown_pose(
    const out_of_lane::EgoData & ego_data, const out_of_lane::OutOfLaneData & out_of_lane_data);
  void update_slowdown_pose_buffer(
    const out_of_lane::EgoData & ego_data,
    const std::optional<geometry_msgs::msg::Pose> & slowdown_pose);
  /// @brief update the given planning result and some internal states of the module
  void update_result(
    VelocityPlanningResult & result, const std::optional<geometry_msgs::msg::Pose> & slowdown_pose,
    const out_of_lane::EgoData & ego_data, const out_of_lane::OutOfLaneData & out_of_lane_data);

  out_of_lane::PlannerParam params_{};

  inline static const std::string ns_ = "out_of_lane";
  std::string module_name_{"uninitialized"};
  rclcpp::Clock::SharedPtr clock_{nullptr};
  std::optional<geometry_msgs::msg::Pose> previous_slowdown_pose_{std::nullopt};
  std::vector<out_of_lane::SlowdownPose> slowdown_pose_buffer_;

protected:
  // Debug
  mutable out_of_lane::DebugData debug_data_{};
};
}  // namespace autoware::motion_velocity_planner

#endif  // OUT_OF_LANE_MODULE_HPP_
