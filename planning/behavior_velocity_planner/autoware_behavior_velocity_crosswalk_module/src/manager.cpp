// Copyright 2020 TIER IV, Inc.
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

#include "manager.hpp"

#include <autoware/behavior_velocity_planner_common/utilization/util.hpp>
#include <autoware_utils/ros/parameter.hpp>

#include <algorithm>
#include <limits>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace autoware::behavior_velocity_planner
{

using autoware_utils::get_or_declare_parameter;
using lanelet::autoware::Crosswalk;

CrosswalkModuleManager::CrosswalkModuleManager(rclcpp::Node & node)
: SceneModuleManagerInterfaceWithRTC(
    node, getModuleName(), getEnableRTC(node, std::string(getModuleName()) + ".common.enable_rtc"))
{
  const std::string ns(CrosswalkModuleManager::getModuleName());

  // for crosswalk parameters
  auto & cp = crosswalk_planner_param_;
  cp.show_processing_time =
    get_or_declare_parameter<bool>(node, ns + ".common.show_processing_time");

  // param for input data
  cp.traffic_light_state_timeout =
    get_or_declare_parameter<double>(node, ns + ".common.traffic_light_state_timeout");
  cp.lost_detection_timeout =
    get_or_declare_parameter<double>(node, ns + ".common.lost_detection_timeout");

  // param for stop position
  cp.stop_distance_from_crosswalk =
    get_or_declare_parameter<double>(node, ns + ".stop_position.stop_distance_from_crosswalk");
  cp.stop_distance_from_object_preferred = get_or_declare_parameter<double>(
    node, ns + ".stop_position.stop_distance_from_object_preferred");
  cp.stop_distance_from_crosswalk_limit = get_or_declare_parameter<double>(
    node, ns + ".stop_position.stop_distance_from_crosswalk_limit");
  cp.stop_position_threshold =
    get_or_declare_parameter<double>(node, ns + ".stop_position.stop_position_threshold");
  cp.min_acc_preferred =
    get_or_declare_parameter<double>(node, ns + ".stop_position.min_acc_preferred");
  cp.min_jerk_preferred =
    get_or_declare_parameter<double>(node, ns + ".stop_position.min_jerk_preferred");

  // param for restart suppression
  cp.min_dist_to_stop_for_restart_suppression =
    get_or_declare_parameter<double>(node, ns + ".restart_suppression.min_distance_to_stop");
  cp.max_dist_to_stop_for_restart_suppression =
    get_or_declare_parameter<double>(node, ns + ".restart_suppression.max_distance_to_stop");

  // param for ego velocity
  cp.min_slow_down_velocity =
    get_or_declare_parameter<double>(node, ns + ".slow_down.min_slow_down_velocity");
  cp.max_slow_down_jerk =
    get_or_declare_parameter<double>(node, ns + ".slow_down.max_slow_down_jerk");
  cp.max_slow_down_accel =
    get_or_declare_parameter<double>(node, ns + ".slow_down.max_slow_down_accel");
  cp.no_relax_velocity =
    get_or_declare_parameter<double>(node, ns + ".slow_down.no_relax_velocity");

  // param for obstruction prevention
  cp.enable_obstruction_prevention = get_or_declare_parameter<bool>(
    node, ns + ".obstruction_prevention.enable_obstruction_prevention");
  cp.target_vehicle_velocity =
    get_or_declare_parameter<double>(node, ns + ".obstruction_prevention.target_vehicle_velocity");
  cp.max_target_vehicle_lateral_offset = get_or_declare_parameter<double>(
    node, ns + ".obstruction_prevention.max_target_vehicle_lateral_offset");
  cp.required_clearance =
    get_or_declare_parameter<double>(node, ns + ".obstruction_prevention.required_clearance");
  cp.min_acc_for_target_vehicle =
    get_or_declare_parameter<double>(node, ns + ".obstruction_prevention.min_acc");
  cp.max_jerk_for_target_vehicle =
    get_or_declare_parameter<double>(node, ns + ".obstruction_prevention.max_jerk");
  cp.min_jerk_for_target_vehicle =
    get_or_declare_parameter<double>(node, ns + ".obstruction_prevention.min_jerk");

  // param for pass judge logic
  cp.ego_pass_first_margin_x =
    get_or_declare_parameter<std::vector<double>>(node, ns + ".pass_judge.ego_pass_first_margin_x");
  cp.ego_pass_first_margin_y =
    get_or_declare_parameter<std::vector<double>>(node, ns + ".pass_judge.ego_pass_first_margin_y");
  cp.ego_pass_first_additional_margin =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.ego_pass_first_additional_margin");
  cp.ego_pass_later_margin_x =
    get_or_declare_parameter<std::vector<double>>(node, ns + ".pass_judge.ego_pass_later_margin_x");
  cp.ego_pass_later_margin_y =
    get_or_declare_parameter<std::vector<double>>(node, ns + ".pass_judge.ego_pass_later_margin_y");
  cp.ego_pass_later_additional_margin =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.ego_pass_later_additional_margin");
  cp.ego_min_assumed_speed =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.ego_min_assumed_speed");
  cp.consider_obj_on_crosswalk_on_red_light =
    get_or_declare_parameter<bool>(node, ns + ".pass_judge.consider_obj_on_crosswalk_on_red_light");
  cp.enable_no_stop_decision = get_or_declare_parameter<bool>(
    node, ns + ".pass_judge.no_stop_decision.enable_no_stop_decision");
  cp.min_acc_for_no_stop_decision =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.no_stop_decision.min_acc");
  cp.min_jerk_for_no_stop_decision =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.no_stop_decision.min_jerk");
  cp.stop_object_velocity =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.stop_object_velocity_threshold");
  cp.min_object_velocity =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.min_object_velocity");
  cp.disable_yield_for_new_stopped_object =
    get_or_declare_parameter<bool>(node, ns + ".pass_judge.disable_yield_for_new_stopped_object");
  cp.distance_set_for_no_intention_to_walk = get_or_declare_parameter<std::vector<double>>(
    node, ns + ".pass_judge.distance_set_for_no_intention_to_walk");
  cp.timeout_set_for_no_intention_to_walk = get_or_declare_parameter<std::vector<double>>(
    node, ns + ".pass_judge.timeout_set_for_no_intention_to_walk");
  cp.timeout_ego_stop_for_yield =
    get_or_declare_parameter<double>(node, ns + ".pass_judge.timeout_ego_stop_for_yield");

  // param for target area & object
  cp.crosswalk_attention_range =
    get_or_declare_parameter<double>(node, ns + ".object_filtering.crosswalk_attention_range");
  cp.vehicle_object_cross_angle_threshold = get_or_declare_parameter<double>(
    node, ns + ".object_filtering.vehicle_object_cross_angle_threshold");
  cp.look_unknown =
    get_or_declare_parameter<bool>(node, ns + ".object_filtering.target_object.unknown");
  cp.look_bicycle =
    get_or_declare_parameter<bool>(node, ns + ".object_filtering.target_object.bicycle");
  cp.look_motorcycle =
    get_or_declare_parameter<bool>(node, ns + ".object_filtering.target_object.motorcycle");
  cp.look_pedestrian =
    get_or_declare_parameter<bool>(node, ns + ".object_filtering.target_object.pedestrian");

  // param for occlusions
  cp.occlusion_enable = get_or_declare_parameter<bool>(node, ns + ".occlusion.enable");
  cp.occlusion_occluded_object_velocity =
    get_or_declare_parameter<double>(node, ns + ".occlusion.occluded_object_velocity");
  cp.occlusion_slow_down_velocity =
    get_or_declare_parameter<float>(node, ns + ".occlusion.slow_down_velocity");
  cp.occlusion_time_buffer = get_or_declare_parameter<double>(node, ns + ".occlusion.time_buffer");
  cp.occlusion_min_size = get_or_declare_parameter<double>(node, ns + ".occlusion.min_size");
  cp.occlusion_free_space_max =
    get_or_declare_parameter<int>(node, ns + ".occlusion.free_space_max");
  cp.occlusion_occupied_min = get_or_declare_parameter<int>(node, ns + ".occlusion.occupied_min");
  cp.occlusion_ignore_with_traffic_light =
    get_or_declare_parameter<bool>(node, ns + ".occlusion.ignore_with_traffic_light");
  cp.occlusion_ignore_behind_predicted_objects =
    get_or_declare_parameter<bool>(node, ns + ".occlusion.ignore_behind_predicted_objects");

  cp.occlusion_ignore_velocity_thresholds.resize(
    autoware_perception_msgs::msg::ObjectClassification::PEDESTRIAN + 1,
    get_or_declare_parameter<double>(node, ns + ".occlusion.ignore_velocity_thresholds.default"));
  const auto get_label = [](const std::string & s) {
    if (s == "CAR") return autoware_perception_msgs::msg::ObjectClassification::CAR;
    if (s == "TRUCK") return autoware_perception_msgs::msg::ObjectClassification::TRUCK;
    if (s == "BUS") return autoware_perception_msgs::msg::ObjectClassification::BUS;
    if (s == "TRAILER") return autoware_perception_msgs::msg::ObjectClassification::TRAILER;
    if (s == "MOTORCYCLE") return autoware_perception_msgs::msg::ObjectClassification::MOTORCYCLE;
    if (s == "BICYCLE") return autoware_perception_msgs::msg::ObjectClassification::BICYCLE;
    if (s == "PEDESTRIAN") return autoware_perception_msgs::msg::ObjectClassification::PEDESTRIAN;
    return autoware_perception_msgs::msg::ObjectClassification::UNKNOWN;
  };
  const auto custom_labels = get_or_declare_parameter<std::vector<std::string>>(
    node, ns + ".occlusion.ignore_velocity_thresholds.custom_labels");
  const auto custom_velocities = get_or_declare_parameter<std::vector<double>>(
    node, ns + ".occlusion.ignore_velocity_thresholds.custom_thresholds");
  for (auto idx = 0UL; idx < std::min(custom_labels.size(), custom_velocities.size()); ++idx) {
    cp.occlusion_ignore_velocity_thresholds[get_label(custom_labels[idx])] = custom_velocities[idx];
  }
  cp.occlusion_extra_objects_size =
    get_or_declare_parameter<double>(node, ns + ".occlusion.extra_predicted_objects_size");

  // param for parked vehicles stop
  cp.parked_vehicles_stop_enable =
    get_or_declare_parameter<bool>(node, ns + ".parked_vehicles_stop.enable");
  cp.parked_vehicles_stop_search_distance =
    get_or_declare_parameter<double>(node, ns + ".parked_vehicles_stop.search_distance");
  cp.parked_vehicles_stop_min_ego_stop_duration =
    get_or_declare_parameter<double>(node, ns + ".parked_vehicles_stop.min_ego_stop_duration");
  cp.parked_vehicles_stop_parked_ego_inside_safe_area_margin = get_or_declare_parameter<double>(
    node, ns + ".parked_vehicles_stop.ego_inside_safe_area_margin");
  cp.parked_vehicles_stop_parked_velocity_threshold =
    get_or_declare_parameter<double>(node, ns + ".parked_vehicles_stop.parked_velocity_threshold");
  cp.parked_vehicles_stop_vehicle_permanence_duration = get_or_declare_parameter<double>(
    node, ns + ".parked_vehicles_stop.vehicle_permanence_duration");
}

void CrosswalkModuleManager::launchNewModules(const PathWithLaneId & path)
{
  const auto rh = planner_data_->route_handler_;

  const auto launch = [this, &path](
                        const auto road_lanelet_id, const auto crosswalk_lanelet_id,
                        const std::optional<int64_t> & reg_elem_id) {
    if (isModuleRegistered(crosswalk_lanelet_id)) {
      return;
    }

    const auto & p = crosswalk_planner_param_;
    const auto logger = logger_.get_child("crosswalk_module");
    const auto lanelet_map_ptr = planner_data_->route_handler_->getLaneletMapPtr();

    // NOTE: module_id is always a lane id so that isModuleRegistered works correctly in the case
    //       where both regulatory element and non-regulatory element crosswalks exist.
    registerModule(
      std::make_shared<CrosswalkModule>(
        node_, road_lanelet_id, crosswalk_lanelet_id, reg_elem_id, lanelet_map_ptr, p, logger,
        clock_, time_keeper_, planning_factor_interface_));
    generate_uuid(crosswalk_lanelet_id);
    updateRTCStatus(
      getUUID(crosswalk_lanelet_id), true, State::WAITING_FOR_EXECUTION,
      std::numeric_limits<double>::lowest(), path.header.stamp);
  };

  const auto crosswalk_reg_elem_map = planning_utils::getRegElemMapOnPath<Crosswalk>(
    path, rh->getLaneletMapPtr(), planner_data_->current_odometry->pose);

  for (const auto & crosswalk : crosswalk_reg_elem_map) {
    // NOTE: The former id is a lane id, and the latter one is a regulatory element's id.
    launch(crosswalk.second.id(), crosswalk.first->crosswalkLanelet().id(), crosswalk.first->id());
  }

  const auto crosswalk_lanelets = getCrosswalksOnPath(
    planner_data_->current_odometry->pose, path, rh->getLaneletMapPtr(), rh->getOverallGraphPtr());

  for (const auto & crosswalk : crosswalk_lanelets) {
    launch(crosswalk.first, crosswalk.second.id(), std::nullopt);
  }
}

std::function<bool(const std::shared_ptr<SceneModuleInterfaceWithRTC> &)>
CrosswalkModuleManager::getModuleExpiredFunction(const PathWithLaneId & path)
{
  const auto rh = planner_data_->route_handler_;

  std::set<int64_t> crosswalk_id_set;

  crosswalk_id_set = getCrosswalkIdSetOnPath(
    planner_data_->current_odometry->pose, path, rh->getLaneletMapPtr(), rh->getOverallGraphPtr());

  const auto crosswalk_reg_elem_map = planning_utils::getRegElemMapOnPath<Crosswalk>(
    path, rh->getLaneletMapPtr(), planner_data_->current_odometry->pose);

  for (const auto & crosswalk : crosswalk_reg_elem_map) {
    crosswalk_id_set.insert(crosswalk.first->crosswalkLanelet().id());
  }

  return [crosswalk_id_set](const std::shared_ptr<SceneModuleInterfaceWithRTC> & scene_module) {
    return crosswalk_id_set.count(scene_module->getModuleId()) == 0;
  };
}
}  // namespace autoware::behavior_velocity_planner

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(
  autoware::behavior_velocity_planner::CrosswalkModulePlugin,
  autoware::behavior_velocity_planner::PluginInterface)
