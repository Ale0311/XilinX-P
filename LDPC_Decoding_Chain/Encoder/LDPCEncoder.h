/*
 * LDPCEncoder.h
 *
 *  Created on: Apr 2, 2020
 *      Author: Oana
 */

#ifndef ENCODER_LDPCENCODER_H_
#define ENCODER_LDPCENCODER_H_

#include<fstream>

class LDPC_Encoder {
public:
	LDPC_Encoder(int nr_cols_b, int nr_rows_b, int expansion_factor);
	~LDPC_Encoder();

	void set_base_matrix();
	//
	int encode(unsigned  *src_vec, unsigned  *coded_vector);
    

private:
	//size of the input and output vector
	int nr_src_bits;	//number of source(usefull) bits
	int codeword_size;	//codeword size in bits
	//codeword properties
	int expansion_factor;	//the size of the expansion factor
	//size of base matrix b
	int nr_cols_b;		//nr of columns in b matrix;
	int nr_rows_b;		//nr of rows in b matrix;
	//size of parity check matrix h
	int nr_cols_h; 		//nr of columns in h matrix
	int nr_rows_h;		//nr of rows in h matrix
    
    int **identity;
	//base matrix b
	int **base_matrix;
	//parity check matrix h
	//each value in the vector contains 8 binary values from a row
	int **parity_check;
	//transformed version of  h
	//each value in the vector contains 8 binary values from a row
	int **trans_version_h;
    
    int **a;
    float **t;
    float **inverse_of_t;
    
   
	void extract_h();
    void create_identity( int n );
    void read_b(std::ifstream &fin);
    void see_b();
    
	void gaussian_elimination_inv_t();
	bool parity_check_b();

	void get_h_triangular_form();

	void get_sub_matrix_a();
	void get_sub_matrix_b();
	void get_sub_matrix_t();
	void get_sub_matrix_c();
	void get_sub_matrix_d();
	void get_sub_matrix_e();

    void get_p1(unsigned char *src_vector, unsigned char *p1);
	void get_p2(unsigned char *src_vector, unsigned char *p2);
};

#endif /* ENCODER_LDPCENCODER_H_ */
