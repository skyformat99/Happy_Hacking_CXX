// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// Happy Hacking CXX Library (https://github.com/Lingxi-Li/Happy_Hacking_CXX)

#ifndef HHXX_MULTI_VIEW_HPP_
#define HHXX_MULTI_VIEW_HPP_

#include <cassert>
#include <cstddef>

#include <algorithm>
#include <initializer_list>
#include <tuple>
#include <type_traits>
#include <utility>

namespace hhxx {

/// Provides a multi-dimensional view of a one-dimensional linear range. The
/// linear range can then be accessed in a multi-dimensional fashion. `Iterator`
/// specifies the iterator type used to denote the linear range.

template <typename Iterator>
class multi_view {
public:
  /// Maximum number of dimensions supported.
  static constexpr std::size_t max_dim = 10;

  /// `base` is an iterator denoting a one-dimensional linear range. `extents...`
  /// specifies the extent of each dimension of the multi-dimensional view.
  /// So, `sizeof...(extents)` is the number of dimensions.
  template <typename... Ts>
  multi_view(Iterator base, Ts... extents)
      : base_(base) {
    constexpr auto n = sizeof...(extents);
    static_assert(0 < n && n <= max_dim, "");
    auto init_list = { extents... };
    std::copy(init_list.begin(), init_list.end(), steps_);
    auto i = n - 1;
    std::size_t acc = 1;
    do {
      acc *= std::exchange(steps_[i], acc);
    }
    while (i-- > 0);
    assert(acc);
    num_elements_ = acc;
  }

  /// Returns a begin iterator of the sub-object at `indices...`. An empty set of
  /// `indices` returns a begin iterator of the multi-dimensional object itself.

  template <typename... Ts>
  auto begin() const {
    return base_;
  }

  template <typename... Ts>
  auto begin(Ts... indices) const {
    auto idxes = std::begin({ indices... });
    std::size_t offset = 0;
    for (std::size_t i = 0; i < sizeof...(indices) && steps_[i]; ++i) {
      assert(idxes[i] >= 0);
      offset += idxes[i] * steps_[i];
    }
    return (base_ + offset);
  }

  /// Returns an end iterator of the sub-object at `indices...`. An empty set of
  /// `indices` returns an end iterator of the multi-dimensional object itself.

  template <typename... Ts>
  auto end() const {
    return base_ + num_elements_;
  }

  template <typename... Ts>
  auto end(Ts... indices) const {
    return end_impl(std::index_sequence_for<Ts...>{}, indices...);
  }

  /// Accesses the element at `indices...`. If `sizeof...(indices)` is smaller
  /// than the number of dimensions, missing indices are zero filled.
  template <typename... Ts>
  auto operator ()(Ts... indices) const {
    return *begin(indices...);
  }

private:
  template <std::size_t... seq, typename... Ts>
  auto end_impl(std::index_sequence<seq...>, Ts... indices) const {
    return begin(indices + (seq == sizeof...(Ts) - 1 ? 1 : 0) ...);
  }

  Iterator base_;
  std::size_t steps_[max_dim + 1]{};
  std::size_t num_elements_ = 0;
};

/// Makes a `multi_view` of the range beginning at `base` with dimension extents
/// `extents...`.
template <typename Iterator, typename... Ts>
auto make_multi_view(Iterator base, Ts... extents) {
  return multi_view<Iterator>(base, extents...);
}

} // namespace hhxx

#endif // HHXX_MULTI_VIEW_HPP_
