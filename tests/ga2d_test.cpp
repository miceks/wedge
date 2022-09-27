#include <gtest/gtest.h>
#include <cmath>
#include <numbers>
#include "wedge.hpp"

using namespace wg;
using namespace algebras::ga2d;


TEST(ga2d, sum)
{
    mvec<e1, e2, e12> v1 = {1.0f, 1.0f, 1.0f};
    mvec<e1, e2> v2 = {1.0f, -1.0f};
    auto v3 = eval(v1 + v2 + 1.0f);

    EXPECT_FLOAT_EQ(get<scalar>(v3), 1.0f);
    EXPECT_FLOAT_EQ(get<e1>(v3),     2.0f);
    EXPECT_FLOAT_EQ(get<e2>(v3),     0.0f);
    EXPECT_FLOAT_EQ(get<e12>(v3),    1.0f);

    vec v4 = {5, 1};
    vec v5 = {-1.2f, 5.5f};
    vec v6 = v4 + v5;
    EXPECT_FLOAT_EQ(get<e1>(v6), 3.8f);
    EXPECT_FLOAT_EQ(get<e2>(v6), 6.5f);

    auto v7 = eval(1_e1 + 2_e2 + 4_e12 + 1.5_e1 + 2.5_e2 + 4.5_e12 + 1 + 2.5f);
    EXPECT_FLOAT_EQ(get<scalar>(v7), 3.5f);
    EXPECT_FLOAT_EQ(get<e1>(v7),     2.5f);
    EXPECT_FLOAT_EQ(get<e2>(v7),     4.5f);
    EXPECT_FLOAT_EQ(get<e12>(v7),    8.5f);
}

TEST(ga2d, diff)
{
    mvec<e1, e2, e12> v1 = {1.0f, 1.0f, 1.0f};
    mvec<e1, e2> v2 = {1.0f, -1.0f};
    auto v3 = eval(v1 - v2 - 1.0f);
    EXPECT_FLOAT_EQ(get<scalar>(v3), -1.0f);
    EXPECT_FLOAT_EQ(get<e1>(v3),      0.0f);
    EXPECT_FLOAT_EQ(get<e2>(v3),      2.0f);
    EXPECT_FLOAT_EQ(get<e12>(v3),     1.0f);

    vec v4 = {5, 1};
    vec v5 = {-1.2f, 5.5f};
    vec v6 = v4 - v5;
    EXPECT_FLOAT_EQ(get<e1>(v6), 6.2f);
    EXPECT_FLOAT_EQ(get<e2>(v6), -4.5f);

    auto v7 = eval(-1_e1 - 2_e2 - 4_e12 - 1.5_e1 - 2.5_e2 - 4.5_e12 - 1 - 2.5f);
    EXPECT_FLOAT_EQ(get<scalar>(v7), -3.5f);
    EXPECT_FLOAT_EQ(get<e1>(v7),     -2.5f);
    EXPECT_FLOAT_EQ(get<e2>(v7),     -4.5f);
    EXPECT_FLOAT_EQ(get<e12>(v7),    -8.5f);
    
}

TEST(ga2d, scaling)
{
    mvec<scalar, e1, e2, e12> v1 = 1 + 1_e1 + 1_e2 + 1_e12;
    auto v2 = eval(2 * v1);
    auto v3 = eval(v1 * 2.0f);
    auto v4 = eval(v2 - v3);
    EXPECT_FLOAT_EQ(get<scalar>(v4), 0.0f);
    EXPECT_FLOAT_EQ(get<e1>(v4),     0.0f);
    EXPECT_FLOAT_EQ(get<e2>(v4),     0.0f);
    EXPECT_FLOAT_EQ(get<e12>(v4),    0.0f);

    mvec<scalar, e1, e2, e12> v5 = 1.0f + 1.0_e1 + 1.0_e2 + 1.0_e12;
    auto v6 = eval(2.0f * v5);
    auto v7 = eval(v5 * 2);
    auto v8 = eval(v6 - v7);
    EXPECT_FLOAT_EQ(get<scalar>(v8), 0.0f);
    EXPECT_FLOAT_EQ(get<e1>(v8),     0.0f);
    EXPECT_FLOAT_EQ(get<e2>(v8),     0.0f);
    EXPECT_FLOAT_EQ(get<e12>(v8),    0.0f);
}

TEST(ga2d, negation)
{
    mvec<scalar, e1, e2, e12> v1 = 1 + 1_e1 + 1_e2 + 1_e12;
    auto v2 = eval(-v1);
    auto v3 = eval(v1 + v2);
    EXPECT_FLOAT_EQ(get<scalar>(v3), 0.0f);
    EXPECT_FLOAT_EQ(get<e1>(v3),     0.0f);
    EXPECT_FLOAT_EQ(get<e2>(v3),     0.0f);
    EXPECT_FLOAT_EQ(get<e12>(v3),    0.0f);
}

TEST(ga2d, reversion)
{
    mvec<scalar, e1, e2, e12> v1 = 1 + 1_e1 + 1_e2 + 1_e12;
    auto v2 = eval(~v1);
    EXPECT_FLOAT_EQ(get<scalar>(v2),  1.0f);
    EXPECT_FLOAT_EQ(get<e1>(v2),      1.0f);
    EXPECT_FLOAT_EQ(get<e2>(v2),      1.0f);
    EXPECT_FLOAT_EQ(get<e12>(v2),    -1.0f);
}

TEST(ga2d, geometric_prod)
{
    EXPECT_FLOAT_EQ(get<scalar>(1_e1 * 1_e1),    1.0f);
    EXPECT_FLOAT_EQ(get<scalar>(1_e2 * 1_e2),    1.0f);
    EXPECT_FLOAT_EQ(get<scalar>(1_e12 * 1_e12), -1.0f);

    EXPECT_FLOAT_EQ(get<e12>(1_e1 * 1_e2),  1.0f);
    EXPECT_FLOAT_EQ(get<e12>(1_e2 * 1_e1), -1.0f);

    mvec<e1, e2> v1 = 1_e1 + 1_e2;
    auto v2 = eval(v1 * v1);
    EXPECT_FLOAT_EQ(get<scalar>(v2), 1.0f + 1.0f);
    EXPECT_FLOAT_EQ(get<e12>(v2),    0.0f);

    mvec<scalar, e1, e2, e12> v3 = 3 + 2_e1 - 1_e2 + 1_e12;
    mvec<scalar, e1, e2, e12> v4 = 0.7f - 1.1_e1 + 0.4_e2 - 4.7_e12;
    auto v5 = eval(v3 * v4);
    EXPECT_FLOAT_EQ(get<scalar>(v5),  4.2f );
    EXPECT_FLOAT_EQ(get<e1>(v5),     -6.2f );
    EXPECT_FLOAT_EQ(get<e2>(v5),     -7.8f );
    EXPECT_FLOAT_EQ(get<e12>(v5),    -13.7f);
}

TEST(ga2d, mixed_expr)
{
    // Reflection
    vec v1 = {1, 2};
    vec v2 = {1, 0};
    auto v3 = eval(-v2 * v1 * v2);
    EXPECT_FLOAT_EQ(get<e1>(v3), -1.0f);
    EXPECT_FLOAT_EQ(get<e2>(v3),  2.0f);

    // Double reflection by same vector (identity)
    vec v4 = 1.2_e1 - 3.1_e2;
    vec v5 = std::cos(std::numbers::pi / 7) * 1_e1 + std::sin(std::numbers::pi / 7) * 1_e2;
    auto v6 = eval((v5 * v5) * v4 * ~(v5 * v5));
    EXPECT_FLOAT_EQ(get<e1>(v6),  1.2f);
    EXPECT_FLOAT_EQ(get<e2>(v6), -3.1f);

    // Larger expression
    vec v7 = {1, 5};
    vec v8 = {-1.3f, 4.2f};
    vec v9 = {0.0f, 3};
    auto v10 = eval(-(1.2f * v7 - v8 + 1) * (v8 * v9 + 2_e1 - 1.5f) * 2);
    EXPECT_FLOAT_EQ(get<scalar>(v10), -32.2f );
    EXPECT_FLOAT_EQ(get<e1>(v10),     -73.54f);
    EXPECT_FLOAT_EQ(get<e2>(v10),     -20.46f);
    EXPECT_FLOAT_EQ(get<e12>(v10),     15.0f);
}