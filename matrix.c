// The MIT License (MIT)

// Copyright (c) 2024 Ubeyda ALNACCAR

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


#include "matrix.h"

//struct sMatrix ANS = (struct sMatrix){.r = 0, .c = 0, .data = NULL};

Matrix matInit0(unsigned row, unsigned column){
    Matrix mat = malloc(sizeof(struct sMatrix));
    if(mat == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    void *pvc = &mat->r;
    *((unsigned*)pvc) = row;
    pvc = &mat->c;
    *((unsigned*)pvc) = column;
    pvc = &mat->data;
    *((double**)pvc) = malloc(sizeof(double*) * row);
    if(mat->data == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    for (size_t i = 0; i < row; i++)
    {
        mat->data[i] = malloc(sizeof(double) * column);
        if(mat->data[i] == NULL){
            for (size_t j = 0; j < i; j++)
            {
                free(mat->data[j]);
            }
            free(mat->data);
            return NULL;
        }
        for (size_t j = 0; j < mat->c; j++)
        {
            mat->data[i][j] = 0.0f;
        }
    }
    /*
    if(ANS.data == NULL){
        pvc = &ANS.data;
        *((double**)pvc) = malloc(sizeof(double*));
    }
    */
    return mat;
}

Matrix matInitI(unsigned dim){
    Matrix result = matInit0(dim, dim);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    for (size_t i = 0; i < dim; i++)
    {
        result->data[i][i] = 1;
    }
    return result;
}

Matrix matInitArr(unsigned row, unsigned column, double *arr){
    Matrix result = matInit0(row, column);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            result->data[i][j] = arr[(i*column) + j];
        }
    }
    return result;
}

Matrix matInitArr2(unsigned row, unsigned column, ...){
    Matrix result = matInit0(row, column);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    va_list ptr;
    va_start(ptr, row*column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            result->data[i][j] = va_arg(ptr, double);
        }
    }
    va_end(ptr);
    return result;
}

bool matCopy(const Matrix from, Matrix to){
    if(from == NULL || to == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    if(from->c != to->c || from->r != to->r) return -1;
    for (size_t i = 0; i < from->r; i++)
    {
        for (size_t j = 0; j < from->c; j++)
        {
            to->data[i][j] = from->data[i][j];
        }
    }
    return 0;
}

void matFree(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Cannot free an uninitialized matrix!(%u:%s)\n", __LINE__, __FILE__);
        return;
    }
    for (size_t i = 0; i < mat->r; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

static Matrix matSubMat(const Matrix mat, unsigned iIndex, unsigned jIndex){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix result = matInit0(mat->r-1,mat->c-1);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    unsigned iCounter = 0, jCounter = 0;
    for (size_t i = 0; i < mat->r; i++)
    {
        if(i == iIndex) continue;
        jCounter = 0;
        for (size_t j = 0; j < mat->c; j++)
        {
            if(j == jIndex) continue;
            result->data[iCounter][jCounter] = mat->data[i][j];
            jCounter++;
        }
        iCounter++;
    }
    return result;
}

double matDet(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return 0;
    }
    if(mat->c != mat->r){
        printf("ERROR: Non-square matrix provided, determinant uncalculable!(%u:%s)\n", __LINE__, __FILE__);
    };
    double result = 0;
    for (size_t j = 0; j < mat->c; j++)
    {
        if(mat->r == 2){
            return ((mat->data[0][0] * mat->data[1][1]) - (mat->data[0][1] * mat->data[1][0]));
        }
        Matrix temp = matSubMat(mat, 0, j);
        if(temp == NULL){
            printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
            return 0;
        }
        if(j % 2 == 0)
            result += mat->data[0][j] * matDet(temp);
        else 
            result -= mat->data[0][j] * matDet(temp);
        matFree(temp);
    }
    return result;   
}

void matPrint(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Cannot print an uninitialized matrix!(%u:%s)\n", __LINE__, __FILE__);
        return;
    }
    printf("{\n");
    for (size_t i = 0; i < mat->r; i++)
    {
        printf("\t");
        for (size_t j = 0; j < mat->c; j++)
        {
            printf("%lf\t", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("}\n");
}

bool matSetFromArr(Matrix mat, double *arr){
    for (size_t i = 0; i < mat->r; i++)
    {
        for (size_t j = 0; j < mat->c; j++)
        {
            mat->data[i][j] = arr[(mat->r*i) + j];
        }
    }
    return 0;
}

Matrix matMinor(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix result = matInit0(mat->r, mat->c);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    for (size_t i = 0; i < mat->r; i++)
    {
        for (size_t j = 0; j < mat->c; j++)
        {
            Matrix temp = matSubMat(mat, i, j);
            result->data[i][j] = matDet(temp);   
            matFree(temp);
        }
    }
    return result;
}

Matrix matCofactor(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix result = matInit0(mat->r, mat->c);
    if(result == NULL){
        printf("ERROR: Cannot allocate memory!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    for (size_t i = 0; i < mat->r; i++)
    {
        for (size_t j = 0; j < mat->c; j++)
        {
            if(i % 2 == 0){
                if(j % 2 == 0)
                    result->data[i][j] = (+1) * mat->data[i][j];
                else
                    result->data[i][j] = (-1) * mat->data[i][j];
            }else{
                if(j % 2 == 0)
                    result->data[i][j] = (-1) * mat->data[i][j];
                else
                    result->data[i][j] = (+1) * mat->data[i][j]; 
            }
        }   
    }
    return result;
}

Matrix matTranspose(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix result = matInit0(mat->c, mat->r);
    unsigned iCounter = 0, jCounter = 0;
    for (size_t j = 0; j < mat->c; j++)
    {
        jCounter = 0;
        for (size_t i = 0; i < mat->r; i++)
        {
            result->data[iCounter][jCounter] = mat->data[i][j]; 
            jCounter++;
        }
        iCounter++;
    }
    return result;
}

Matrix matScale(Matrix mat, double value){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix result = matInit0(mat->r, mat->c);
    for (size_t i = 0; i < mat->r; i++)
    {
        for (size_t j = 0; j < mat->c; j++)
        {
            result->data[i][j] = mat->data[i][j] * value;
        }
    }
    return result;
}

Matrix matInverse(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    double det = matDet(mat); 
    if(det == 0){
        printf("Warning: Matrix un-inversable (single, det = 0) or an memory allocation error occured!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    Matrix Mminor = matMinor(mat);
    Matrix Mcofator = matCofactor(Mminor);
    Matrix Mtranspose = matTranspose(Mcofator);//The result is adjoing of the matrix
    Matrix result = matScale(Mtranspose, 1/det);

    matFree(Mminor);
    matFree(Mcofator);
    matFree(Mtranspose);

    return result;
}

Matrix matMult(Matrix mat1, Matrix mat2){
    if(mat1 == NULL || mat2 == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    if(mat1->c != mat2->r){
        printf("ERROR: Cannot multiply provided matrices, dimensions do not match!(%u:%u)\n", mat1->c, mat2->r);
        return NULL;
    };
    Matrix result = matInit0(mat1->r, mat2->c);
    for (size_t i = 0; i < mat1->r; i++)
    {
        for (size_t j = 0; j < mat2->c; j++)
        {
            double add = 0.0f;
            for (size_t k = 0; k < mat2->r; k++)
            {
                add += mat1->data[i][k] * mat2->data[k][j];
            }
            result->data[i][j] = add;
        }
        
    }
    return result;
}

void matInput(Matrix mat){
    if(mat == NULL){
        printf("ERROR: Uninitialized matrix was provided!(%u:%s)\n", __LINE__, __FILE__);
        return NULL;
    }
    unsigned compCols = 0;
    unsigned compRows = 0;
    for (size_t cycles = 0; cycles < mat->r*mat->c; cycles++)
    {
        printf("{\n");
        for (size_t i = 0; i < compRows+1; i++)
        {
            printf("\t");
            for (size_t j = 0; j < compCols; j++)
            {
                printf("%lf\t", mat->data[i][j]);
            }
            if(i == compRows - 1){
                scanf("%lf", &mat->data[compRows][compCols++]);
                if(compCols == mat->c){
                    compCols = 0;
                    compRows++;
                }
                break;
            }else{
                printf("\n");
            }
        }
        printf("}\n");
    }
}