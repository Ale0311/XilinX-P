//
//  gauss.h
//  HfromB
//
//  Created by Alexandra-Gabriela Laicu-Hausberger on 30/03/2020.
//  Copyright © 2020 Alexandra-Gabriela Laicu-Hausberger. All rights reserved.
//

#ifndef gauss_h
#define gauss_h

#include<iostream>

using namespace::std;


void hello (){
    cout<<"hello";
}
// Function to Print matrix.
void PrintMatrix(Data **ar, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ar[i][j].getValue() << "  ";
        }
        printf("\n");
    }
    return;
}
  
// Function to Print inverse matrix
void PrintInverse(Data **ar, int n, ofstream &fout)
{
    for (int i = 0; i < n; i++) {
        for (int j=0; j < n; j++) {
            fout<<ar[i][j].getValue()<<" ";
        }
        fout<<endl;
    }
    return;
}
  
// Function to perform the inverse operation on the matrix.
void InverseOfMatrix(Data **matrix, int order)
{
    // Matrix Declaration.
  
    
    Data temp;
  
    // PrintMatrix function to print the element
    // of the matrix.
    printf("=== Matrix ===\n");
    //PrintMatrix(matrix, order, order);
  
    // Create the augmented matrix
    // Add the identity matrix
    // of order at the end of original matrix.
    for (int i = 0; i < order; i++) {
  
        for (int j = order; j < 2 * order; j++) {
  
            // Add '1' at the diagonal places of
            // the matrix to create a identity matirx
            if (j == (i + order))
                matrix[i][j].setValue(1) ;
            else  matrix[i][j].setValue(0);
        }
    }
  
    // Interchange the row of matrix,
    // interchanging of row will start from the last row
    for (int i = order - 1; i > 0; i--) {
  
         //Swapping each and every element of the two rows
         if (matrix[i - 1][0].getValue() < matrix[i][0].getValue() )
             
         for (int j = 0; j < 2 * order; j++) {
      
            
          temp = matrix[i][j];
          matrix[i][j] = matrix[i - 1][j];
          matrix[i - 1][j] = temp;
        
            }
    }
  
        
    
  
    // Print matrix after interchange operations.
    printf("\n=== Augmented Matrix ===\n");
    //PrintMatrix(matrix, order, order * 2);
  
    // Replace a row by sum of itself and a
    // constant multiple of another row of the matrix
    for (int i = 0; i < order; i++) {
  
        for (int j = 0; j < order; j++) {
  
            if (j != i) {
  //* instead of /
                temp = matrix[j][i] * matrix[i][i];
                for (int k = 0; k < 2 * order; k++) {
  
                    matrix[j][k] = matrix[j][k] - matrix[i][k] * temp;
                }
            }
        }
    }
  
    // Multiply each row by a nonzero integer.
    // Divide row element by the diagonal element
    for (int i = 0; i < order; i++) {
  
        temp = matrix[i][i];
        for (int j = 0; j < 2 * order; j++) {
   //* instead of /
            matrix[i][j] = matrix[i][j] * temp;
        }
    }
  
    // print the resultant Inverse matrix.
    printf("\n=== Inverse Matrix ===\n");
  
    return;
}


#endif /* gauss_h */
