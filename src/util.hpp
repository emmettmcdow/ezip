#include <stdint.h>
#include <Eigen/Dense>
#include <list> 
#include <iterator> 
#include <iostream>
#include<fstream>
#include <regex>
#include <iomanip>
#include <boost/filesystem.hpp>

//using namespace Eigen;
//using namespace std;

extern uint8_t sbox[];
extern unsigned int keys[];
extern unsigned int curr_round;
extern std::list<Eigen::Matrix<unsigned char, 4,4>> data_mtx;

void keyexp();
unsigned int rot_word(unsigned int);
unsigned int sub_word(unsigned int);
unsigned char gmul(unsigned char, unsigned char);
void add_round_key(Eigen::Matrix<unsigned char, 4, 4>*, int);
void print_list(std::list<Eigen::Matrix<unsigned char, 4, 4>>);
unsigned int* parse_key(char*);
long long parse_file(char *);
void print_keys();
void add_metadata(std::list<Eigen::Matrix<unsigned char, 4, 4>>, long long);
void keygen(std::string);
unsigned long long parse_metadata();