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

#include "matrix.h"
int main(){
    double arr[] = {
        3, 2, 3, 5, 1, 2,
        4, 5, 6, 7, 2, 3,
        1, 3, -2, 1, 9, 7,
        5, 2, 6, 1, 3, 1,
        7, 1, 4, 2, 6, 9,
        6, 2, 3, 1, 6, 2
    };
    //Matrix mat1   = matInitArr(6, 6, arr); //Uncomment
    Matrix mat1 = matInitArr2(3, 3,
    3.0f, 4.0f, 2.0f, 
    1.0f, 7.0f, 6.0f,
    5.0f, 6.0f, 1.0f
    );
    Matrix InvMat = matInverse(mat1);
    Matrix resMat = matMult(mat1, InvMat);
    
    Matrix arrMat = matInitArr(6, 6, arr);
    Matrix invArr = matInverse(arrMat);
    Matrix arrI = matMult(arrMat, invArr);

    matPrint(mat1);
    matPrint(InvMat);
    matPrint(resMat);

    matPrint(arrMat);
    matPrint(invArr);
    matPrint(arrI);


    //Free-ing used matrices.
    matFree(mat1);
    matFree(InvMat);
    matFree(resMat);
    matFree(arrMat);
    matFree(invArr);
    matFree(arrI);
    return 0;
}
