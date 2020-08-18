#include "encrypt_util.hpp"
#include "decrypt_util.hpp"
#include "util.hpp"
#include <iostream>

#include <stdarg.h>
#include <unistd.h>

#include <list> 
#include <iterator> 
#include <time.h> 

void d_and_e(unsigned int[4]);
void encrypt(std::string);
void decrypt(std::string);