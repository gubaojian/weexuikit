// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Macros for static thread-safety analysis.
//
// These are from http://clang.llvm.org/docs/ThreadSafetyAnalysis.html (and thus
// really derive from google3's thread_annotations.h).
//
// TODO(vtl): We're still using the old-fashioned, deprecated annotations
// ("locks" instead of "capabilities"), since the new ones don't work yet (in
// particular, |TRY_ACQUIRE()| doesn't work: b/19264527).
// https://github.com/domokit/mojo/issues/314

#ifndef WEEX_UIKIT_WML_SYNCHRONIZATION_THREAD_ANNOTATIONS_H_
#define WEEX_UIKIT_WML_SYNCHRONIZATION_THREAD_ANNOTATIONS_H_

#include "wml/build_config.h"

// Enable thread-safety attributes only with clang.
// The attributes can be safely erased when compiling with other compilers.
#if defined(__clang__) && !defined(OS_ANDROID)
#define WML_THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))
#else
#define WML_THREAD_ANNOTATION_ATTRIBUTE__(x)
#endif

#define WML_GUARDED_BY(x) WML_THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))

#define WML_PT_GUARDED_BY(x) WML_THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))

#define WML_ACQUIRE(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

#define WML_RELEASE(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define WML_ACQUIRED_AFTER(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))

#define WML_ACQUIRED_BEFORE(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))

#define WML_EXCLUSIVE_LOCKS_REQUIRED(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(exclusive_locks_required(__VA_ARGS__))

#define WML_SHARED_LOCKS_REQUIRED(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(shared_locks_required(__VA_ARGS__))

#define WML_LOCKS_EXCLUDED(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

#define WML_LOCK_RETURNED(x) WML_THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))

#define WML_LOCKABLE WML_THREAD_ANNOTATION_ATTRIBUTE__(lockable)

#define WML_SCOPED_LOCKABLE WML_THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)

#define WML_EXCLUSIVE_LOCK_FUNCTION(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(exclusive_lock_function(__VA_ARGS__))

#define WML_SHARED_LOCK_FUNCTION(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(shared_lock_function(__VA_ARGS__))

#define WML_ASSERT_EXCLUSIVE_LOCK(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(assert_exclusive_lock(__VA_ARGS__))

#define WML_ASSERT_SHARED_LOCK(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_lock(__VA_ARGS__))

#define WML_EXCLUSIVE_TRYLOCK_FUNCTION(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(exclusive_trylock_function(__VA_ARGS__))

#define WML_SHARED_TRYLOCK_FUNCTION(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(shared_trylock_function(__VA_ARGS__))

#define WML_UNLOCK_FUNCTION(...) \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(unlock_function(__VA_ARGS__))

#define WML_NO_THREAD_SAFETY_ANALYSIS \
  WML_THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)

// Use this in the header to annotate a function/method as not being
// thread-safe. This is equivalent to |WML_NO_THREAD_SAFETY_ANALYSIS|, but
// semantically different: it declares that the caller must abide by additional
// restrictions. Limitation: Unfortunately, you can't apply this to a method in
// an interface (i.e., pure virtual method) and have it applied automatically to
// implementations.
#define WML_NOT_THREAD_SAFE WML_NO_THREAD_SAFETY_ANALYSIS

#endif  // WEEX_UIKIT_WML_SYNCHRONIZATION_THREAD_ANNOTATIONS_H_
