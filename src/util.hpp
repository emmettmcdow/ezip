#include <stdint.h>
#include <Eigen/Dense>
#include <list> 
#include <iterator> 
#include <iostream>
#include<fstream>
#include <regex>
#include <iomanip>

//using namespace Eigen;
//using namespace std;

extern uint8_t sbox[];
extern unsigned int keys[];
extern unsigned int curr_round;
extern std::list<Eigen::Matrix<unsigned char, 4,4>> data_mtx;

void keygen(unsigned int[4]);
unsigned int rot_word(unsigned int);
unsigned int sub_word(unsigned int);
unsigned char gmul(unsigned char, unsigned char);
void add_round_key(Eigen::Matrix<unsigned char, 4, 4>*, int);
void print_list(std::list<Eigen::Matrix<unsigned char, 4, 4>>);
unsigned int* parse_key(char*);
std::list <Eigen::Matrix<unsigned char, 4, 4>>* parse_file(char *);
void print_keys();
