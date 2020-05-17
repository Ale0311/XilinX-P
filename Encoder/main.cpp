//
//  main.cpp
//  HfromB
//
//  Created by Alexandra-Gabriela Laicu-Hausberger on 23/03/2020.
//  Copyright © 2020 Alexandra-Gabriela Laicu-Hausberger. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "gauss.h"

using namespace ::std;

int const EXP_F = 96;
int const LINE = 6;
int const COL = 24;
int co = 0;


int identity[EXP_F][EXP_F];

int b[LINE][COL];
int h[LINE*EXP_F][COL*EXP_F];
float a[(COL-LINE)*EXP_F][(COL-LINE)*EXP_F];
float t[LINE*EXP_F][LINE*EXP_F*2];
float tmp[LINE*EXP_F][(COL-LINE)*EXP_F];

int codeword[(COL-LINE)*EXP_F];

int index1,index2;



void permute( ofstream &fout,int n ){
    int i,j;
    int k=0;

    
    if ( n!= -1 ){
    for( i=n;i<EXP_F;i++ ){
        for(j=0;j<EXP_F;j++){
                   fout<<identity[i][j]<<" ";
            
            
        }
        
        fout<<endl;
        k++;
    }
    
    for( i=0;i<n;i++ ){
        for(j=0;j<EXP_F;j++){
                    fout<<identity[i][j]<<" ";
           
            
        }
        
        fout<<endl;
        k++;
           }
    }
    
    else {
        
        for( i=0;i<EXP_F;i++ ){
            for(j=0;j<EXP_F;j++){
                fout<<0<<" ";
        
            }
    
        fout<<endl;
        k++;
        
    }
    }
    

    
    cout<<k<<endl;

    co++;
    

}

void writeInFile(ofstream &fout){
    
    int i,j;

    for( i=0;i<LINE;i++ ){

        for(j=0;j<COL;j++){
                  cout<<b[i][j]<<" ";
           // if(i==0 && j == 18 )
             //   fout<<"***";
            permute(fout, b[i][j]);
        }


       }

}

void createIdentity(){
    int i,j;
    
    for( i=0;i<EXP_F;i++ ){
        for(j=0;j<EXP_F;j++)
            if ( i==j )
                identity[i][j] = 1;
            else identity[i][j] = 0;
    }
    
    
}

void readB(ifstream &fin,ofstream &fout){
    
int i,j;
   for( i=0;i<LINE;i++ )
        for(j=0;j<COL;j++)
            fin>>b[i][j];
    
//    for( i=0;i<LINE;i++ ){
//           for(j=0;j<COL;j++)
//               fout<<b[i][j]<<" ";
//    fout<<endl;
//    }
    
}

void getH(ifstream &fin){
    
    int co1,co2;
    co1=0;
    co2=0;
    int k=0;
    int i,j;
    int matrixRead=0;

    while (!fin.eof()){
        
        for( i=0;i<EXP_F;i++ )
            for(j=0;j<EXP_F;j++)
                fin>>h[EXP_F*index1+i][EXP_F*matrixRead+j];
        

        
        matrixRead++;
        
        if(matrixRead == COL){
            index1++;
            matrixRead=0;
        }
        
    }
    

    
    cout<<endl<<co1<<endl<<co2<<endl<<k<<endl;
    cout<<endl<<h[288][2016]<<endl;
}

void getT(){
    int i,j;
    
    ofstream fout("T.txt");
    
    for( i=0;i<LINE*EXP_F;i++ ){
        for(j=0;j<LINE*EXP_F;j++){
            t[i][j]=h[i][j+(COL-LINE)*EXP_F];
            fout<<t[i][j];
        }
        
        fout<<endl<<endl;
        }
    
    for( i=0;i<LINE*EXP_F;i++ ){
        for(j=0;j<LINE*EXP_F;j++)
            if ( t[i][j] == 1 && i == j )
                index2++;
    }
            
            
            
    cout<<index2<<endl;
    
    fout.close();
    
}

void getA(){
    
    int i,j;
    
    for( i=0;i<(COL-LINE)*EXP_F;i++ )
           for(j=0;j<(COL-LINE)*EXP_F;j++)
               a[i][j]=h[i][j];
    
}

void getCodeWord(){
    int i,j,k;
    int s[(COL-LINE)*EXP_F];
    
    ofstream fout("res.txt");
    
    srand((int)time(0));
    for(i=0;i<(COL-LINE)*EXP_F;i++){
        s[i]= rand()%2 ;
      }
    
    for(i=0;i<(COL-LINE)*EXP_F;i++){
        //fout<<s[i]<<" ";
    }
    fout<<endl;
    
   InverseOfMatrix(t, LINE*EXP_F,fout);
    
    fout<<endl;
    fout<<endl;
    fout<<"***";
    
    cout<<t[0][LINE*EXP_F+2];
    for( i=0;i<LINE*EXP_F;i++ )
        for(j=0;j<LINE*EXP_F;j++){
            t[i][j]=t[i][j+LINE*EXP_F];
        }
    
    float resultFinal[(COL)*EXP_F];
    float result[(COL-LINE)*EXP_F];

    for (i=0;i<(COL-LINE)*EXP_F;i++){
         result[i]=0;
    }
    
    for (i=0;i<COL*EXP_F;i++){
            resultFinal[i]=0;
       }
    
    
    for(i = 0; i < LINE*EXP_F; ++i)
    for(j = 0; j < (COL-LINE)*EXP_F; ++j)
        for(k = 0; k < LINE*EXP_F; ++k)
        {
            tmp[i][j] += t[i][k] * a[k][j];
        }

    for ( i=0;i<LINE*EXP_F;i++){
          for ( j=0;j<(COL-LINE)*EXP_F;j++){
               result[i]+=( tmp[i][j]*s[j]);
          }
       }

    fout<<endl<<"T^-1 * A * s = :"<<endl;
    for ( i=0;i<LINE*EXP_F;i++)
        fout<<result[i]<<" ";
    fout<<endl;
    
    for ( i=0;i<(COL-LINE)*EXP_F;i++)
      resultFinal[i]=s[i];
    for ( i=(COL-LINE)*EXP_F;i<COL*EXP_F;i++)
        resultFinal[i]=result[i-(COL-LINE)*EXP_F];
          
    fout<<endl<<"CodeWord:"<<endl;
    for ( i=0;i<COL*EXP_F;i++)
        fout<<resultFinal[i]<<" ";
    
    fout<<endl;
        
    for ( i=0;i<(LINE)*EXP_F;i++){
        int x = 0;
             for ( j=0;j<(COL)*EXP_F;j++)
                  x+=( h[i][j]*resultFinal[j]);
                 
        fout<<x<<" ";
             
          }
    
    fout.close();
    
}

int main(int argc, const char * argv[]) {
    
    ifstream fin("b.txt");
    ofstream fout("h.txt");
    
    readB(fin,fout);
    createIdentity();
    writeInFile(fout);


    cout<<co<<endl;
    
    fin.close();
    fout.close();

    ifstream f("h.txt");
    getH(f);
    f.close();
    
    getT();
    getA();
    
   getCodeWord();
    
  

    return 0;
}
