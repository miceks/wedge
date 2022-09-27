#include <gtest/gtest.h>
#include <type_traits>
#include "wedge.hpp"

using namespace wg;

TEST(mvec_test, tuple_size)
{
    EXPECT_EQ((std::tuple_size<mvec<blade<0,0,0>>>::value), 1);

    EXPECT_EQ((std::tuple_size<mvec<blade<0,0,0>,
                                    blade<1,0,0>>>::value), 2);

    EXPECT_EQ((std::tuple_size<mvec<blade<0,0,0>,
                                    blade<1,0,0>,
                                    blade<2,0,0>>>::value), 3);

    EXPECT_EQ((std::tuple_size<mvec<blade<0,0,0>,
                                    blade<1,0,0>,
                                    blade<2,0,0>,
                                    blade<3,0,0>>>::value), 4);
}

TEST(mvec_test, tuple_element)
{
    using M1 = mvec<blade<1,0,0, float>>;
    EXPECT_TRUE((std::is_same_v<std::tuple_element<0, M1>::type, float>));

    using M2 = mvec<blade<1,0,0, double>>;
    EXPECT_TRUE((std::is_same_v<std::tuple_element<0, M2>::type, double>));

    using M3 = mvec<blade<1,0,0, float>, 
                    blade<2,0,0, double>>;
    EXPECT_TRUE((std::is_same_v<std::tuple_element<0, M3>::type, float>));
    EXPECT_TRUE((std::is_same_v<std::tuple_element<1, M3>::type, double>));
}

TEST(mvec_test, get)
{
    mvec<blade<1,0,0>, blade<2,0,0>, blade<1,0,1>> v1 = {1.0, 2.0, -4.2};

    EXPECT_FLOAT_EQ(get<0>(v1),  1.0f);
    EXPECT_FLOAT_EQ(get<1>(v1),  2.0f);
    EXPECT_FLOAT_EQ(get<2>(v1), -4.2f);

    EXPECT_FLOAT_EQ((get<blade<1,0,0>>(v1)),  1.0f);
    EXPECT_FLOAT_EQ((get<blade<2,0,0>>(v1)),  2.0f);
    EXPECT_FLOAT_EQ((get<blade<1,0,1>>(v1)), -4.2f);

    auto v2 = get<blade<1,0,0>, blade<1,0,1>>(v1);

    EXPECT_FLOAT_EQ(get<0>(v2),  1.0f);
    EXPECT_FLOAT_EQ(get<1>(v2), -4.2f);
}

TEST(mvec_test, structured_bindings)
{
    mvec<blade<0,0,0>, blade<2,1,0>, blade<3,0,1>> v = {0.1, -1.1, 2.5};

    auto [a1, a2, a3] = v;
    EXPECT_FLOAT_EQ(a1,  0.1f);
    EXPECT_FLOAT_EQ(a2, -1.1f);
    EXPECT_FLOAT_EQ(a3,  2.5f);

    auto [b1, b2] = get<blade<0,0,0>, blade<3,0,1>>(v);
    EXPECT_FLOAT_EQ(b1, 0.1f);
    EXPECT_FLOAT_EQ(b2, 2.5f);
}

TEST(mvec_test, eval)
{
    mvec<blade<1,0,0>, blade<2,0,1>> v1 = {0.0, 10.1};
    auto v2 = eval(v1);
    EXPECT_FLOAT_EQ(get<0>(v2), 0.0f);
    EXPECT_FLOAT_EQ(get<1>(v2), 10.1f);
}

TEST(mvec_test, grade_projection)
{
    mvec<blade<0,0,0>,
         blade<1,0,0>,
         blade<2,0,0>,
         blade<3,0,0>,
         blade<0,1,1>> v = {1, 2, 3, 4, 5};

    auto scalar = grade<0>(v);
    EXPECT_FLOAT_EQ(get<0>(scalar), 1.0f);

    auto vector = grade<1>(v);
    EXPECT_FLOAT_EQ(get<0>(vector), 2.0f);
    EXPECT_FLOAT_EQ(get<1>(vector), 3.0f);

    auto bi_vector = grade<2>(v);
    EXPECT_FLOAT_EQ(get<0>(bi_vector), 4.0f);
    EXPECT_FLOAT_EQ(get<1>(bi_vector), 5.0f);
}