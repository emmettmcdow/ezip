//#include <stdint.h>
#include "encrypt_util.hpp"

/**
 * Substitute each byte in the data-matrix for another in the Rijndael S-block
 * @param input_matrix data-matrix to be subbed
 * 
 */
void sub_block(Eigen::Matrix<unsigned char, 4, 4> *input_matrix) {
    int new_value = -1;
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 4; column++){
            new_value = sbox[(int)input_matrix->array()(row, column)];
            input_matrix->array()(row, column) = new_value;
        }
    }
}

/**
 * Shift the data-matrix in the following way
 *     1 0 0 0 << 0
 *     0 1 0 0 << 1
 *     0 0 1 0 << 2
 *     0 0 0 1 << 3
 * 
 * @param input_matrix matrix to be shifted
 *     
 */
void row_shift(Eigen::Matrix<unsigned char, 4, 4> *input_matrix) {
    Eigen::Matrix<int, 4, 4> one_shift_s;
    one_shift_s << 0, 0, 0, 1,
                 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0;

    Eigen::Matrix<int, 4, 4> two_shift_s;
    two_shift_s << 0, 0, 1, 0,
                 0, 0, 0, 1,
                 1, 0, 0, 0,
                 0, 1, 0, 0;
    
    Eigen::Matrix<int, 4, 4> three_shift_s;
    three_shift_s << 0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1,
                   1, 0, 0, 0;
    
    
    input_matrix->row(1) = ((*input_matrix).cast<int>() * one_shift_s).row(1).cast<unsigned char>();
    input_matrix->row(2) = ((*input_matrix).cast<int>() * two_shift_s).row(2).cast<unsigned char>();
    input_matrix->row(3) = ((*input_matrix).cast<int>() * three_shift_s).row(3).cast<unsigned char>();

}

/**
 * Mix the columns of the data matrix using the transformation matrix
 *     2 3 1 1
 *     1 2 3 1
 *     1 1 2 3
 *     3 1 1 2
 * Multiply according the the Galois field
 * @param input_matrix data-matrix to be mixed
 * 
 */
void mix_columns(Eigen::Matrix<unsigned char, 4, 4> *input_matrix) {
    Eigen::Matrix<unsigned char, 4, 4> a = *input_matrix;
    for (int c = 0; c < 4; c++) {

        input_matrix->array()(0, c) = gmul(a.array()(0,c),2) ^ gmul(a.array()(3,c),1) ^ gmul(a.array()(2,c),1) ^ gmul(a.array()(1,c),3);
        input_matrix->array()(1, c) = gmul(a.array()(1,c),2) ^ gmul(a.array()(0,c),1) ^ gmul(a.array()(3,c),1) ^ gmul(a.array()(2,c),3);
        input_matrix->array()(2, c) = gmul(a.array()(2,c),2) ^ gmul(a.array()(1,c),1) ^ gmul(a.array()(0,c),1) ^ gmul(a.array()(3,c),3);
        input_matrix->array()(3, c) = gmul(a.array()(3,c),2) ^ gmul(a.array()(2,c),1) ^ gmul(a.array()(1,c),1) ^ gmul(a.array()(0,c),3);

    }

}

/**
 * Helper function to encrypt for a singular round 
 * 
 * @param input_matrix particular data matrix to perform encryption on
 * @param round round of encryption
 */
void encrypt_round(Eigen::Matrix<unsigned char, 4, 4> *input_matrix, int round){
    if (round == 0) { add_round_key(input_matrix, round); };
    sub_block(input_matrix);
    row_shift(input_matrix);
    if (round != 9) { mix_columns(input_matrix); };
    add_round_key(input_matrix, round);
}
