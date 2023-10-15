 /*
Assignment 5 - PHYS30471
Artemis Bouzaki - 20/03/2023
This is the main program and it implements the different operators, constructors and member functions of the matrix class.
*/
#include <iostream>
#include "matrix.h"
int main()
{
    // First part of assignemnt: matrix operations 
    //Default constructor
    matrix matrix_default;
    std::cout<<"The default matrix is:"<<std::endl;
    std::cout<<matrix_default<<std::endl;
    // Parameterized constructor
    double data_A[9] = {1,2,3,9,8,7,4,2,6};
    double data_B[9] = {5,5,4,1,2,3,6,9,8};
    double data_C[6] = {3,4,1,2,5,6};
    // Define matrices
    matrix matrix_B(3,3,data_B);
    matrix matrix_A(3,3,data_A);
    matrix matrix_C(2,3,data_C);
    // Read matrix A and B
    std::cout<<"Matrix A is"<<std::endl;
    std::cout<<matrix_A<<std::endl;
    std::cout<<"Matrix B is"<<std::endl;
    std::cout<<matrix_B<<std::endl;
    // Print addition and subtraction of A and B 
    std::cout<<"Addition of A and B is "<<std::endl;
    std::cout<<matrix_A+matrix_B<<std::endl;
    std::cout<<"Subtraction of B from A (A-B) is"<<std::endl;
    std::cout<<matrix_A-matrix_B<<std::endl;
    // Print product of A.B, B.C
    std::cout<<"Product A*B is"<<std::endl;
    std::cout<<matrix_A*matrix_B<<std::endl;
    std::cout<<"Product C*B is"<<std::endl;
    std::cout<<matrix_C*matrix_B<<std::endl;
    // Remove ith row and jth column of A
    std::cout<<"Matrix A with row 1 and column 2 removed"<<std::endl;
    std::cout<<matrix_A.delete_row_col(1,2)<<std::endl;
   // Determinant calculation
    std::cout<<"Determinant of A is: "<<matrix_A.determinant()<<std::endl;
    std::cout<<"Determinant of B is: "<<matrix_B.determinant()<<std::endl;
    // Second part of assignment: constructing and deep copying matrices
    // Deep copy by assignment
    matrix matrix_D;
    matrix_D=matrix_A;
    std::cout<<"Copy of matrix A using assignment"<<std::endl;
    std::cout<<matrix_D<<std::endl;   
    matrix_A.set_element(1,1,0);
    // Modify elements of A and show D is unchanged
    std::cout<<"Modified first element of matrix A.."<<std::endl;
    std::cout<<matrix_A<<std::endl;
    std::cout<<"But copied matrix is the same!"<<std::endl;
    std::cout<<matrix_D<<std::endl;
    // Deep copy using copy constructor
    matrix matrix_E{matrix_A};
    std::cout<<"Copy of matrix A using copy constructor (using previously modified version of A)"<<std::endl;
    std::cout<<matrix_E<<std::endl;
    // Modify contents of A and show E  is unchanged
    matrix_A.set_element(1,2,-1);
    std::cout<<"Modify matrix A further:"<<std::endl;
    std::cout<<matrix_A<<std::endl;
    std::cout<<"But copied matrix is the same!"<<std::endl;
    std::cout<<matrix_E<<std::endl;
    // Change elements of A to return to how it was originally
    matrix_A.set_element(1,1,1);
    matrix_A.set_element(1,2,2);
    std::cout<<"Now we edit matrix A so that it is on its original form again (easier to show move operations):"<<std::endl;
    std::cout<<matrix_A<<std::endl;
    // Copy using move constructor
    matrix matrix_H(std::move(matrix_B));
    std::cout<<"Copy of matrix B using move constructor"<<std::endl;
    std::cout<<matrix_H<<std::endl;
    std::cout<<"Demonstration that B no longer exists"<<std::endl;
    std::cout<<matrix_B<<std::endl;
    // Copy using move assignment
    matrix matrix_F;
    matrix_F = std::move(matrix_A);
    std::cout<<"Copy of matrix A using move assignment"<<std::endl;
    std::cout<<matrix_F<<std::endl;
    std::cout<<"Demonstration that A no longer exists"<<std::endl;
    std::cout<<matrix_A<<std::endl;
    // Third part of assignment: ask user for input
    matrix input_matrix;
    std::cout<<"You made it this far! Now time to input your own matrix in the format: rows, cols [data] eg. 1,2 [1 2]"<<std::endl;
    std::cout<<"Please be careful! Data should be space separated but there should be a comma between rows and cols!"<<std::endl;
    std::cin>> input_matrix;
    std::cout<<"Your input matrix is:"<<std::endl;
    std::cout<<input_matrix<<std::endl;
    // Show impossibility of B*C
    std::cout<<"Product B*C is"<<std::endl;
    std::cout<<matrix_H*matrix_C<<std::endl;
    return 0;
}