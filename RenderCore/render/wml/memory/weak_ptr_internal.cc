// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wml/memory/weak_ptr_internal.h"

#include "wml/logging.h"

namespace wml {
namespace internal {

WeakPtrFlag::WeakPtrFlag() : is_valid_(true) {}

WeakPtrFlag::~WeakPtrFlag() {
  // Should be invalidated before destruction.
  WML_DCHECK_(!is_valid_);
}

void WeakPtrFlag::Invalidate() {
  // Invalidation should happen exactly once.
  WML_DCHECK_(is_valid_);
  is_valid_ = false;
}

}  // namespace internal
}  // namespace wml
