Build your project with the matrix.c file.

Use the "Matrix" definition, do not work with the structure, unless you know what you are doing.

You can find the determinant, minor, cofactor, adjoint and inverse of any matrix as long as it's possible to calculate. (Unless there's a bug)

A matrix is just a pointer to the real data, so it was intended for variables to have constant addresses as values to prevent memory leaks.
(This means that every time you do a calculation, whether it is an inverse or scale of a matrix for example, it will need a new variable to store the resulting matrix. This is the best solution that I found for preventing memory leaks. Suggestions are open)  

Do not forget to free the memory after defining a matrix. (All values of the matrix lies in the dynamic memory.)

This is a hobby project (obviously), so do not expect professionalism.
