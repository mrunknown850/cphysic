#include <gtest/gtest.h>
#include "math/matrices.hpp"
#include "math/quaternions.hpp"
#include "math/vectors.hpp"

TEST(Matrix3x3Test, IdentityMatrix) {
    Matrix3x3 I = Matrix3x3::Identity();
    EXPECT_DOUBLE_EQ(I(0,0), 1.0);
    EXPECT_DOUBLE_EQ(I(1,1), 1.0);
    EXPECT_DOUBLE_EQ(I(2,2), 1.0);
    EXPECT_DOUBLE_EQ(I(0,1), 0.0);
    EXPECT_DOUBLE_EQ(I(0,2), 0.0);
    EXPECT_DOUBLE_EQ(I(1,0), 0.0);
    EXPECT_DOUBLE_EQ(I(1,2), 0.0);
    EXPECT_DOUBLE_EQ(I(2,0), 0.0);
    EXPECT_DOUBLE_EQ(I(2,1), 0.0);
}

TEST(Matrix3x3Test, MatrixVectorMultiplication) {
    Matrix3x3 M;
    M(0,0) = 1; M(0,1) = 2; M(0,2) = 3;
    M(1,0) = 4; M(1,1) = 5; M(1,2) = 6;
    M(2,0) = 7; M(2,1) = 8; M(2,2) = 9;
    Vec3 v(1, 2, 3);
    Vec3 result = M * v;
    EXPECT_DOUBLE_EQ(result.x, 1*1 + 2*2 + 3*3);
    EXPECT_DOUBLE_EQ(result.y, 4*1 + 5*2 + 6*3);
    EXPECT_DOUBLE_EQ(result.z, 7*1 + 8*2 + 9*3);
}

TEST(Matrix3x3Test, MatrixMatrixMultiplication) {
    Matrix3x3 A;
    A(0,0) = 1; A(0,1) = 2; A(0,2) = 3;
    A(1,0) = 4; A(1,1) = 5; A(1,2) = 6;
    A(2,0) = 7; A(2,1) = 8; A(2,2) = 9;

    Matrix3x3 B;
    B(0,0) = 9; B(0,1) = 8; B(0,2) = 7;
    B(1,0) = 6; B(1,1) = 5; B(1,2) = 4;
    B(2,0) = 3; B(2,1) = 2; B(2,2) = 1;

    Matrix3x3 C = A * B;
    EXPECT_DOUBLE_EQ(C(0,0), 1*9 + 2*6 + 3*3);
    EXPECT_DOUBLE_EQ(C(0,1), 1*8 + 2*5 + 3*2);
    EXPECT_DOUBLE_EQ(C(0,2), 1*7 + 2*4 + 3*1);
    EXPECT_DOUBLE_EQ(C(1,0), 4*9 + 5*6 + 6*3);
    EXPECT_DOUBLE_EQ(C(1,1), 4*8 + 5*5 + 6*2);
    EXPECT_DOUBLE_EQ(C(1,2), 4*7 + 5*4 + 6*1);
    EXPECT_DOUBLE_EQ(C(2,0), 7*9 + 8*6 + 9*3);
    EXPECT_DOUBLE_EQ(C(2,1), 7*8 + 8*5 + 9*2);
    EXPECT_DOUBLE_EQ(C(2,2), 7*7 + 8*4 + 9*1);
}

TEST(Matrix3x3Test, ZeroMatrix) {
    Matrix3x3 Z;
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j)
            EXPECT_DOUBLE_EQ(Z(i,j), 0.0);
}

TEST(Matrix3x3Test, MatrixSelfMultiplication) {
    Matrix3x3 M;
    M(0,0) = 2; M(0,1) = 0; M(0,2) = 0;
    M(1,0) = 0; M(1,1) = 3; M(1,2) = 0;
    M(2,0) = 0; M(2,1) = 0; M(2,2) = 4;
    Matrix3x3 R = M * M;
    EXPECT_DOUBLE_EQ(R(0,0), 4);
    EXPECT_DOUBLE_EQ(R(1,1), 9);
    EXPECT_DOUBLE_EQ(R(2,2), 16);
    EXPECT_DOUBLE_EQ(R(0,1), 0);
    EXPECT_DOUBLE_EQ(R(0,2), 0);
    EXPECT_DOUBLE_EQ(R(1,0), 0);
    EXPECT_DOUBLE_EQ(R(1,2), 0);
    EXPECT_DOUBLE_EQ(R(2,0), 0);
    EXPECT_DOUBLE_EQ(R(2,1), 0);
}

TEST(Matrix3x3Test, TransposeMatrix) {
    Matrix3x3 M;
    M(0,0) = 1; M(0,1) = 2; M(0,2) = 3;
    M(1,0) = 4; M(1,1) = 5; M(1,2) = 6;
    M(2,0) = 7; M(2,1) = 8; M(2,2) = 9;
    Matrix3x3 MT = M.Transpose();
    EXPECT_DOUBLE_EQ(MT(0, 0), 1);
    EXPECT_DOUBLE_EQ(MT(0, 1), 4);
    EXPECT_DOUBLE_EQ(MT(0, 2), 7);
    EXPECT_DOUBLE_EQ(MT(1, 0), 2);
    EXPECT_DOUBLE_EQ(MT(1, 1), 5);
    EXPECT_DOUBLE_EQ(MT(1, 2), 8);
    EXPECT_DOUBLE_EQ(MT(2, 0), 3);   
    EXPECT_DOUBLE_EQ(MT(2, 1), 6);   
    EXPECT_DOUBLE_EQ(MT(2, 2), 9);   
}