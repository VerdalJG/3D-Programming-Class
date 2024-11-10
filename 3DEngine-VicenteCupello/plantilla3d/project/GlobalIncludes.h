#pragma once
#include <xstring>
#include <vector>
#include <memory>


// General alias for std::shared_ptr
template<typename T>
using SharedPtr = std::shared_ptr<T>;

// General alias for std::unique_ptr (optional)
template<typename T>
using UniquePtr = std::unique_ptr<T>;

// General alias for std::weak_ptr (optional)
template<typename T>
using WeakPtr = std::weak_ptr<T>;