#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

namespace zich{
    class Matrix{
        private:
            std::vector<std::vector<double>> matrix;
            int rows;
            int cols;
            static std::vector<std::vector<double>> genMatrix(const std::vector<double>& vals, int r, int c);
            
        public:
            
            Matrix(const std::vector<double>& vals, int r, int c);
            Matrix();

            //mat + mat
            friend Matrix operator+(Matrix lMat, const Matrix& rMat);
            //+= operator
            Matrix& operator+=(const Matrix& rMat);
            //unary + operator
            Matrix& operator+(){
                return *this;
            }
            //mat - mat
            friend Matrix operator-(Matrix lMat, const Matrix& rMat);
            //-= operator
            Matrix& operator-=(const Matrix& rMat);
            //unary - operator
            friend Matrix operator-(Matrix mat);

            bool operator<(const Matrix& rMat) const;
            bool operator>(const Matrix& rMat) const;
            bool operator==(const Matrix& rMat) const;
            bool operator!=(const Matrix& rMat) const;
                //return !(this->operator==(rMat));
            
            bool operator<=(const Matrix& rMat) const;
                //return this->operator==(rMat) || this->operator<(rMat);
            
            bool operator>=(const Matrix& rMat) const;
                //return this->operator==(rMat) || this->operator>(rMat);
            

            //++mat operator
            Matrix& operator++();
            //mat++ operator
            Matrix operator++(int);
            //--mat operator
            Matrix& operator--();
            //mat-- operator
            Matrix operator--(int);
            
            //mat * scalar
            friend Matrix operator*(Matrix lMat, double scalar);
            //scalar * mat
            friend Matrix operator*(double scalar,Matrix rMat);
            //*= operator
            Matrix& operator*=(double scalar);
            //mat - mat
            friend Matrix operator*(Matrix lMat, const Matrix& rMat);
            //*= operator
            Matrix& operator*=(const Matrix& rMat);
            //<< operator
            friend std::ostream& operator<<(std::ostream& output, const Matrix& mat);
            //>> operator
            
            friend std::istream& operator>>(std::istream& input, Matrix& mat);
            

            double get(std::size_t i, std::size_t j) const{
                return matrix[i][j];
            }
            int getRows()const{
                return rows;
            }
            int getCols()const{
                return cols;
            }
            void ensureSameSize(const Matrix& mat) const{
                if(rows != mat.getRows() || cols != mat.getCols()){
                    throw std::invalid_argument("Matrices are not the same size");
                }
            }
            //will apply some function that gets (const Matrix&,const Matrix& , size_t, size_t) on each element
            //of our matrix 
            void applyOnEach(const Matrix& srcMat, double (*process)(const Matrix&,const Matrix& ,size_t, size_t)){
                for(size_t i = 0; i<rows; i++){
                    for(size_t j = 0; j<cols; j++){
                        matrix[i][j] = process(*this,srcMat,i,j);
                    }
                }
            }
            //same as before but for using a double instead of matrix
            void applyOnEach(double scalar, double (*process)(const Matrix&,double ,size_t, size_t)){
                for(size_t i = 0; i<rows; i++){
                    for(size_t j = 0; j<cols; j++){
                        matrix[i][j] = process(*this,scalar,i,j);
                    }
                }
            }

            //compute sum of matrix
            double sum() const{
                double sum = 0;
                for(size_t i = 0; i<rows; i++){
                    for(size_t j = 0; j<cols; j++){
                        sum+=matrix[i][j];
                    }
                }
                return sum;
            }
    };
}




