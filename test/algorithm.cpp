// Copyright (c) 2016, Lingxi Li <lilingxi.cs@gmail.com>
// All rights reserved.
// CPP Utility Library (https://github.com/Lingxi-Li/CPP_Utility)

#include <cppu/algorithm.hpp>
#include <cppu/algorithm.hpp>

#include <gtest/gtest.h>

namespace swap_test_ns {

struct member_swap_t {
  void swap(member_swap_t& other) {
    std::swap(v, other.v);
    // does something different for distinguishing purpose
    ++v;
    ++other.v;
  }
  int v;
};

struct free_adl_swap_t {
  int v;
};

void swap(free_adl_swap_t& x, free_adl_swap_t& y) {
  std::swap(x.v, y.v);
  // does something different for distinguishing purpose
  ++x.v;
  ++y.v;
}

} // namespace swap_test_ns

TEST(swap, member_swap) {
  using cppu::swap;
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x{0};
  obj_t y{1};
  swap(x, y);
  EXPECT_EQ(2, x.v);
  EXPECT_EQ(1, y.v);
}

TEST(swap, free_adl_swap) {
  using cppu::swap;
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x{0};
  obj_t y{1};
  swap(x, y);
  EXPECT_EQ(2, x.v);
  EXPECT_EQ(1, y.v);
}

TEST(swap, free_std_swap) {
  using cppu::swap;
  // ADL doesn't apply to primitive types
  int x = 0;
  int y = 1;
  swap(x, y);
  EXPECT_EQ(1, x);
  EXPECT_EQ(0, y);
}

TEST(swap, member_swap_array) {
  using cppu::swap;
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_adl_swap_array) {
  using cppu::swap;
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x[] = { {0}, {0} };
  obj_t y[] = { {1}, {1} };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_std_swap_array) {
  using cppu::swap;
  // ADL doesn't apply to primitive types
  int x[] = { 0, 0 };
  int y[] = { 1, 1 };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(1, x[i]);
    EXPECT_EQ(0, y[i]);
  }
}

TEST(swap, member_swap_array_recursive) {
  using cppu::swap;
  using obj_t = swap_test_ns::member_swap_t;
  obj_t x[2][2] = { { {0}, {0} },
                    { {0}, {0} } };
  obj_t y[2][2] = { { {1}, {1} },
                    { {1}, {1} } };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_adl_swap_array_recursive) {
  using cppu::swap;
  using obj_t = swap_test_ns::free_adl_swap_t;
  obj_t x[2][2] = { { {0}, {0} },
                    { {0}, {0} } };
  obj_t y[2][2] = { { {1}, {1} },
                    { {1}, {1} } };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_std_swap_array_recursive) {
  using cppu::swap;
  // ADL doesn't apply to primitive types
  int x[2][2] = { { 0, 0 },
                  { 0, 0 } };
  int y[2][2] = { { 1, 1 },
                  { 1, 1 } };
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(1, x[i][j]);
      EXPECT_EQ(0, y[i][j]);
    }
  }
}

TEST(swap, member_swap_std_array) {
  using cppu::swap;
  using obj_t = swap_test_ns::member_swap_t;
  using array_t = std::array<obj_t, 2>;
  array_t x = {{ {0}, {0} }};
  array_t y = {{ {1}, {1} }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_adl_swap_std_array) {
  using cppu::swap;
  using obj_t = swap_test_ns::free_adl_swap_t;
  using array_t = std::array<obj_t, 2>;
  array_t x = {{ {0}, {0} }};
  array_t y = {{ {1}, {1} }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(2, x[i].v);
    EXPECT_EQ(1, y[i].v);
  }
}

TEST(swap, free_std_swap_std_array) {
  using cppu::swap;
  // ADL doesn't apply to primitive types
  using array_t = std::array<int, 2>;
  array_t x = {{ 0, 0 }};
  array_t y = {{ 1, 1 }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    EXPECT_EQ(1, x[i]);
    EXPECT_EQ(0, y[i]);
  }
}

TEST(swap, member_swap_std_array_recursive) {
  using cppu::swap;
  using obj_t = swap_test_ns::member_swap_t;
  using array_t = std::array<std::array<obj_t, 2>, 2>;
  array_t x = {{ {{ {0}, {0} }},
                 {{ {0}, {0} }} }};
  array_t y = {{ {{ {1}, {1} }},
                 {{ {1}, {1} }} }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_adl_swap_std_array_recursive) {
  using cppu::swap;
  using obj_t = swap_test_ns::free_adl_swap_t;
  using array_t = std::array<std::array<obj_t, 2>, 2>;
  array_t x = {{ {{ {0}, {0} }},
                 {{ {0}, {0} }} }};
  array_t y = {{ {{ {1}, {1} }},
                 {{ {1}, {1} }} }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(2, x[i][j].v);
      EXPECT_EQ(1, y[i][j].v);
    }
  }
}

TEST(swap, free_std_swap_std_array_recursive) {
  using cppu::swap;
  // ADL doesn't apply to primitive types
  using array_t = std::array<std::array<int, 2>, 2>;
  array_t x = {{ {{ 0, 0 }},
                 {{ 0, 0 }} }};
  array_t y = {{ {{ 1, 1 }},
                 {{ 1, 1 }} }};
  swap(x, y);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(1, x[i][j]);
      EXPECT_EQ(0, y[i][j]);
    }
  }
}

////////////////////////////////////////
