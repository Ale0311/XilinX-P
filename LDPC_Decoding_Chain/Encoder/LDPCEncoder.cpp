/*
 * LDPCEncoder.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Oana
 */

#include "LDPCEncoder.h"
#include<iostream>
#include <fstream>
#include <cstdlib>

using namespace ::std;

LDPC_Encoder::LDPC_Encoder(int nr_cols_b, int nr_rows_b, int expansion_factor) {
	// TODO Auto-generated constructor stub
    this->nr_cols_b = nr_cols_b;
    this->nr_rows_b = nr_rows_b;
    this->expansion_factor = expansion_factor;
	
	//vezi ca trebuie calculati si aceste valori 
	/*
	int nr_cols_h; 		//nr of columns in h matrix
	int nr_rows_h;		//nr of rows in h matrix
    int nr_src_bits;	//number of source(usefull) bits
	int codeword_size;	//codeword size in bits
	*/
	
	
	
}

LDPC_Encoder::~LDPC_Encoder() {
	// TODO Auto-generated destructor stub

}


//creating the identity matrix
void LDPC_Encoder::create_identity(){
    int i,j;
    
    this->identity = (int **)malloc(this->expansion_factor * sizeof(int *));
    for (i=0; i<this->expansion_factor; i++)
         this->identity[i] = (int *)malloc(this->expansion_factor * sizeof(int));
    
    for( i=0;i<this->expansion_factor;i++ ){
        for(j=0;j<this->expansion_factor;j++)
            if ( i==j )
                this->identity[i][j] = 1;
            else this->identity[i][j] = 0;
    }
    
    
}
//reading matrix b from a given file
void LDPC_Encoder::read_b(ifstream &fin){
    
    int i,j;
    
   this->base_matrix = (int **)malloc(this->nr_rows_b * sizeof(int *));
   for (i=0; i<this->nr_rows_b; i++)
        this->base_matrix[i] = (int *)malloc(this->nr_cols_b * sizeof(int));
        
    
       for( i=0;i<this->nr_rows_b;i++ )
            for(j=0;j<this->nr_cols_b;j++)
                fin>>this->base_matrix[i][j];

}
//printing the matrix
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

void LDPC_Encoder :: permute(ofstream &fout,int n ) {
    
    
    
    int i,j;
    int k=0;

    
    if ( n!= -1 ){
    for( i=n;i<this->expansion_factor;i++ ){
        for(j=0;j<this->expansion_factor;j++){
                   fout<<identity[i][j]<<" ";
            
            
        }
        
        fout<<endl;
        
    }
    
    for( i=0;i<n;i++ ){
        for(j=0;j<this->expansion_factor;j++){
                    fout<<identity[i][j]<<" ";
           
            
        }
        
        fout<<endl;
        
           }
    }
    
    else {
        
        for( i=0;i<this->expansion_factor;i++ ){
            for(j=0;j<this->expansion_factor;j++){
                fout<<0<<" ";
        
            }
    
        fout<<endl;
       
        
    }
    }
    

    
    cout<<k<<endl;
    
}

void LDPC_Encoder::expand_b(ofstream & fout){
    
    
    int i,j;
    for( i=0;i<this->nr_rows_b;i++ ){
    for(j=0;j<this->nr_cols_b;j++){
            cout<<this->base_matrix[i][j]<<" ";
           permute(fout, this->base_matrix[i][j]);
       }
      }
    
   
}

void LDPC_Encoder::extract_h(){
    
    ifstream fin("h.txt");
    
    
    int index1=0;
    int i,j;
    int matrixRead=0;
    
    int x = this->nr_rows_b * this->expansion_factor;
    int y = this->nr_cols_b * this->expansion_factor;
    
    this->parity_check = (int **)malloc( x * sizeof(int *));
    for (i=0; i<x; i++)
         this->parity_check[i] = (int *)malloc( y * sizeof(int));
    
    i=0;
    
    
    
    while (!fin.eof()){
        
        for( i=0;i<this->expansion_factor;i++ )
            for(j=0;j<this->expansion_factor;j++){
                fin>>this->parity_check[this->expansion_factor*index1+i][this->expansion_factor*matrixRead+j];
            }

        
        matrixRead++;
        
        if(matrixRead == this->nr_cols_b){
            index1++;
            matrixRead=0;
        }
        
    }
    

    cout<<endl<<this->parity_check[288][2016]<<endl;
  
    fin.close();
}

void LDPC_Encoder::set_base_matrix(){
    
    ifstream fin("b.txt");
    ofstream fout("h.txt");
    
    read_b(fin);
    create_identity();
    see_b();
    
    
    expand_b(fout);
    fin.close();
    fout.close();
    extract_h();

}





int main () {
    
    LDPC_Encoder E(24,6,96);
    E.set_base_matrix();
    
    return 0;
    
}

