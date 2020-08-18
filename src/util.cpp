#include "util.hpp"
//using namespace Eigen;
#include <list> 
#include <iterator>

unsigned char rc[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

uint8_t sbox[] =  {
 0x63 ,0x7c ,0x77 ,0x7b ,0xf2 ,0x6b ,0x6f ,0xc5 ,0x30 ,0x01 ,0x67 ,0x2b ,0xfe ,0xd7 ,0xab ,0x76
 ,0xca ,0x82 ,0xc9 ,0x7d ,0xfa ,0x59 ,0x47 ,0xf0 ,0xad ,0xd4 ,0xa2 ,0xaf ,0x9c ,0xa4 ,0x72 ,0xc0
 ,0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15
 ,0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75
 ,0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84
 ,0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf
 ,0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8
 ,0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2
 ,0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73
 ,0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb
 ,0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79
 ,0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08
 ,0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a
 ,0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e
 ,0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf
 ,0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16};

unsigned int keys[40];
unsigned int ogkey[4];
unsigned int curr_round;
std::list <Eigen::Matrix<unsigned char, 4, 4>> data_mtx;

/**
 * Singular circular left shift on a word
 * @param input Word to be rotated
 * @return Rotated word
 * 
 */
unsigned int rot_word(unsigned int input) {
    unsigned int filter = 0xFF000000;
    filter = (filter & input) >> 24;
    unsigned int nu = input;
    nu = nu << 8;
    //printf("\n%u", input);
    //printf("\n%u", nu | filter);
    return (nu | filter);
}

/**
 * Substitutes every byte in the inputted word with a byte from Rijndael's S-Box
 * @param input byte to be replaced
 * @return replaced word
 */ 
unsigned int sub_word(unsigned int input) {
    unsigned int filter_0 = 0x000000FF;    
    unsigned int filter_1 = 0x0000FF00;
    unsigned int filter_2 = 0x00FF0000; 
    unsigned int filter_3 = 0xFF000000;

    //printf("\n%u", input);
    //printf("\n%u", (filter_0 & input));
    filter_0 = sbox[(filter_0 & input)];
    filter_1 = sbox[(filter_1 & input) >> 8];
    //printf("\n%u", filter_1 & input);
    filter_2 = sbox[(filter_2 & input) >> 16];
    //printf("\n%u", filter_2 & input);
    filter_3 = sbox[(filter_3 & input) >> 24];
    //printf("\n%u", filter_3 & input);

    return (filter_0) |
           ((filter_1) << 8) |
           ((filter_2) << 16) |
           ((filter_3) << 24);
            
}

/**
 * Generate 10 round keys from original key
 * @param original_key inputted original key
 * 
 */
void keyexp() {
    int N = 4;
    int i = 0;
    //unsigned int words[44];
    while (i < 40){
        if (i < N) {
            keys[i] = ogkey[i];
            i++;
        } else if (i % N == 0) {
            keys[i] = keys[i - N] ^ (sub_word(rot_word(keys[i-1]))) ^ rc[i / N];
            i+=1;
        } else if (i >= N && N > 6 && (i % N) == (4 % N)) {
            keys[i] = keys[i -N] ^ sub_word(keys[i-1]);
            i++;
        } else {
            keys[i] = keys[i - N] ^ keys[i - 1];
            i++;
        }
    }
/*     for (int i = 0; i < 11; i++) {
        keys[i] += (static_cast<__int128_t>(words[i])) << 96;
        keys[i] += (static_cast<__int128_t>(words[4*i+1])) << 64;
        keys[i] += (static_cast<__int128_t>(words[4*i+2])) << 32;
        keys[i] += (static_cast<__int128_t>(words[4*i+3]));

    } */


}

/**
 * Galois Field Multiplication
 * @param a first term in the multiplication
 * @param b second term in the multiplication
 * @return product of a*b
 */
unsigned char gmul(unsigned char a, unsigned char b) {
	unsigned char p = 0;
	unsigned char counter;
	unsigned char hi_bit_set;
	for(counter = 0; counter < 8; counter++) {
		if((b & 1) == 1) 
			p ^= a;
		hi_bit_set = (a & 0x80);
		a <<= 1;
		if(hi_bit_set == 0x80) 
			a ^= 0x1b;		
		b >>= 1;
	}
	return p;
}

/**
 * Adds the current round key to a single data-matrix
 * @param *input pointer to the single data-matrix
 * 
 */
void add_round_key(Eigen::Matrix<unsigned char, 4, 4> *input, int round) {
    int cri = 4*round;
    for (int i = 0; i < 4; i++) {
        cri += i;
        input->array()(i, 0) ^= (keys[(cri)] & 0xFF000000) >> 24;
        input->array()(i, 1) ^= (keys[(cri)] & 0x00FF0000) >> 16;
        input->array()(i, 2) ^= (keys[(cri)] & 0x0000FF00) >> 8;
        input->array()(i, 3) ^= (keys[(cri)] & 0x000000FF);
    }
}


/**
 * Helpter function to print all of the data in the list of data-matrices provided
 * @param matrix_list list of all the data-matrices
 * 
 */
void print_list(std::list <Eigen::Matrix<unsigned char, 4, 4>> matrix_list) { 

    std::list <Eigen::Matrix<unsigned char, 4, 4>> :: iterator it; 
    for(it = matrix_list.begin(); it != matrix_list.end(); ++it) {
        for(int r = 0; r < 4; r++) {
            for(int c = 0; c < 4; c++) {
                std::cout  <<" "<< std::setw(2) << std::setfill('0') << std::hex << static_cast<int> (it->array()(r,c));
            }
            printf("\n");
        }
        printf("\n");
    }
}

/**
 * Helper function to parse and store the inputted key
 * @param key_loc pointer to the string representing the location of the key
 * @return the processed original key
 */
unsigned int* parse_key(char* key_loc) {
    std::fstream ink;

    ink.open(key_loc, std::ifstream::in);
    if (ink.fail()) {
        printf("\nFailed to open key\n");
        return NULL;
    }

    std::string byte;
    std::string str = "";
    std::regex valid ("[A-F0-9]*");
    //printf("\n Original Data: \n");
    while(ink.good()) {
        ink >> byte;

        //std::cout << std::hex << byte << std::endl;

        str.append(byte);

    }
    ink.close();

    if (!std::regex_match(str, valid)) {
        printf("\n INVALID KEY\n");
        return NULL;
    }

    unsigned int *newkey = new unsigned int[4];
    newkey[0] = std::stol(str.substr(0,8), 0, 16);
    newkey[1] = std::stol(str.substr(8,8), 0, 16);
    newkey[2] = std::stol(str.substr(16,8), 0, 16);
    newkey[3] = std::stol(str.substr(24,8), 0, 16);
    std::cout <<"\n Input Key: "<< newkey[0] << newkey[1] << newkey[2] << newkey[3] << std::endl;

    return newkey;
}
/**
 * Helper function to parse file
 * @param data_loc pointer to string representing the location of data
 * @return data in data-matrix-list form
 * 
 */
long long parse_file(char *data_loc) {
    std::ifstream inf;
    inf.open(data_loc, std::ios::binary);
    if (inf.fail()) {

        return -1;
    }

    curr_round = 0;
    char byte;
    data_mtx.push_back(Eigen::Matrix<unsigned char, 4, 4>());
    int row = 0;
    int col = 0;
    long long count = 0;



    while(true){
        inf.read(&byte, 1);
        if (inf.eof()) break;
        data_mtx.back().array()(row, col) = (unsigned char) byte;

        col += 1;
        if (col > 3) {
            row += 1;
            col = 0;
        }
        if (row > 3) {
            row = 0;
            col = 0;
            data_mtx.push_back(Eigen::Matrix<unsigned char, 4, 4>());
        }

        count += 1;
        
    }
    inf.close();
    if (row == 0 && col == 0) {
        data_mtx.pop_back();
    } else {
        while (row != 0 || col != 0) {
            data_mtx.back().array()(row, col) = (unsigned char)48;
            col += 1;
            if (col > 3) {
                row +=1;
                col = 0;
            }
            if (row > 3) {
                row = 0;
                col = 0;
            }
        }
    }



    return count;
}
/**
 * Helper Function to print the keys 
 * 
 */
void print_keys() {
    printf("\n\n Generated Keys: \n");
    for (int i = 0; i < 40; i += 1) {
        std::cout <<" "<< std::setw(8) << std::setfill('0') << std::hex << static_cast<int>(keys[i]);
        if ((i + 1) % 4 == 0) {printf("\n");};
    }
    printf("\n");
}
/**
 * Adds metadata to the data_matrix. This metadata contains the length of the encrypted data.
 * 
 * @param list data_matrix to use
 * @param count length of the data in bytes
 * 
 */
void add_metadata(std::list<Eigen::Matrix<unsigned char, 4, 4>> list, long long count) {
    long long filter = 0xFF00000000000000;
    int shift = 56;
    data_mtx.push_back(Eigen::Matrix<unsigned char, 4,4>());
    for (int i = 0; i < 8; i++) {
        data_mtx.back().array()(i/4, i%4) = (count & filter) >> shift;
        data_mtx.back().array()(i/4 + 2, i%4) = (unsigned char)0;
        shift -= 8;
        filter = filter >> 8;
    }
}

/**
 * Parses the metadata at the end of the encrypted file. This will result in the length
 * in bytes of the data_matrix 
 * 
 * @return the length in bytes of the data matrix
 * 
 */
unsigned long long parse_metadata() {
    unsigned long long rtn = 0;
    int shift = 56;
    for (int i = 0; i < 8; i++) {
        unsigned long long value = static_cast<int>(data_mtx.back().array()(i/4, i%4));
        rtn += value << shift;
        shift -= 8;
    }
    printf("\n length: %d", rtn);
    return rtn;
}

/**
 * Generates a key to use
 * 
 * @param nom name to use for the output file.
 */
void keygen(std::string nom) {
    ogkey[0] = 0;
    ogkey[1] = 0;
    ogkey[2] = 0;
    ogkey[3] = 0;

    namespace fs = boost::filesystem;
    fs::path pth{nom};

    pth = pth.filename();
    std::string name = pth.string();
    std::ofstream keyfile(name.append(".key"));

    // Write to the file
    keyfile << std::hex << "00000000000000000000000000000000";

    // Close the file
    keyfile.close();
}