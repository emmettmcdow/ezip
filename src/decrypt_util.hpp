#include <stdint.h>
#include <Eigen/Dense>
#include "encrypt_util.hpp"

/* Function Declarations */
void sub_block_i(Eigen::Matrix<unsigned char, 4, 4> *);
void row_shift_i(Eigen::Matrix<unsigned char, 4, 4> *);
void mix_columns_i(Eigen::Matrix<unsigned char, 4, 4> *);