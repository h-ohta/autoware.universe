// Copyright 2020 Tier IV, Inc.
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

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <boost/optional.hpp>

#include <memory>
#include <utility>
#include <vector>

#define EIGEN_MPL2_ONLY
#include <Eigen/Core>
#include <autoware/behavior_velocity_planner_common/utilization/boost_geometry_helper.hpp>
#include <autoware/behavior_velocity_rtc_interface/scene_module_interface_with_rtc.hpp>
#include <autoware_lanelet2_extension/regulatory_elements/detection_area.hpp>
#include <rclcpp/rclcpp.hpp>

#include <lanelet2_core/LaneletMap.h>
#include <tf2/LinearMath/Transform.h>

namespace autoware::behavior_velocity_planner
{
using PathIndexWithPose = std::pair<size_t, geometry_msgs::msg::Pose>;  // front index, pose
using PathIndexWithPoint2d = std::pair<size_t, Point2d>;                // front index, point2d
using PathIndexWithOffset = std::pair<size_t, double>;                  // front index, offset
using autoware_internal_planning_msgs::msg::PathWithLaneId;

class DetectionAreaModule : public SceneModuleInterfaceWithRTC
{
public:
  enum class State { GO, STOP };

  struct DebugData
  {
    double base_link2front;
    std::vector<geometry_msgs::msg::Pose> stop_poses;
    std::vector<geometry_msgs::msg::Pose> dead_line_poses;
    geometry_msgs::msg::Pose first_stop_pose;
    std::vector<geometry_msgs::msg::Point> obstacle_points;
  };

  struct PlannerParam
  {
    double stop_margin;
    bool use_dead_line;
    double dead_line_margin;
    bool use_max_acceleration;
    double max_acceleration;
    bool use_pass_judge_line;
    double state_clear_time;
    double hold_stop_margin_distance;
    double distance_to_judge_over_stop_line;
    bool suppress_pass_judge_when_stopping;
    bool enable_detected_obstacle_logging;
  };

  DetectionAreaModule(
    const int64_t module_id, const int64_t lane_id,
    const lanelet::autoware::DetectionArea & detection_area_reg_elem,
    const PlannerParam & planner_param, const rclcpp::Logger & logger,
    const rclcpp::Clock::SharedPtr clock,
    const std::shared_ptr<autoware_utils::TimeKeeper> time_keeper,
    const std::shared_ptr<planning_factor_interface::PlanningFactorInterface>
      planning_factor_interface);

  bool modifyPathVelocity(PathWithLaneId * path) override;

  visualization_msgs::msg::MarkerArray createDebugMarkerArray() override;
  autoware::motion_utils::VirtualWalls createVirtualWalls() override;

  std::vector<int64_t> getRegulatoryElementIds() const override
  {
    return {detection_area_reg_elem_.id()};
  }
  std::vector<int64_t> getLaneletIds() const override { return {lane_id_}; }
  std::vector<int64_t> getLineIds() const override
  {
    return {detection_area_reg_elem_.stopLine().id()};
  }

private:
  // Lane id
  int64_t lane_id_;

  // Key Feature
  const lanelet::autoware::DetectionArea & detection_area_reg_elem_;

  // State
  State state_;
  std::shared_ptr<const rclcpp::Time> last_obstacle_found_time_;
  double forward_offset_to_stop_line_{0.0};

  // Parameter
  PlannerParam planner_param_;

  // Debug
  DebugData debug_data_;

  /**
   * @brief Print positions of detected obstacle, time elapsed since last detection, and ego vehicle
   * position
   * @param obstacle_points Points representing detected obstacles in the detection area
   * @param self_pose Current pose of the ego vehicle
   */
  void print_detected_obstacle(
    const std::vector<geometry_msgs::msg::Point> & obstacle_points,
    const geometry_msgs::msg::Pose & self_pose) const;
};
}  // namespace autoware::behavior_velocity_planner

#endif  // SCENE_HPP_
