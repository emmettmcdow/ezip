#include <stdint.h>
#include <Eigen/Dense>

extern uint8_t sbox[];

unsigned int *keygen(unsigned int[4]);
unsigned int rot_word(unsigned int);
unsigned int sub_word(unsigned int);
unsigned char gmul(unsigned char, unsigned char);