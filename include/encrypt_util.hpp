#include <stdint.h>
#include "../include/util.hpp"
#include <Eigen/Dense>

/* Function Declarations */
void sub_block(Eigen::Matrix<unsigned char, 4, 4> *);
void row_shift(Eigen::Matrix<unsigned char, 4, 4> *);
void mix_columns(Eigen::Matrix<unsigned char, 4, 4> *);
void encrypt_round(Eigen::Matrix<unsigned char, 4, 4> *, int);



