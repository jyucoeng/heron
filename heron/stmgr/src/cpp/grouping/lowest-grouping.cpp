/*
 * Copyright 2015 Twitter, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "grouping/lowest-grouping.h"
#include <functional>
#include <iostream>
#include <list>
#include <vector>
#include "grouping/grouping.h"
#include "proto/messages.h"
#include "basics/basics.h"
#include "errors/errors.h"
#include "threads/threads.h"
#include "network/network.h"

namespace heron {
namespace stmgr {

LowestGrouping::LowestGrouping(const std::vector<sp_int32>& _task_ids) : Grouping(_task_ids) {
  lowest_taskid_ = _task_ids[0];
  for (sp_uint32 i = 1; i < _task_ids.size(); ++i) {
    if (lowest_taskid_ > _task_ids[i]) {
      lowest_taskid_ = _task_ids[i];
    }
  }
}

LowestGrouping::~LowestGrouping() {}

void LowestGrouping::GetListToSend(const proto::system::HeronDataTuple&,
                                   std::list<sp_int32>& _return) {
  _return.push_back(lowest_taskid_);
}

}  // namespace stmgr
}  // namespace heron
