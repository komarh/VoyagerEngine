//
// Created by aethe on 5/20/2026.
//

#include <gtest/gtest.h>
#include "math/vector.h"

TEST(VectorCore, Vector_Constructor_Initilization)
{
    const VE::Math::TVector<float> v(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v[0], 1.0f);
    EXPECT_EQ(v[1], 2.0f);
    EXPECT_EQ(v[2], 3.0f);
}

TEST(VectorCore, Vector_Addition)
{
    const VE::Math::TVector<float> v1(1.0f, 1.0f, 1.0f);
    const VE::Math::TVector<float> v2(1.0f, 1.0f, 1.0f);

    VE::Math::TVector<float> v_final = v1 + v2;
    EXPECT_EQ(v_final[0], 2.0f);
    EXPECT_EQ(v_final[1], 2.0f);
    EXPECT_EQ(v_final[2], 2.0f);

    VE::Math::TVector<float> v3(1.0f, 1.0f, 1.0f);
    v3 += v2;
    EXPECT_EQ(v3[0], 2.0f);
    EXPECT_EQ(v3[1], 2.0f);
    EXPECT_EQ(v3[2], 2.0f);
}

TEST(VectorCore, Vector_Subtraction)
{
    const VE::Math::TVector<float> v1(1.0f, 1.0f, 1.0f);
    const VE::Math::TVector<float> v2(1.0f, 1.0f, 1.0f);

    VE::Math::TVector<float> v_final = v1 - v2;
    EXPECT_EQ(v_final[0], 0.0f);
    EXPECT_EQ(v_final[1], 0.0f);
    EXPECT_EQ(v_final[2], 0.0f);

    VE::Math::TVector<float> v3(1.0f, 1.0f, 1.0f);
    v3 -= v2;
    EXPECT_EQ(v3[0], 0.0f);
    EXPECT_EQ(v3[1], 0.0f);
    EXPECT_EQ(v3[2], 0.0f);
}

TEST(VectorCore, Vector_Multiplication)
{
    const VE::Math::TVector<float> v1(1.0f, 1.0f, 1.0f);
    VE::Math::TVector<float> v2 = v1 * 2.0f;
    EXPECT_EQ(v2[0], 2.0f);
    EXPECT_EQ(v2[1], 2.0f);
    EXPECT_EQ(v2[2], 2.0f);

    const VE::Math::TVector<float> v3 = 2.0f * v1;
    EXPECT_EQ(v3[0], 2.0f);
    EXPECT_EQ(v3[1], 2.0f);
    EXPECT_EQ(v3[2], 2.0f);

    VE::Math::TVector<float> v4(1.0f, 1.0f, 1.0f);
    v4 *= 2;
    EXPECT_EQ(v4[0], 2.0f);
    EXPECT_EQ(v4[1], 2.0f);
    EXPECT_EQ(v4[2], 2.0f);
}

TEST(VectorCore, Vector_Division)
{
    const VE::Math::TVector<float> v1(2.0f, 2.0f, 2.0f);
    VE::Math::TVector<float> v2 = v1/2;
    EXPECT_EQ(v2[0], 1.0f);
    EXPECT_EQ(v2[1], 1.0f);
    EXPECT_EQ(v2[2], 1.0f);

    VE::Math::TVector<float> v3(2.0f, 2.0f, 2.0f);
    v3 /= 2.0f;
    EXPECT_EQ(v3[0], 1.0f);
    EXPECT_EQ(v3[1], 1.0f);
    EXPECT_EQ(v3[2], 1.0f);
}

TEST(VectorCore, Vector_Magnitude) {
    const VE::Math::TVector<float> v1(1.0f, 0.0f, 0.0f);
    const VE::Math::TVector<float> v2(0.0f, 1.0f, 0.0f);
    const VE::Math::TVector<float> v3(0.0f, 0.0f, 1.0f);
    const VE::Math::TVector<float> v4(std::cos(1.0f), std::sin(1.0f), 0.0f);
    EXPECT_EQ(v1.Magnitude(), 1.0f);
    EXPECT_EQ(v2.Magnitude(), 1.0f);
    EXPECT_EQ(v3.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(v4.Magnitude(), 1.0f);
}

TEST(VectorCore, Vector_Normalize) {
    const VE::Math::TVector<float> v1(2.0f, 2.0f, 0.0f);
    VE::Math::TVector<float> v2 = v1.GetNormalized();

    VE::Math::TVector<float> v3(2.0f, 2.0f, 0.0f);
    v3.Normalize();

    VE::Math::TVector<float> v4(0.0f, 0.0f, 0.0f);

    EXPECT_FLOAT_EQ(v2.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(v3.Magnitude(), 1.0f);
    EXPECT_THROW(v4.Normalize(), std::runtime_error);
}





