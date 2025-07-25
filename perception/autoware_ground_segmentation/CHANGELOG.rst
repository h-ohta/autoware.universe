^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package autoware_ground_segmentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.46.0 (2025-06-20)
-------------------
* Merge remote-tracking branch 'upstream/main' into tmp/TaikiYamada/bump_version_base
* feat(autoware_pointcloud_preprocessor): add diagnostic message (`#10579 <https://github.com/autowarefoundation/autoware_universe/issues/10579>`_)
  * feat: add diag msg
  * chore: fix code
  * chore: remove outlier count in ring
  * chore: move format timestamp to utility
  * chore: add paramter to schema
  * chore: add parameter for cluster
  * chore: clean code
  * chore: fix schema
  * chore: move diagnostic updater to filter base class
  * chore: fix schema
  * chore: fix spell error
  * chore: set up diagnostic updater
  * refactor: utilize autoware_utils diagnostic message
  * chore: add publish
  * chore: add detail message
  * chore: const for time difference
  * refactor: structure diagnostics to class
  * chore: const reference
  * chore: clean logic
  * chore: modify function name
  * chore: update parameter
  * chore: move evaluate status into diagnostic
  * chore: fix description for concatenated pointcloud
  * chore: timestamp mismatch threshold
  * chore: fix diagnostic key
  * chore: change function naming
  ---------
* fix(scan_ground_segmentation): separate parameter for recheck ignore distance (`#10686 <https://github.com/autowarefoundation/autoware_universe/issues/10686>`_)
  * fix(scan_ground_segmentation): fix recheck effective range
  * feat: separate param for recheck region
  * chore: docs and test update
  * chore: docs
  * chore: rename param
  * chore: fix schema
  ---------
* Contributors: TaikiYamada4, Yi-Hsiang Fang (Vivid), badai nguyen

0.45.0 (2025-05-22)
-------------------
* Merge remote-tracking branch 'origin/main' into tmp/notbot/bump_version_base
* fix(autoware_ground_segmentation): correct slope threshold global to local (`#10666 <https://github.com/autowarefoundation/autoware_universe/issues/10666>`_)
  * fix(grid_ground_filter): correct slope threshold global to local
  * Update perception/autoware_ground_segmentation/src/scan_ground_filter/grid_ground_filter.cpp
  Co-authored-by: badai nguyen  <94814556+badai-nguyen@users.noreply.github.com>
  * Update grid_ground_filter.cpp
  * fix(grid_ground_filter): update slope threshold from global to local
  ---------
  Co-authored-by: badai nguyen <94814556+badai-nguyen@users.noreply.github.com>
* chore: perception code owner update (`#10645 <https://github.com/autowarefoundation/autoware_universe/issues/10645>`_)
  * chore: update maintainers in multiple perception packages
  * Revert "chore: update maintainers in multiple perception packages"
  This reverts commit f2838c33d6cd82bd032039e2a12b9cb8ba6eb584.
  * chore: update maintainers in multiple perception packages
  * chore: add Kok Seang Tan as maintainer in multiple perception packages
  ---------
* docs(autoware_ground_segmentation): move parameter table to respective README (`#10500 <https://github.com/autowarefoundation/autoware_universe/issues/10500>`_)
* Contributors: Ryohsuke Mitsudome, Taekjin LEE, TaikiYamada4

0.44.2 (2025-06-10)
-------------------

0.44.1 (2025-05-01)
-------------------

0.44.0 (2025-04-18)
-------------------
* Merge remote-tracking branch 'origin/main' into humble
* refactor(ground_segmentation): rework parameter (`#8988 <https://github.com/autowarefoundation/autoware_universe/issues/8988>`_)
* perf(autoware_pointcloud_preprocessor): introduce managed transform buffer with implicitly defined listener type (`#9197 <https://github.com/autowarefoundation/autoware_universe/issues/9197>`_)
  * feat(autoware_universe_utils): rework managed transform buffer
  * feat(autoware_pointcloud_preprocessor): integrate Managed TF Buffer into pointcloud densifier
  * chore: update repos
  * chore(managed_transform_buffer): fix version
  ---------
  Co-authored-by: Kenzo Lobos-Tsunekawa <kenzo.lobos@tier4.jp>
* Contributors: Amadeusz Szymko, Prakash Kannaiah, Ryohsuke Mitsudome

0.43.0 (2025-03-21)
-------------------
* Merge remote-tracking branch 'origin/main' into chore/bump-version-0.43
* chore: rename from `autoware.universe` to `autoware_universe` (`#10306 <https://github.com/autowarefoundation/autoware_universe/issues/10306>`_)
* Contributors: Hayato Mizushima, Yutaka Kondo

0.42.0 (2025-03-03)
-------------------
* Merge remote-tracking branch 'origin/main' into tmp/bot/bump_version_base
* feat(autoware_utils): replace autoware_universe_utils with autoware_utils  (`#10191 <https://github.com/autowarefoundation/autoware_universe/issues/10191>`_)
* chore: refine maintainer list (`#10110 <https://github.com/autowarefoundation/autoware_universe/issues/10110>`_)
  * chore: remove Miura from maintainer
  * chore: add Taekjin-san to perception_utils package maintainer
  ---------
* Contributors: Fumiya Watanabe, Shunsuke Miura, 心刚

0.41.2 (2025-02-19)
-------------------
* chore: bump version to 0.41.1 (`#10088 <https://github.com/autowarefoundation/autoware_universe/issues/10088>`_)
* Contributors: Ryohsuke Mitsudome

0.41.1 (2025-02-10)
-------------------

0.41.0 (2025-01-29)
-------------------
* Merge remote-tracking branch 'origin/main' into tmp/bot/bump_version_base
* feat(autoware_ground_segmentation): tier4_debug_msgs changed to autoware_internal_debug_msgs in fil… (`#9878 <https://github.com/autowarefoundation/autoware_universe/issues/9878>`_)
  feat: tier4_debug_msgs changed to autoware_internal_debug_msgs in files perception/autoware_ground_segmentation
* fix(autoware_ground_segmentation): fix bugprone-branch-clone (`#9648 <https://github.com/autowarefoundation/autoware_universe/issues/9648>`_)
  fix: bugprone-branch-clone
* Contributors: Fumiya Watanabe, Vishal Chauhan, kobayu858

0.40.0 (2024-12-12)
-------------------
* Merge branch 'main' into release-0.40.0
* Revert "chore(package.xml): bump version to 0.39.0 (`#9587 <https://github.com/autowarefoundation/autoware_universe/issues/9587>`_)"
  This reverts commit c9f0f2688c57b0f657f5c1f28f036a970682e7f5.
* fix: fix ticket links in CHANGELOG.rst (`#9588 <https://github.com/autowarefoundation/autoware_universe/issues/9588>`_)
* chore(package.xml): bump version to 0.39.0 (`#9587 <https://github.com/autowarefoundation/autoware_universe/issues/9587>`_)
  * chore(package.xml): bump version to 0.39.0
  * fix: fix ticket links in CHANGELOG.rst
  * fix: remove unnecessary diff
  ---------
  Co-authored-by: Yutaka Kondo <yutaka.kondo@youtalk.jp>
* fix: fix ticket links in CHANGELOG.rst (`#9588 <https://github.com/autowarefoundation/autoware_universe/issues/9588>`_)
* fix(cpplint): include what you use - perception (`#9569 <https://github.com/autowarefoundation/autoware_universe/issues/9569>`_)
* fix(autoware_ground_segmentation): remove unused function (`#9536 <https://github.com/autowarefoundation/autoware_universe/issues/9536>`_)
* fix(autoware_ground_segmentation): fix clang-diagnostic-inconsistent-missing-override (`#9517 <https://github.com/autowarefoundation/autoware_universe/issues/9517>`_)
  * fix: clang-diagnostic-inconsistent-missing-override
  * fix: pre-commit error
  ---------
* feat(autoware_ground_segmentation): grid data structure revision for efficiency improvement (`#9297 <https://github.com/autowarefoundation/autoware_universe/issues/9297>`_)
  * fix: replace point index to data index
  * feat: Use emplace_back instead of push_back for adding gnd_grids in node.cpp
  * fix: prep for non-sorted grid process
  * feat: Add Cell class and Grid class for grid-based segmentation
  * refactor: Add Cell and Grid classes for grid-based segmentation
  * feat: initialize new grid
  * refactor: Update Grid class initialization to use radians for azimuth size
  refactor: Update Grid class initialization to use radians for azimuth size
  refactor: Update Grid class initialization to use radians for azimuth size
  * refactor: Fix calculation of azimuth index in Grid class
  * feat: implement grid based segmentation, temporary logic
  * refactor: idx position convert methods
  * refactor: Update Grid class initialization to use radians for azimuth size
  * feat: reconnect grids filled
  * feat: grid initialization
  * refactor: Update Grid class initialization and reset methods, implement a segmentation logic
  refactor: Update Grid class initialization and reset methods, implement a segmentation logic
  refactor: replace original methods
  * feat: add time_keeper
  * refactor: add time keeper in grid class
  refactor: remove previous scan ground grid
  * refactor: optimize grid boundary calculations and use squared values for radius comparisons
  * fix: use pointer for prev cell
  * refactor: remove time keeper called too many times
  * fix: radial idx estimation fix
  * refactor: optimize ground bin average calculation
  fix: ground bin logic fix
  * refactor: make grid ground filter separate
  * refactor: remove unused code
  fix: azimuth grid index converter bug
  * fix: segmentation logic determination fix
  fix: cell connection bug fix
  * refactor: optimize pseudoArcTan2 function
  * refactor: update grid radial calculation
  * refactor: contain input cloud ptr
  * refactor: separate ground initialization
  * refactor: Remove unused code and optimize grid radial calculation
  * refactor: Inline functions for improved performance
  * feat: various azimuth interval per radial distance
  * refactor: Fix bug in grid ground filter segmentation logic and cell connection
  Remove unused code and optimize grid radial calculation
  * fix: add missing offset calculation
  * refactor: Improve grid ground filter segmentation logic and cell connection
  Optimize grid radial calculation and remove unused code
  * refactor: Remove debug print statements and optimize grid initialization
  * refactor: Update grid radial limit to 200.0m
  * refactor: Update grid size to 0.5m for improved ground segmentation
  * refactor: Improve grid ground filter segmentation logic
  * refactor: Optimize grid ground filter segmentation logic
  * refactor: Update logic order for fast segmentation
  * fix: resolve cppcheck issue
  * fix: pseudo atan2 fix for even distribution of azimuth
  * fix: remove unused next_grid_idx\_ update
  * fix: introduce pseudo tangent to match result of pseudo arc tangent
  * style(pre-commit): autofix
  * fix: limit gradient
  * fix: bring previous average when the ground bin is empty
  * fix: back to constant azimuth interval grid
  * perf: remove division for efficiency
  * perf: remove division for efficiency
  * perf: contain radius and height to avoid double calculation
  * perf: optimize grid distance calculation for efficiency
  * style(pre-commit): autofix
  * perf: using isEmpty for efficiency
  * chore: initialization fix
  * perf:  initial ground cell is integrated into the classify method for efficiency
  * perf: refactor grid initialization for efficiency
  * perf: optimize grid cell linking for efficiency
  * Revert "perf:  initial ground cell is integrated into the classify method for efficiency"
  This reverts commit a4ab70b630f966d3e2827a07a0ec27079ecc78d2.
  * fix: fix pseudo atan2 bug
  * feat: various azimuth interval by range
  * perf: optimize pseudoArcTan2 function for efficiency
  * style(pre-commit): autofix
  * fix: avoid zero division on the slope estimation
  * fix: limit recursive search
  refactor: improve efficiency of recursiveSearch function
  Fix function parameter type in GridGroundFilter
  * refactor: add comments about unclassified case
  * chore: add comment to explain methods
  * refactor: remove unnecessary include statement
  * refactor: cast point_list size to int in getPointNum method
  * refactor: add index check in getCell method
  ---------
  Co-authored-by: pre-commit-ci[bot] <66853113+pre-commit-ci[bot]@users.noreply.github.com>
* 0.39.0
* update changelog
* fix: fix ticket links to point to https://github.com/autowarefoundation/autoware_universe (`#9304 <https://github.com/autowarefoundation/autoware_universe/issues/9304>`_)
* fix: fix ticket links to point to https://github.com/autowarefoundation/autoware_universe (`#9304 <https://github.com/autowarefoundation/autoware_universe/issues/9304>`_)
* chore(package.xml): bump version to 0.38.0 (`#9266 <https://github.com/autowarefoundation/autoware_universe/issues/9266>`_) (`#9284 <https://github.com/autowarefoundation/autoware_universe/issues/9284>`_)
  * unify package.xml version to 0.37.0
  * remove system_monitor/CHANGELOG.rst
  * add changelog
  * 0.38.0
  ---------
* Contributors: Esteve Fernandez, Fumiya Watanabe, M. Fatih Cırıt, Ryohsuke Mitsudome, Ryuta Kambe, Taekjin LEE, Yutaka Kondo, kobayu858

0.39.0 (2024-11-25)
-------------------
* fix: fix ticket links to point to https://github.com/autowarefoundation/autoware_universe (`#9304 <https://github.com/autowarefoundation/autoware_universe/issues/9304>`_)
* fix: fix ticket links to point to https://github.com/autowarefoundation/autoware_universe (`#9304 <https://github.com/autowarefoundation/autoware_universe/issues/9304>`_)
* chore(package.xml): bump version to 0.38.0 (`#9266 <https://github.com/autowarefoundation/autoware_universe/issues/9266>`_) (`#9284 <https://github.com/autowarefoundation/autoware_universe/issues/9284>`_)
  * unify package.xml version to 0.37.0
  * remove system_monitor/CHANGELOG.rst
  * add changelog
  * 0.38.0
  ---------
* Contributors: Esteve Fernandez, Yutaka Kondo

0.38.0 (2024-11-08)
-------------------
* unify package.xml version to 0.37.0
* feat(autoware_ground_segmentation): implementing linear least square fitting for local gradient calculation (`#9116 <https://github.com/autowarefoundation/autoware_universe/issues/9116>`_)
  * refactor: calculate local ground gradient in classifyPointCloudGridScan
  Calculate the local ground gradient by fitting a line to the ground grids in the classifyPointCloudGridScan function. This improves the accuracy of the gradient calculation and ensures more precise extrapolation of the ground height.
  * refactor: calculate local ground gradient in classifyPointCloudGridScan
  * refactor: update ground gradient calculation in classifyPointCloudGridScan function
  * style(pre-commit): autofix
  * chore: rename gradient variables
  * refactor: initialize all the member of the struct GridCenter
  * refactor: fix ground gradient calculation in checkContinuousGndGrid function
  ---------
  Co-authored-by: pre-commit-ci[bot] <66853113+pre-commit-ci[bot]@users.noreply.github.com>
* fix(autoware_ground_segmentation): fix scan ground filter logic  (`#9084 <https://github.com/autowarefoundation/autoware_universe/issues/9084>`_)
  * refactor: initialize gnd_grids in ScanGroundFilterComponent::initializeFirstGndGrids
  Initialize gnd_grids vector in the ScanGroundFilterComponent::initializeFirstGndGrids function to ensure it is empty and has the correct capacity. This improves the efficiency of the function and ensures accurate grid initialization.
  * refactor: initialize gnd_grids vector in initializeFirstGndGrids function
  Initialize the gnd_grids vector in the initializeFirstGndGrids function to ensure it is empty and has the correct capacity. This improves the efficiency of the function and ensures accurate grid initialization.
  * refactor: improve efficiency and accuracy of grid initialization
  Initialize the gnd_grids vector in the initializeFirstGndGrids function to ensure it is empty and has the correct capacity. This refactor improves the efficiency of the function and ensures accurate grid initialization.
  * refactor: improve efficiency of checkDiscontinuousGndGrid function
  Refactor the checkDiscontinuousGndGrid function in node.cpp to improve its efficiency. The changes include optimizing the conditional statements and reducing unnecessary calculations.
  * refactor: improve efficiency of checkDiscontinuousGndGrid function
  * fix: add missing condition
  * style(pre-commit): autofix
  * refactor: fix height_max initialization in node.hpp
  * fix: bring back inequality sign
  * fix: parameters from float to double
  following the guideline https://docs.ros.org/en/foxy/Concepts/About-ROS-2-Parameters.html#overview
  * refactor: fix logic description comment
  ---------
  Co-authored-by: pre-commit-ci[bot] <66853113+pre-commit-ci[bot]@users.noreply.github.com>
* chore(autoware_ground_segmentation): scan ground filter refactoring (`#9061 <https://github.com/autowarefoundation/autoware_universe/issues/9061>`_)
  * chore: Add comment classification logic for point cloud grid scan
  * chore: renamed horizontal angle to azimuth angle
  * chore: rename offset to data_index
  * chore: rename ground_cluster to centroid_bin
  chore: Refactor recheckGroundCluster function in scan_ground_filter
  * chore: rename too short variables
  * refactor: set input to be const
  * refactor: update functions to be const
  * chore: reorder params
  * refactor: Add ScanGroundGrid class for managing grid data
  * refactor: Update grid parameters and calculations in ScanGroundGrid class
  * refactor: remove unused methods
  * refactor: classification description
  * refactor: initialize members in ScanGroundGrid class
  * refactor: remove unused value
  * chore: reduce scope
  * refactor: align structure between convertPointcloud and convertPointcloudGridScan
  ---------
* feat(ground_segmentation): add time_keeper (`#8585 <https://github.com/autowarefoundation/autoware_universe/issues/8585>`_)
  * add time_keeper
  * add timekeeper option
  * add autoware_universe_utils
  * fix topic name
  * add scope and timekeeper
  * remove debug code
  * remove some timekeeper and mod block comment
  ---------
* fix(autoware_pointcloud_preprocessor): static TF listener as Filter option (`#8678 <https://github.com/autowarefoundation/autoware_universe/issues/8678>`_)
* fix(ground-segmentation): missing ament_index_cpp dependency (`#8587 <https://github.com/autowarefoundation/autoware_universe/issues/8587>`_)
* fix(autoware_ground_segmentation): fix unusedFunction (`#8566 <https://github.com/autowarefoundation/autoware_universe/issues/8566>`_)
  fix:unusedFunction
* fix(ground_segmentation): missing default parameters ERROR (`#8538 <https://github.com/autowarefoundation/autoware_universe/issues/8538>`_)
  fix(ground_segmentation): remove unused params
* fix(autoware_ground_segmentation): fix unreadVariable (`#8353 <https://github.com/autowarefoundation/autoware_universe/issues/8353>`_)
  * fix:unreadVariable
  * fix:unreadVariable
  ---------
* perf(autoware_pointcloud_preprocessor): lazy & managed TF listeners (`#8174 <https://github.com/autowarefoundation/autoware_universe/issues/8174>`_)
  * perf(autoware_pointcloud_preprocessor): lazy & managed TF listeners
  * fix(autoware_pointcloud_preprocessor): param names & reverse frames transform logic
  * fix(autoware_ground_segmentation): add missing TF listener
  * feat(autoware_ground_segmentation): change to static TF buffer
  * refactor(autoware_pointcloud_preprocessor): move StaticTransformListener to universe utils
  * perf(autoware_universe_utils): skip redundant transform
  * fix(autoware_universe_utils): change checks order
  * doc(autoware_universe_utils): add docstring
  ---------
* fix(autoware_ground_segmentation): fix uninitMemberVar (`#8336 <https://github.com/autowarefoundation/autoware_universe/issues/8336>`_)
  fix:uninitMemberVar
* fix(autoware_ground_segmentation): fix functionConst (`#8291 <https://github.com/autowarefoundation/autoware_universe/issues/8291>`_)
  fix:functionConst
* refactor(ground_segmentation)!: add package name prefix of autoware\_ (`#8135 <https://github.com/autowarefoundation/autoware_universe/issues/8135>`_)
  * refactor(ground_segmentation): add package name prefix of autoware\_
  * fix: update prefix cmake
  ---------
* Contributors: Amadeusz Szymko, Masaki Baba, Rein Appeldoorn, Taekjin LEE, Yutaka Kondo, badai nguyen, kobayu858

0.26.0 (2024-04-03)
-------------------
