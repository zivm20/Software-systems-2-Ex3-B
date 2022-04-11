#include "Matrix.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace zich;
using namespace std;
vector<vector<double>> Matrix::genMatrix(const vector<double>& vals, int r, int c){
    vector<vector<double>> mat;
    for(size_t i = 0; i < r; i++){
        vector<double> row;
        for(size_t j=0; j < c; j++){
            row.push_back(vals[i*size_t(c)+j]);
        }
        mat.push_back(row);
    }
    return mat;
}

Matrix::Matrix(const std::vector<double>& vals, int r, int c): matrix(genMatrix(vals,r,c)), rows(r), cols(c){
}
Matrix::Matrix(): matrix(), rows(0), cols(0){
}

ostream& zich::operator<<(std::ostream& output, const Matrix& mat){
    for(size_t i = 0; i<mat.rows; i++){
        string row;
        for(size_t j = 0; j<mat.cols; j++){
            row += to_string(mat.get(i,j));
            if(j < mat.cols-1){
                row.push_back(' ');
            }
        }
        output << "[" << row << "]" << endl;
    }
    return output;
}
istream& zich::operator>>(std::istream& input, Matrix& mat){
    int newRows;
    int newCols;
    cout<<"Rows; ";
    input>>newRows;
    cout<<"Cols; ";
    input>>newCols;
    vector<vector<double>> newMat;
    for(size_t i = 0; i < newRows; i++){
        vector<double> newRow;
        size_t j=0;
        double newVal; 
        char c;
        if(c != '\n'){
            input >> c;
            if (c == ','){
                input >> c;
            }
        }
        while(j < newCols && input.peek() != ']' && c != '\n'){
            input >> newVal;
            newRow.push_back(newVal);
            j++;
        }
        while(j < newCols){
            newRow.push_back(0);
            j++;
        }
        //get rid of the rest of the input
        while(c != ']' && c != '\n'){
            input >> c;
            if(input.peek() == '\n'){
                c = '\n';
            }
            //cout << (int)c;

        }
        newMat.push_back(newRow);
    }
    mat.cols = newCols;
    mat.rows = newRows;
    mat.matrix = newMat;
    return input;
}

Matrix zich::operator+(Matrix lMat, const Matrix& rMat){
    lMat += rMat;
    return lMat;
}


Matrix& Matrix::operator+=(const Matrix& rMat){
    ensureSameSize(rMat);
    auto MatCellAddition = [](const Matrix& mat1,const Matrix& mat2,size_t i, size_t j){
        return mat1.get(i,j)+mat2.get(i,j);
    };
    applyOnEach(rMat,MatCellAddition);
    return *this;
}


Matrix zich::operator-(Matrix lMat, const Matrix& rMat){
    lMat -= rMat;
    return lMat;
}
Matrix& Matrix::operator-=(const Matrix& rMat){
    //for each cell i,j in mat 1 subtract the value in cel i,j of mat 2
    auto MatCellSubtraction = [](const Matrix& mat1,const Matrix& mat2,size_t i, size_t j){
        return mat1.get(i,j)-mat2.get(i,j);
    };
    ensureSameSize(rMat);
    applyOnEach(rMat,MatCellSubtraction);
    return *this;
}
Matrix zich::operator-(Matrix mat){
    mat*=-1;
    return mat;
}


bool Matrix::operator<(const Matrix& rMat)const {
    ensureSameSize(rMat);
    return sum() < rMat.sum(); 
}
bool Matrix::operator>(const Matrix& rMat)const {
    ensureSameSize(rMat);
    return sum() > rMat.sum(); 
}
bool Matrix::operator==(const Matrix& rMat)const {
    ensureSameSize(rMat);
    if (rows != rMat.getRows() || cols != rMat.getCols()){
        return false;
    }
    for(size_t i = 0; i<rows; i++){
        for(size_t j = 0; j<cols; j++){
            if(matrix[i][j] != rMat.get(i,j)){
                return false;
            }
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix& rMat) const{
    return !operator==(rMat);
}
bool Matrix::operator<=(const Matrix& rMat) const{
    return this->operator==(rMat) || this->operator<(rMat);
}     
bool Matrix::operator>=(const Matrix& rMat) const{
    return this->operator==(rMat) || this->operator>(rMat);
}
          
Matrix& Matrix::operator++(){
    //increment each value by amount, in this case 1
    auto increment = [](const Matrix& mat1,double amount,size_t i, size_t j){
        return mat1.get(i,j)+amount;
    };
    
    applyOnEach(1,increment);
    return *this;
}

Matrix Matrix::operator++(int){
    Matrix temp = *this;
    operator++();
    return temp;
}
Matrix& Matrix::operator--(){
    //decrement each value by 1
    auto decrement = [](const Matrix& mat1,double amount,size_t i, size_t j){
        return mat1.get(i,j)-amount;
    };
    
    applyOnEach(1,decrement);
    return *this;
}

Matrix Matrix::operator--(int){
    Matrix temp = *this;
    operator--();
    return temp;
}

Matrix zich::operator*(Matrix lMat, double scalar){
    lMat*=scalar;
    return lMat;
}
Matrix zich::operator*(double scalar,Matrix rMat){
    rMat*=scalar;
    return rMat;
}
Matrix& Matrix::operator*=(double scalar){
    //multiply each value by scalar
    auto mult = [](const Matrix& mat1,double s,size_t i, size_t j){
            return mat1.get(i,j)*s;
    };
    applyOnEach(scalar,mult);
    return *this;
}

Matrix zich::operator*(Matrix lMat, const Matrix& rMat){
    lMat*=rMat;
    return lMat;
}


Matrix& Matrix::operator*=(const Matrix& rMat){
    if(getCols() != rMat.getRows()){
        throw std::invalid_argument("Invalid matrix multiplication");
    }
    //we cant change our original matrix since rMat might be a refernce to this matrix
    int newCols = rMat.getCols();
    int newRows = getRows();
    vector<double> vars;
    //standard matrix multiplication
    for(size_t i = 0; i < getRows(); i++){
        for(size_t j = 0; j < rMat.getCols(); j++){
            vars.push_back(0);
            for(size_t k = 0; k < getCols(); k++){
                vars[size_t(newCols)*i + j] += get(i,k)*rMat.get(k,j);
            }
        }
    }
    //now that we are done with the calculations, we can update our matrix
    Matrix temp{vars, newRows, newCols};
    *this = temp;
    return *this;
}

