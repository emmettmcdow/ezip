//#include <stdint.h>
#include "encrypt_util.hpp"

#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))

using namespace Eigen;
 



void sub_block(Matrix<unsigned char, 4, 4> *input_matrix) {
    int new_value = -1;
    for (int row = 0; row < 4; row++) {
        for (int column = 0; column < 4; column++){
            new_value = sbox[(int)input_matrix->array()(row, column)];
            input_matrix->array()(row, column) = new_value;
        }
    }
}

void row_shift(Matrix<unsigned char, 4, 4> *input_matrix) {
    Matrix<int, 4, 4> one_shift_s;
    one_shift_s << 0, 0, 0, 1,
                 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0;

    Matrix<int, 4, 4> two_shift_s;
    two_shift_s << 0, 0, 1, 0,
                 0, 0, 0, 1,
                 1, 0, 0, 0,
                 0, 1, 0, 0;
    
    Matrix<int, 4, 4> three_shift_s;
    three_shift_s << 0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1,
                   1, 0, 0, 0;
    
    
    input_matrix->row(1) = ((*input_matrix).cast<int>() * one_shift_s).row(1).cast<unsigned char>();
    input_matrix->row(2) = ((*input_matrix).cast<int>() * two_shift_s).row(2).cast<unsigned char>();
    input_matrix->row(3) = ((*input_matrix).cast<int>() * three_shift_s).row(3).cast<unsigned char>();

}



void mix_columns(Matrix<unsigned char, 4, 4> *input_matrix) {
    Matrix<unsigned char, 4, 4> a = *input_matrix;
    for (int c = 0; c < 4; c++) {

        input_matrix->array()(0, c) = gmul(a.array()(0,c),2) ^ gmul(a.array()(3,c),1) ^ gmul(a.array()(2,c),1) ^ gmul(a.array()(1,c),3);
        input_matrix->array()(1, c) = gmul(a.array()(1,c),2) ^ gmul(a.array()(0,c),1) ^ gmul(a.array()(3,c),1) ^ gmul(a.array()(2,c),3);
        input_matrix->array()(2, c) = gmul(a.array()(2,c),2) ^ gmul(a.array()(1,c),1) ^ gmul(a.array()(0,c),1) ^ gmul(a.array()(3,c),3);
        input_matrix->array()(3, c) = gmul(a.array()(3,c),2) ^ gmul(a.array()(2,c),1) ^ gmul(a.array()(1,c),1) ^ gmul(a.array()(0,c),3);

    }

}