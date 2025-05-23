// -*- C++ -*-
//
// Copyright 2025 Dmitry Igrishin
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

#ifndef DMITIGR_BASE_UTILITY_HPP
#define DMITIGR_BASE_UTILITY_HPP

#include <chrono>
#include <utility>

namespace dmitigr {

template<class E, typename T>
T&& forward_or_throw(T&& value, const char* const what)
{
  if (value)
    return std::forward<T>(value);
  else
    throw E{what ? what : "dmitigr::forward_or_throw(value)"};
}

/// @returns `true` if instance of type `E` is thrown upon calling of `f`.
template<class E, typename F>
bool with_catch(const F& f) noexcept
{
  try {
    f();
  } catch (const E&) {
    return true;
  } catch (...) {}
  return false;
}

/// @returns The duration of call of `f`.
template<typename D = std::chrono::milliseconds, typename F>
auto with_measure(const F& f)
{
  namespace chrono = std::chrono;
  const auto start = chrono::high_resolution_clock::now();
  f();
  const auto end = chrono::high_resolution_clock::now();
  return chrono::duration_cast<D>(end - start);
}

} // namespace dmitigr

#endif  // DMITIGR_BASE_UTILITY_HPP
