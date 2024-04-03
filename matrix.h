// The MIT License (MIT)

// Copyright (c) 2024 Ubeyda A.

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/* code */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>//For I/O
#include <stdlib.h>//For dynamic memory management
#include <stdbool.h>//For booleans
#include <stdarg.h>

struct sMatrix{//Main structure of the Matrix
    const unsigned r, c;//Row, column
    double** const data;//Values
};

#define Matrix struct sMatrix* const //All matrices should be in the dynamic memory, otherwise not implemented.

//extern struct sMatrix ANS;

//Matrix initialization
Matrix  matInit0(unsigned row, unsigned column);//Initialize 0 matrix
Matrix  matInitI(unsigned dim);//Initialize Identity matrix.
Matrix  matInitArr(unsigned row, unsigned column, double *arr);
Matrix  matInitArr2(unsigned row, unsigned column, ...);
bool    matSetFromArr(Matrix mat, double *arr);
void    matFree(Matrix mat);//Free-ing the matrix.

//Matrix I/O
void    matPrint(Matrix mat);
void    matInput(Matrix mat);//Not implementetd. (yet)

//Matrix Algebra
double  matDet(Matrix mat);//Determinant
Matrix  matMinor(Matrix main);//Minor
Matrix  matCofactor(Matrix mat);//Cofactor
Matrix  matTranspose(Matrix mat);//Transposes
Matrix  matInverse(Matrix mat);//Inverse (Minor -> Cofactor -> Transpose (Adjoint) -> Scale with 1/det)
Matrix  matScale(Matrix mat, double value);//Scale the matrix
Matrix  matMult(Matrix mat1, Matrix mat2);//Multiplication between matrices.

#endif
