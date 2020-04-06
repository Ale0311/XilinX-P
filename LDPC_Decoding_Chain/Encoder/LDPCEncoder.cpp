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
    
    this->nr_src_bits = this->nr_cols_b -  this->nr_rows_b;
    this -> codeword_size = this->nr_cols_b;
    
    this ->nr_cols_h =  this->nr_cols_b *  this->expansion_factor;
    this ->nr_rows_h =  this->nr_rows_b *  this->expansion_factor;
    
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
   
    
    this->parity_check = (int **)malloc( this ->nr_rows_h * sizeof(int *));
    for (i=0; i<this ->nr_rows_h; i++)
         this->parity_check[i] = (int *)malloc( nr_cols_h * sizeof(int));
    
    //for the a matrix


    
    this->a = (int **)malloc( this ->nr_rows_h * sizeof(int *));
    for (i=0; i<this ->nr_rows_h; i++)
         this->a[i] = (int *)malloc( this->nr_src_bits * this->expansion_factor * sizeof(int));
    
    //for the t matrix
    
       this->t = (float **)malloc( this ->nr_rows_h * sizeof(float *));
         for (i=0; i<this ->nr_rows_h; i++)
              this->t[i] = (float *)malloc( this ->nr_rows_h * sizeof(float));
    
 
          
        this->inverse_of_t = (float **)malloc( this ->nr_rows_h * sizeof(float *));
            for (i=0; i<this ->nr_rows_h; i++)
                this->inverse_of_t[i] = (float *)malloc( this ->nr_rows_h * sizeof(float));

           
    
    
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
            int k = (i + n)%this->expansion_factor;
 
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
    
    for ( i=0;i<this->nr_rows_h;i++){
          
        for ( j=0;j<(this->nr_src_bits)*this->expansion_factor;j++){
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
    
    for ( i=0;i<this->nr_rows_h;i++){
       
          for ( j=0;j<this->nr_rows_h;j++){
             
            t[i][j] = trans_version_h[i][j + ((this->nr_src_bits)*this->expansion_factor)];
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
       
     
       
          t_inv = (float **)malloc( this->nr_rows_h * sizeof(float *));
            for (i=0; i<this->nr_rows_h; i++)
                 t_inv[i] = (float *)malloc( 2*this->nr_rows_h * sizeof(float));
       
     
       
       for (i=0;i<this->nr_rows_h;i++)
           for(j=0;j<this->nr_rows_h;j++)
               t_inv[i][j]=t[i][j];
       

       InverseOfMatrix (t_inv,this->nr_rows_h);
    
    for (i=0;i<this->nr_rows_h;i++)
        for(j=0;j<this->nr_rows_h;j++)
            inverse_of_t[i][j]=t_inv[i][j+this->nr_rows_h];
    
    PrintInverse(inverse_of_t, this->nr_rows_h, fout);
    
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

int LDPC_Encoder::encode(unsigned *src_vec, unsigned *coded_vector){
    
    
    float* result1;
    float* result2;
    float* x;
    float ** tmp;
    
    int i,j,k;
    
    // result 1 = T^-1 * A * s = p2
    result1=(float *)calloc(this->nr_src_bits * this->expansion_factor, sizeof(float));
    // result2 = x ( codeword )
    result2=(float *)calloc(this->nr_cols_h , sizeof(float));
    x=(float *)calloc(this->nr_cols_h , sizeof(float));
    
    // in tmp we store the result of T^-1 * A
    tmp = (float **)calloc(this->nr_rows_h ,sizeof(float *));
    for (i=0; i<this->nr_rows_h; i++)
    tmp[i] = (float*)calloc(this->expansion_factor*this->nr_src_bits, sizeof(float));
    
    
    //tmp=T^-1 * A
    for(i = 0; i < this->nr_rows_h; ++i)
    for(j = 0; j < this->expansion_factor*this->nr_src_bits; ++j)
        for(k = 0; k < this->nr_rows_h; ++k)
        
        {
            tmp[i][j] += this->inverse_of_t[i][k] * this->a[k][j];
        }
    
    //tmp*s
    for ( i=0;i<this->nr_rows_h;i++){
             for ( j=0;j<this->expansion_factor*this->nr_src_bits;j++){
                  result1[i] += ( tmp[i][j]*src_vec[j] );
             }
          }
    
    free (tmp);
    
    //checking p2
    cout<<endl<<"T^-1 * A * s = :"<<endl;
    for ( i=0;i<this->nr_rows_h;i++)
        cout<<result1[i]<<" ";
    cout<<endl;
    
    //forming the codeword
    for ( i=0;i<this->expansion_factor*this->nr_src_bits;i++)
      result2[i]=src_vec[i];
    
    for ( i=this->expansion_factor*this->nr_src_bits;i<this->nr_cols_h;i++)
        result2[i]=result1[i-this->expansion_factor*this->nr_src_bits];
    
    //checking the codeword
    cout<<endl<<"CodeWord:"<<endl;
    for ( i=0;i<this->nr_cols_h;i++)
        cout<<result2[i]<<" ";
    
    //h*x
    
    for ( i=0;i<this->nr_rows_h;i++){
       for ( j=0;j< this->nr_cols_h;j++){
            x[i] += ( this->parity_check[i][j]*result2[j]);
       }
    }
    
    cout<<endl<<"h*t' :"<<endl;
    for ( i=0;i<this->nr_rows_h;i++)
        cout<<x[i]<<" ";
    
    cout<<endl;

    free(result1);
    free(result2);
    
    return 0;
    
}




int main () {
    
    LDPC_Encoder E(6,3,1);
    E.set_base_matrix();
    
    srand((unsigned)time(0));
    
    unsigned s[18*96];
    unsigned c[24*96];
    
    for(int i=0;i<18*96;i++){
      s[i]= rand()%2;
        //cout<<s[i]<<" ";
    }
    
    E.encode(s, c);
    
    return 0;
    
}

