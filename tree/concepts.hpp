
#pragma once

#ifndef __Concepts_hpp__
#define __Concepts_hpp__

#include <concepts>
#include <compare>

template <typename T>
concept copy_orderable = std::totally_ordered<T> && std::copyable<T>;

#endif
