 /*
Assignment 5 - PHYS30471
Artemis Bouzaki - 20/03/2023
This program demonstrates the use of a class for matrices. The +, -, *, / operators are overloaded to perform operations between matrices. 
The << and >> operators are overloaded for suitable input and output of a matrix. The programme also utilises copy and move constructors as well as 
copy and move assignment operators. Finally, the class has member function to calculate the determinant of a nxn matrix.
*/
#include <iostream>
#include <cmath>
class matrix 
{
    friend std::ostream & operator<<(std::ostream &os, const matrix &matrix_temp);
    friend std::istream & operator>>(std::istream &is, matrix &matrix_temp);
    private:
    size_t row_num{0};
    size_t column_num{0};
    double *matrix_data{nullptr};

    public:
    // Default constructor
    matrix() = default;
    // Parameterized constructor 
    matrix(size_t m, size_t n, double *data): 
        row_num{m}, column_num{n}, matrix_data{data}
    {
        if(m <=0 || n <= 0) {
            throw::std::invalid_argument("Please check that the rows and columns are positive.");
        }
        if (data == nullptr) {
            throw std::invalid_argument("Please provide matrix data.");
        }
        // Dynamically allocate memory
        matrix_data = new double[m*n];
        for(size_t i{0};i<m*n;i++) {
            matrix_data[i] = data[i];
        }
    }
    // Construtor declarations
    matrix(matrix&); // copy constructor
    matrix(matrix&&); //move constructor
    // Destructor
    ~matrix(){
        if(matrix_data != nullptr) {
            delete[] matrix_data;
            std::cout<<"Destructor called"<<std::endl;
        }
    }
    // This function returns an element of the matrix given rows and cols.
    double get_element(size_t i, size_t j) const
    {
        if(i <= 0 || j <= 0 || i > row_num || j > column_num) {
            throw std::invalid_argument("Element you requested is out of bounds.");
        }
        return matrix_data[(i-1)*column_num + j-1];
    }
    // Changes element of matrix
    void set_element(size_t i, size_t j, double value) 
    {
        if(i <= 0 || j <= 0 || i > row_num || j > column_num) {
            throw std::invalid_argument("Element you tried to set is out of bounds.");
        }
        matrix_data[(i-1)*column_num + j-1] = value;
    }
    // This function returns an array containing elements of a row
    double* get_row(size_t i) const
    {
        double* row = new double[column_num];
        if(i < 0 || i > row_num) {
            throw std::invalid_argument("The row index is out of bounds!");
        } else {
            for(size_t j{1};j<=column_num;j++) {
                row[j-1] = get_element(i,j);
            }
        }
        return row;
    }
    // This function returns an array containing elements of a column
    double* get_column(size_t j) const
    {
        double* column = new double[row_num];
        if(j < 0 || j > column_num) {
            throw std::invalid_argument("The column index is out of bounds!");
        } else {
            for(size_t i{1};i<=row_num;i++) {
                column[i-1] = get_element(i,j);
            }
        }
        return column;
    }
    // This function returns matrix with ith row and jth column deleted
    matrix delete_row_col(size_t row, size_t column) const
    {
        double* sub_data = new double[(row_num-1)*(column_num-1)];
        size_t k{0};
        if(row_num < 1 || column_num < 1 || row < 0 || row > row_num || column < 0 || column > column_num) {
            throw std::invalid_argument("Please check that the matrix is reducible and the indices are valid!");
        } else {
            for(size_t i{1};i<=row_num;i++) {
                if(i == row) {
                    continue;
                }
                for(size_t j{1};j<=column_num;j++) {
                    if(j == column) {
                        continue;
                    }
                    sub_data[k++] = get_element(i, j);
                }
            }
        }
        matrix matrix_temp(row_num-1, column_num-1, sub_data);
        delete[] sub_data;
        return matrix_temp;
    }
    // Member function declarations
    matrix& operator=(matrix&); // copy assignment
    matrix& operator=(matrix&&); // move assignment
    double determinant() const; // determinant
    matrix operator+(const matrix &matrix_temp);
    matrix operator-(const matrix &matrix_temp);
    matrix operator*(const matrix &matrix_temp);
    double & operator[](size_t i);
};
// Copy constructor
matrix::matrix(matrix& matrix_temp)
{
    std::cout<<"Copy constructor called"<<std::endl;
    matrix_data = nullptr;
    column_num = matrix_temp.column_num;
    row_num = matrix_temp.row_num;
    if (column_num > 0 && row_num > 0) {
        matrix_data = new double[column_num*row_num];
        for(size_t i{0};i<row_num*column_num;i++) {
            matrix_data[i] = matrix_temp.matrix_data[i];
        }
    }
}
// Move constructor
matrix::matrix(matrix &&matrix_temp)
{ 
    std::cout <<"Move constructor called"<<std::endl;
    column_num = matrix_temp.column_num;
    row_num = matrix_temp.row_num;
    matrix_data = matrix_temp.matrix_data;
    matrix_temp.column_num = 0;
    matrix_temp.row_num = 0;
    matrix_temp.matrix_data = nullptr;
}
// Assignment operator
matrix & matrix::operator=(matrix &matrix_temp)
{
    std::cout<<"Assignment called"<<std::endl;
    if(&matrix_temp == this) {
        return *this;
    }
    // Delete matrix data
    delete [] matrix_data; 
    matrix_data = nullptr;
    column_num = 0;
    row_num = 0;
    // Copy and declare new array
    column_num = matrix_temp.column_num;
    row_num = matrix_temp.row_num;
    if(column_num > 0 && row_num > 0) {
        matrix_data = new double[row_num*column_num];
        for(size_t i{0};i<column_num*row_num;i++) {
            matrix_data[i] = matrix_temp.matrix_data[i];
        }
    }
    return *this;
}
// Move assignment operator
matrix & matrix::operator=(matrix&& matrix_temp)
{
    std::cout <<"Move assignment called"<<std::endl;
    std::swap(column_num, matrix_temp.column_num);
    std::swap(row_num, matrix_temp.row_num);
    std::swap(matrix_data, matrix_temp.matrix_data);
    return *this; 
}
// Overloading + operator
matrix matrix::operator+(const matrix &matrix_temp)
{
    double *addition = new double[row_num*column_num];
    // check if matrices are of same size
    if(matrix_temp.row_num != row_num || matrix_temp.column_num != column_num) {
        throw std::invalid_argument("Please check if matrices are of the same size");
    } else {
        for(size_t i{0};i<row_num*column_num;i++) {
            addition[i] = matrix_data[i] + matrix_temp.matrix_data[i];
        }
    }
    matrix temp(row_num, column_num, addition);
    delete[] addition;
    return temp;
}
// Overload - operator
matrix matrix::operator-(const matrix &matrix_temp)
{
    double *subtraction = new double[row_num*column_num];
    if(matrix_temp.row_num != row_num || matrix_temp.column_num != column_num) {
        throw std::invalid_argument("Please check if matrices are of the same size");
    } else {
        for(size_t i{0};i<row_num*column_num;i++) {
            subtraction[i] = matrix_data[i] - matrix_temp.matrix_data[i];
        }
    }
    matrix temp(row_num, column_num, subtraction);
    delete[] subtraction;
    return temp;
}
// Overload * operator
matrix matrix::operator*(const matrix &matrix_temp)
{
    double* product = new double[row_num*matrix_temp.column_num];
    double sum{0};
    if(column_num != matrix_temp.row_num) {
        throw std::invalid_argument("Please check if number of columns of the first matrix equals the number of rows of the second.");
    } else {
        for(size_t i{1};i<=row_num;i++) {
            for(size_t j{1};j<=matrix_temp.column_num;j++) {
                double* row = get_row(i);
                double* column = matrix_temp.get_column(j);
                for(size_t k{1};k<=column_num;k++) {
                    sum += row[k-1]*column[k-1];
                }
                product[matrix_temp.column_num*(i-1) + j-1] = sum;
                sum = 0;
                delete[] row;
                delete[] column;
            }
        }
    }
    matrix temp(row_num, matrix_temp.column_num, product);
    delete[] product;
    return temp;   
}
// Function to overload << operator 
std::ostream & operator<<(std::ostream &os, const matrix &matrix_temp)
{
    for(size_t i{1};i<=matrix_temp.row_num;i++) {
        os<<"{";
        for(size_t j{1};j<=matrix_temp.column_num;j++) {
            if(j!=matrix_temp.column_num) {
                os<<matrix_temp.get_element(i,j)<<", ";
            } else {
                os<<matrix_temp.get_element(i,j);
            }
        }
        os<<"}\n";
    }
    return os;
}
// Function to overload >> operator 
std::istream & operator>>(std::istream &is, matrix &matrix_temp)
{
    int rows;
    int cols;
    char comma;
    char bracket;
    while(true) {
        if(is >> rows && rows > 0) {
            matrix_temp.row_num = rows;
            if(is >> comma >> cols && comma == ',' && cols > 0) {
                matrix_temp.column_num = cols;
                if(is>> bracket && bracket == '[') {
                    delete[] matrix_temp.matrix_data;
                    matrix_temp.matrix_data = new double[rows*cols];
                    for(size_t i{0};i<rows*cols;i++) {
                        double value;
                        is >> value;
                        if(is.fail()) {
                            break;
                        }
                        matrix_temp.matrix_data[i] = value;
                    }
                    if(is >> bracket && bracket == ']') {
                        break;
                    }
                }
            }
        }
        std::cout << "Invalid input. Please check and try again." << std::endl;
        is.clear();
        is.ignore(1000, '\n');
    }
    return is;
}
// Overloaded element [] operator implementation
double & matrix::operator[](size_t i)
{
    if(i < 0 || i > column_num*row_num) {
        std::cout<<"Error: trying to access array element out of bounds"<<std::endl;
        throw("Out of Bounds error");
    }
    return matrix_data[i];
} 
// This function returns the determinant of an nxn matrix recursively
double matrix::determinant() const
{
    if(column_num != row_num) {
        throw std::invalid_argument("Cannot calculate determinant of non-square matrix!");
    } else {
        // Case of 1x1 matrix
        if(column_num == 1) {
           return get_element(1,1);
        } else if(column_num == 2) {
            // Case of 2x2 matrix
            return get_element(1,1)*get_element(2,2)-get_element(1,2)*get_element(2,1);
        } else {
            // All other cases
            double determinant_value{0};
            for(size_t j{1};j<=column_num;j++) {
                matrix minor{delete_row_col(1,j)};
                determinant_value += pow(-1, 1+j)*get_element(1,j)*minor.determinant();
            }
            return determinant_value;
        }
    }
}