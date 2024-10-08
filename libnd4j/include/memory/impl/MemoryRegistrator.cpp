/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// Created by raver119 on 07.10.2017.
//
#include <memory/MemoryRegistrator.h>

namespace sd {
namespace memory {

MemoryRegistrator::MemoryRegistrator() { _workspace = nullptr; };

MemoryRegistrator& MemoryRegistrator::getInstance() {
  static MemoryRegistrator instance;
  return instance;
}

bool MemoryRegistrator::hasWorkspaceAttached() { return _workspace != nullptr; }

Workspace* MemoryRegistrator::getWorkspace() { return _workspace; }

void MemoryRegistrator::attachWorkspace(Workspace* workspace) { _workspace = workspace; }

void MemoryRegistrator::forgetWorkspace() { _workspace = nullptr; }

void MemoryRegistrator::setGraphMemoryFootprint(LongType hash, LongType bytes) {
  _lock.lock();

  _footprint[hash] = bytes;

  _lock.unlock();
}

void MemoryRegistrator::setGraphMemoryFootprintIfGreater(LongType hash, LongType bytes) {
  _lock.lock();

  if (_footprint.count(hash) == 0)
    _footprint[hash] = bytes;
  else {
    LongType cv = _footprint[hash];
    if (bytes > cv) _footprint[hash] = bytes;
  }

  _lock.unlock();
}

LongType MemoryRegistrator::getGraphMemoryFootprint(LongType hash) {
  _lock.lock();

  LongType result = 0L;
  if (_footprint.count(hash) > 0) result = _footprint[hash];

  _lock.unlock();

  return result;
}
}  // namespace memory
}  // namespace sd
