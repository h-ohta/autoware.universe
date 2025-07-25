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

#ifndef OUT_OF_LANE_COLLISIONS_HPP_
#define OUT_OF_LANE_COLLISIONS_HPP_

#include "types.hpp"

#include <autoware/motion_velocity_planner_common/collision_checker.hpp>
#include <autoware/route_handler/route_handler.hpp>

#include <autoware_perception_msgs/msg/predicted_object.hpp>
#include <autoware_planning_msgs/msg/trajectory_point.hpp>

#include <vector>

namespace autoware::motion_velocity_planner::out_of_lane
{

/// @brief calculate the times and points where ego collides with an object's path outside of its
/// lane
void calculate_object_path_time_collisions(
  OutOfLaneData & out_of_lane_data, const size_t & object_path_id,
  const autoware_perception_msgs::msg::PredictedObject & object,
  const route_handler::RouteHandler & route_handler,
  const bool validate_predicted_paths_on_lanelets);

/// @brief calculate the times and points where ego collides with an object outside of its lane
void calculate_objects_time_collisions(
  OutOfLaneData & out_of_lane_data,
  const std::vector<autoware_perception_msgs::msg::PredictedObject> & objects,
  const route_handler::RouteHandler & route_handler, const PlannerParam & params);

/// @brief calculate the collisions to avoid
/// @details either uses the time to collision or just the time when the object will arrive at the
/// point
void calculate_collisions_to_avoid(
  OutOfLaneData & out_of_lane_data,
  const std::vector<autoware_planning_msgs::msg::TrajectoryPoint> & trajectory,
  const PlannerParam & params, const bool is_stopping = false);

/// @brief calculate the out of lane points
std::vector<OutOfLanePoint> calculate_out_of_lane_points(const EgoData & ego_data);

/// @brief prepare the rtree of out of lane points for the given data
void prepare_out_of_lane_areas_rtree(OutOfLaneData & out_of_lane_data);
}  // namespace autoware::motion_velocity_planner::out_of_lane

#endif  // OUT_OF_LANE_COLLISIONS_HPP_
