/*
 * LDPCEncoder.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Oana
 */

#include "LDPCEncoder.h"
#include "gauss.h"
#include<iostream>
#include <fstream>
#include <cstdlib>

using namespace ::std;

LDPC_Encoder::LDPC_Encoder(int nr_cols_b, int nr_rows_b, int expansion_factor) {
	// TODO Auto-generated constructor stub
    this->nr_cols_b = nr_cols_b;
    this->nr_rows_b = nr_rows_b;
    this->expansion_factor = expansion_factor;
    
    //memory allocation
    int i;
    
    //for the identity matrix
    this->identity = (int **)malloc(this->expansion_factor * sizeof(int *));
       for (i=0; i<this->expansion_factor; i++)
            this->identity[i] = (int *)malloc(this->expansion_factor * sizeof(int));
    
    //for the base matrix
    this->base_matrix = (int **)malloc(this->nr_rows_b * sizeof(int *));
      for (i=0; i<this->nr_rows_b; i++)
           this->base_matrix[i] = (int *)malloc(this->nr_cols_b * sizeof(int));
    
    //for the h matrix
    int x = this->nr_rows_b * this->expansion_factor;
    int y = this->nr_cols_b * this->expansion_factor;
    
    this->parity_check = (int **)malloc( x * sizeof(int *));
    for (i=0; i<x; i++)
         this->parity_check[i] = (int *)malloc( y * sizeof(int));
    
    //for the a matrix
    x = this->nr_rows_b * this->expansion_factor;
    y = (this->nr_cols_b-this->nr_rows_b) * this->expansion_factor;
    
    this->a = (int **)malloc( x * sizeof(int *));
    for (i=0; i<x; i++)
         this->a[i] = (int *)malloc( y * sizeof(int));
    
    //for the t matrix
    
    x = this->nr_rows_b * this->expansion_factor;
    
       this->t = (float **)malloc( x * sizeof(float *));
         for (i=0; i<x; i++)
              this->t[i] = (float *)malloc( x * sizeof(float));
    
 
          
        this->inverse_of_t = (float **)malloc( x * sizeof(float *));
            for (i=0; i<x; i++)
                this->inverse_of_t[i] = (float *)malloc( x * sizeof(float));

           
    
    
}

LDPC_Encoder::~LDPC_Encoder() {

    free(this->identity);
    free(this->parity_check);
    free(this->base_matrix);
    free(this->a);
    free(this->t);
    free(this->inverse_of_t);

}




//reading matrix b from a given file

void LDPC_Encoder::read_b(ifstream &fin){
    
    int i,j;
       for( i=0;i<this->nr_rows_b;i++ )
            for(j=0;j<this->nr_cols_b;j++)
                fin>>this->base_matrix[i][j];

}

//printing the base matrix

void LDPC_Encoder::see_b(){
    
   
        
    int i,j;

    for( i=0;i<this->nr_rows_b;i++ ){

          for(j=0;j<this->nr_cols_b;j++){
                    cout<<base_matrix[i][j]<<" ";

              //permute(fout, b[i][j]);
          }
        cout<<endl;
    }


        
}

//creating the identity matrix

void LDPC_Encoder::create_identity( int n ){
    
    int i,j;
    unsigned char one = 1;
    unsigned char zero = 0;
    
    if ( n != -1 ){
        
    for( i=0;i<this->expansion_factor;i++ )
        for(j=0;j<this->expansion_factor;j++){
            int k = (i + n)%96;
            if ( k == j )
                this->identity[i][j] = one;
           else this->identity[i][j] = zero;
        }
                
            
    } else {
        for( i=0;i<this->expansion_factor;i++ )
    for(j=0;j<this->expansion_factor;j++)
         this->identity[i][j] = zero;
    }
    
    
}




void LDPC_Encoder::extract_h(){
    
    int index1=0;
    int i,j,k,l;
    int matrixRead=0;
    
    i=0;
    
    
    
    for (k=0;k<this->nr_rows_b;k++)
        for (l=0;l<this->nr_cols_b;l++){
            
            create_identity(this->base_matrix[k][l]);
        
        for( i=0;i<this->expansion_factor;i++ )
            for(j=0;j<this->expansion_factor;j++){
                this->parity_check[this->expansion_factor*index1+i][this->expansion_factor*matrixRead+j]=identity[i][j];
            }

        
        matrixRead++;
        
        if(matrixRead == this->nr_cols_b){
            index1++;
            matrixRead=0;
        }
        
    }
    

    get_h_triangular_form();
    
    //cout<<"h";
    //cout<<endl<<this->parity_check[288][2016]<<endl;
    //cout<<endl<<this->parity_check[3*96][960+61]<<endl;
  

}

//checking if b has a triangular form
bool LDPC_Encoder::parity_check_b(){
    return true;
}

//transforming h in a triangular form

void LDPC_Encoder::get_h_triangular_form() {
    if (this->parity_check_b () == true){
       
        this -> trans_version_h = this->parity_check;
        
       this->get_sub_matrix_a();
       this->get_sub_matrix_t();
        
    }
}

void LDPC_Encoder::get_sub_matrix_a() {
    
    int i,j;
    int k =0;
    
    for ( i=0;i<this->nr_rows_b*this->expansion_factor;i++){
          
        for ( j=0;j<(this->nr_cols_b - this->nr_rows_b)*this->expansion_factor;j++){
            a[i][j] = trans_version_h[i][j];
            k++;
        }
    }
    //cout<<endl<<k<<endl;
    //cout<<endl<<this->a[3*96][960+61]<<endl;
    
}

void LDPC_Encoder::get_sub_matrix_t() {
    
    int i,j;
    int k =0;
    
    for ( i=0;i<this->nr_rows_b*this->expansion_factor;i++){
       
          for ( j=0;j<this->nr_rows_b*this->expansion_factor;j++){
             
            t[i][j] = trans_version_h[i][j + ((this->nr_cols_b - this->nr_rows_b)*this->expansion_factor)];
            k++;
        }
    }
    
    //cout<<endl<<k<<endl;
    //cout<<endl<<this->t[574][574]<<endl;
    
}

void LDPC_Encoder::gaussian_elimination_inv_t(){
    
    ofstream fout ("inverse.txt");
    
       float **t_inv;
       int i,j;
       
      int x = this->nr_rows_b * this->expansion_factor;
       
          t_inv = (float **)malloc( x * sizeof(float *));
            for (i=0; i<x; i++)
                 t_inv[i] = (float *)malloc( 2*x * sizeof(float));
       
     
       
       for (i=0;i<x;i++)
           for(j=0;j<x;j++)
               t_inv[i][j]=t[i][j];
       

       InverseOfMatrix (t_inv,x);
    
    for (i=0;i<x;i++)
        for(j=0;j<x;j++)
            inverse_of_t[i][j]=t_inv[i][j+x];
    
    PrintInverse(inverse_of_t, x, fout);
    
    free(t_inv);
    
    fout.close();
    
    
}




void LDPC_Encoder::set_base_matrix(){
    
    ifstream fin("b.txt");
    read_b(fin);
    fin.close();
    
    see_b();
    extract_h();
    gaussian_elimination_inv_t();
   
    
    
}







int main () {
    
    LDPC_Encoder E(24,6,96);
    E.set_base_matrix();
    
    

    
    return 0;
    
}

