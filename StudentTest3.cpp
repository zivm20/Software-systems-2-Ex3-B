//
// Created by Amit Melamed on 02/04/2022.
//
#include "doctest.h"
#include "Matrix.hpp"

using namespace std;
using namespace zich;
TEST_CASE ("ADD/SUB/MULTY") {
    vector<double> vector;
    for (double i = 0; i < 100; ++i) {
        vector.push_back(i);
    }
    /**
     * Here we will check adding,substructing of 2 different shape matrix.
     * we can add and substruct A and B if and only if the two matrix have same rows and cols size.
     */
    Matrix A{vector, 10, 10};
    Matrix B{vector, 5, 20};
    CHECK_THROWS(A + B);
    CHECK_THROWS(B + A);
    CHECK_THROWS(A - B);
    CHECK_THROWS(B - A);
    CHECK_THROWS(A += B);
    CHECK_THROWS(B += A);
    CHECK_THROWS(A -= B);
    CHECK_THROWS(B -= A);
    /**
     * A and B can be multiply if and only if:
     * A is n*m matrix
     * B is m*k matrix
     */
    vector.clear();
    for (double i = 0; i < 30; ++i) {
        vector.push_back(i);
    }
    Matrix C{vector, 5, 6};
    vector.clear();
    for (double i = 0; i < 60; ++i) {
        vector.push_back(i);
    }
    Matrix D{vector, 6, 10};
    //A is 10*10
    //B is 5*20
    //C is 5*6
    //D is 6*10
    // only A*A, D*A and C*D are allowed
    CHECK_NOTHROW(A * A);
    CHECK_THROWS(A * B);
    CHECK_THROWS(A * C);
    CHECK_THROWS(A * D);
    CHECK_THROWS(B * A);
    CHECK_THROWS(B * B);
    CHECK_THROWS(B * C);
    CHECK_THROWS(B * D);
    CHECK_THROWS(C * A);
    CHECK_THROWS(C * B);
    CHECK_THROWS(C * C);
    CHECK_NOTHROW(C * D);
    CHECK_NOTHROW(D * A);
    CHECK_THROWS(D * B);
    CHECK_THROWS(D * C);
    CHECK_THROWS(D * D);
    CHECK_NOTHROW(A *= A);
    CHECK_THROWS(A *= B);
    CHECK_THROWS(A *= C);
    CHECK_THROWS(A *= D);
    CHECK_THROWS(B *= A);
    CHECK_THROWS(B *= B);
    CHECK_THROWS(B *= C);
    CHECK_THROWS(B *= D);
    CHECK_THROWS(C *= A);
    CHECK_THROWS(C *= B);
    CHECK_THROWS(C *= C);
    CHECK_NOTHROW(C *= D);
    CHECK_NOTHROW(D *= A);
    CHECK_THROWS(D *= B);
    CHECK_THROWS(D *= C);
    CHECK_THROWS(D *= D);
}

TEST_CASE ("Equality between two matrix's") {
    /**
     * Given 2 matrix's A and B
     * Matrix A and Matrix B will call equal if and only if all their numbers equals.
     * Matrix A will be called bigger than B if and only if the sum of the parts of A biggers then parts of B.
     * If matrix A and B not from the same shape (different rows and cols size)-an error should be thrown.
     * If the sum of A and B is equal but not all of their numbers are equal- A are not equal to B.
     */
    SUBCASE("Two equal matrix") {
        vector<double> vectorA = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<double> vectorB = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Matrix A{vectorA, 3, 3};
        Matrix B{vectorB, 3, 3};
        CHECK_EQ(A == B, true);
        CHECK_EQ(A != B, false);
        CHECK_EQ(A < B, false);
        CHECK_EQ(A > B, false);
        CHECK_EQ(A <= B, true);
        CHECK_EQ(A >= B, true);
    }

    SUBCASE("A and B is in the same shape, but B is bigger") {
        vector<double> vectorA = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<double> vectorB = {9, 9, 9, 9, 9, 9, 9, 9, 9};
        Matrix A{vectorA, 3, 3};
        Matrix B{vectorB, 3, 3};
        CHECK_EQ(A == B, false);
        CHECK_EQ(A != B, true);
        CHECK_EQ(A < B, true);
        CHECK_EQ(A > B, false);
        CHECK_EQ(A <= B, true);
        CHECK_EQ(A >= B, false);
    }
    SUBCASE("A and B is in the same shape, but A is bigger") {
        vector<double> vectorA = {10, 20, 30, 40, 50, 60, 70, 80, 90,100,110,120};
        vector<double> vectorB = {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12};
        Matrix A{vectorA, 3, 4};
        Matrix B{vectorB, 3, 4};
        CHECK_EQ(A == B, false);
        CHECK_EQ(A != B, true);
        CHECK_EQ(A < B, false);
        CHECK_EQ(A > B, true);
        CHECK_EQ(A <= B, false);
        CHECK_EQ(A >= B, true);
        //Now we will multy B by 10 and A==B
        B=B*10;
        CHECK_EQ(B==A, true);

        CHECK_EQ(B==A, true);
        A*=10;
        B=B*5;
        B=B*2;
        CHECK_EQ(B==A, true);
    }
}
/**
 * In this test case we will check our calculation work.
 * we will check adding,substructing and multiplication functions.
 */
TEST_CASE("Calculation work"){
    vector<double> vectorA = {1, 2, 3, 4,
                              5, 6, 7, 8,
                              9,10,11,12};
    vector<double> vectorB = {1, 2, 3,
                              4, 5, 6,
                              7, 8, 9,
                              10,11,12};
    //A*B==C
    vector<double> vectorC = {70, 80, 90,
                              158, 184, 210,
                              246, 288, 330};
    //B*A=D
    vector<double > vectorD={38,44,50,56,
                             83,98,113,128,
                             128,152,176,200,
                             173,206,239,272};
    vector<double> vectorI_3={1,0,0,
                              0,1,0,
                              0,0,1};
    vector<double> vectorI_4={1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              0,0,0,1};
    vector<double > vector_zero_3={0,0,0,
                                   0,0,0,
                                   0,0,0};
    vector<double > vector_zero_4={0,0,0,0,
                                   0,0,0,0,
                                   0,0,0,0,
                                   0,0,0,0};
    vector<double> vector_one_3={1,1,1,
                                 1,1,1,
                                 1,1,1};
    vector<double> vector_one_4={1,1,1,1,
                                 1,1,1,1,
                                 1,1,1,1,
                                 1,1,1,1};


    Matrix A{vectorA, 3, 4};
    Matrix B{vectorB, 4, 3};
    Matrix C{vectorC,3,3};
    Matrix D{vectorD,4,4};
    Matrix I_3{vectorI_3,3,3};
    Matrix I_4{vectorI_4,4,4};
    Matrix zero_3{vector_zero_3,3,3};
    Matrix zero_4{vector_zero_4,4,4};
    Matrix oneMatrix_3{vector_one_3,3,3};
    Matrix oneMatrix_4{vector_one_4,4,4};




    CHECK_EQ((A*B)==C, true);
    CHECK_EQ((B*A)==D, true);
    //every matrix * the I matrix should be equal to itself.
    CHECK_EQ((C*I_3)==C, true);
    CHECK_EQ((D*I_4)==D, true);
    //every matrix * the ZERO matrix is equal to zero matrix.
    CHECK_EQ((C*zero_3)==zero_3, true);
    CHECK_EQ((D*zero_4)==zero_4, true);
    //every matrix + zero matrix equal to itself.
    CHECK_EQ((C+zero_3)==C, true);
    CHECK_EQ((D+zero_4)==D, true);
    //every matrix - zero matrix equal to itself.
    CHECK_EQ((C-zero_3)==C, true);
    CHECK_EQ((D-zero_4)==D, true);
    CHECK_EQ((D-D)==zero_4, true);
    CHECK_EQ((C-C)==zero_3, true);
    //zero matrix ++ should be equal to one matrix
    zero_3++;
    ++zero_4;
    CHECK_EQ(zero_3==oneMatrix_3,true);
    CHECK_EQ(zero_4==oneMatrix_4,true);
}
/**
 * matrix size should be m*n integers:
 * m>0,n>0.
 * numbers array size should be n*m.
 */
TEST_CASE("Bad input in Constructor"){
    vector<double> arr={1,2,3,4,5,6,7,8,9,10,11,12};
    CHECK_NOTHROW(Matrix m(arr,3,4));
    CHECK_NOTHROW(Matrix m(arr,4,3));
    CHECK_NOTHROW(Matrix m(arr,2,6));
    CHECK_NOTHROW(Matrix m(arr,6,2));
    CHECK_NOTHROW(Matrix m(arr,1,12));
    CHECK_NOTHROW(Matrix m(arr,12,1));
    //m and n positive integers,but m*n!=arr.size
    CHECK_THROWS(Matrix m(arr,10,10));
    CHECK_THROWS(Matrix m(arr,3,3));
    CHECK_THROWS(Matrix m(arr,4,4));
    CHECK_THROWS(Matrix m(arr,4,10));
    CHECK_THROWS(Matrix m(arr,10,3));
    //m*n==arr.size but m and n negative
    CHECK_THROWS(Matrix m(arr,-3,-4));
    CHECK_THROWS(Matrix m(arr,-4,-3));
    CHECK_THROWS(Matrix m(arr,-2,-6));
    CHECK_THROWS(Matrix m(arr,-6,-2));
    CHECK_THROWS(Matrix m(arr,-1,-12));
    CHECK_THROWS(Matrix m(arr,-12,-1));
    //negative numbers and zero
    CHECK_THROWS(Matrix m(arr,-4,3));
    CHECK_THROWS(Matrix m(arr,4,-3));
    CHECK_THROWS(Matrix m(arr,0,-3));
    CHECK_THROWS(Matrix m(arr,-3,0));
    CHECK_THROWS(Matrix m(arr,0,0));
    CHECK_THROWS(Matrix m(arr,0,3));
    CHECK_THROWS(Matrix m(arr,3,0));
}
TEST_CASE("bad input in functions"){
    vector<double> arr={1,2,3,4,5,6,7,8,9,10,11,12};
    Matrix A(arr,4,3);
    Matrix B(arr,2,6);
    CHECK_THROWS(A*B);
    CHECK_THROWS(B*A);
    CHECK_THROWS(A+B);
    CHECK_THROWS(A-B);
    CHECK_THROWS(B-A);
    CHECK_THROWS(B+A);
    Matrix C(arr,3,4);
    CHECK_NOTHROW(A*C);
    CHECK_NOTHROW(C*A);
    CHECK_THROWS(A+C);
    CHECK_THROWS(A-C);
    CHECK_THROWS(C-A);
    CHECK_THROWS(C+A);
    CHECK_THROWS(A*=B);
    CHECK_THROWS(B*=A);
    CHECK_THROWS(A+=B);
    CHECK_THROWS(A-=B);
    CHECK_THROWS(B-=A);
    CHECK_THROWS(B+=A);
    CHECK_NOTHROW(A*=C);
    CHECK_NOTHROW(C*=A);
    CHECK_THROWS(A+=C);
    CHECK_THROWS(A-=C);
    CHECK_THROWS(C-=A);
    CHECK_THROWS(C+=A);
}
TEST_CASE("Prefix and Postfix"){
    Matrix A({1,2,3,4,5,6},2,3);
    Matrix B({2,3,4,5,6,7},2,3);
    Matrix C({3,4,5,6,7,8},2,3);
    Matrix D({1,2,3,4,5,6},2,3);

    A++;
    CHECK_EQ(A==B, true);
    ++A;
    CHECK_EQ(A==C, true);
    A--;
    --A;
    CHECK_EQ(A==D, true);
}




