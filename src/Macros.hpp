#pragma once

#include <memory>

#define SMART_PTRS(type)                                                                           \
  using Ref = std::shared_ptr<type>;                                                               \
  template <typename... Args> static Ref New(Args&&... CtorArgs) {                                 \
    return std::move(std::make_shared<type>(std::forward<Args>(CtorArgs)...));                     \
  }
