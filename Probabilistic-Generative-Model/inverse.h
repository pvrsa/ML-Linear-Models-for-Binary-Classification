#include <bits/stdc++.h>

#define pi 3.141592653

using namespace std;

#define D 4

void getCofactor(double A[D][D], double temp[D][D], int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
double determinant(double A[D][D], int n)
{
    double x= 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
 
    double temp[D][D]; // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        x += sign * A[0][f] * determinant(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return x;
}
 
// Function to get adjoint of A[D][D] in adj[D][D].
void adjoint(double A[D][D],double adj[D][D])
{
    if (D == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1;
    double temp[D][D];
 
    for (int i=0; i<D; i++)
    {
        for (int j=0; j<D; j++)
        {
            
            getCofactor(A, temp, i, j, D);  
            sign = ((i+j)%2==0)? 1: -1;
            
            adj[j][i] = (sign)*(determinant(temp, D-1));
        }
    }
}
 

bool inverse(double A[D][D], double inverse[D][D])
{
    // Find determinant of A[][]
    int det = determinant(A, D);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    double adj[D][D];
    adjoint(A, adj);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<D; i++)
        for (int j=0; j<D; j++)
            inverse[i][j] = adj[i][j]/(double)det;
 
    return true;
}
