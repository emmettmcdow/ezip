#include "../include/driver.hpp"
//using namespace std;
//using namespace Eigen;



extern char *optarg;
extern int optind, optopt;



void usage (void)
{
    fprintf (stderr, "Usage:\n");
    fprintf (stderr, "\t-o <operation> (choices: e - encrypt, d - decrypt, b - both/debug, -k - see keys)\n");
    fprintf (stderr, "\t-f <data input>\n\n");
    fprintf (stderr, "\t-k <key location> \n\n");
}

int main(int argc, char *argv[]) {

    /** Parse command line arguments.  */
    int c;
    char* operation;
    char* data_loc;
    char* key_loc;


    while ((c = getopt(argc, argv, "hP:o:f:k:")) != -1)
    {
        switch(c)
        {
        case 'h':
            usage ();
            exit (0);
            break;

        case 'o':
            operation = strdup (optarg);
            break;
        case 'f':
            data_loc = strdup (optarg);
            break;
        case 'k':
            key_loc = strdup (optarg);
            break;
        default:
            fprintf (stderr, "Invalid command line arguments - %c", c);
            usage ();
            exit (-1);
        }
    }


    if (*operation == 'k'){

    } else if (*operation == 'b') {
        printf("boof");
    } else if (*operation == 'e') {
        long long cnt = parse_file(data_loc);
        add_metadata(data_mtx, cnt);
        std::string s(data_loc, strlen(data_loc));
        encrypt(s);
    } else if (*operation == 'd') {
        long long cnt = parse_file(data_loc);
        std::string s(data_loc, strlen(data_loc));
        parse_key(key_loc);
        decrypt(s);
    }


}

/**
 * Decryption and Encryption (for Debugging)
 * 
 * @param original_key oops
 */
void d_and_e(unsigned int original_key[4]) {
    std::list <Eigen::Matrix<unsigned char, 4, 4>> :: iterator it; 

    printf("\n Unencrypted Data \n");
    print_list(data_mtx);

    keyexp();
    print_keys();
    for(it = data_mtx.begin(); it != data_mtx.end(); ++it) {
        Eigen::Matrix<unsigned char, 4, 4>* curr = &(*it);
        for (int i = 0; i < 10; i++) {
            encrypt_round(curr, i);
        }
    }

    printf("\n Encrypted Data \n");
    print_list(data_mtx);

    for(it = data_mtx.begin(); it != data_mtx.end(); ++it) {
        Eigen::Matrix<unsigned char, 4, 4>* curr = &(*it);
        for (int i = 9; i != -1; i--) {
            decrypt_round(curr, i);
        }
    }

    printf("\n Decrypted Data \n");
    print_list(data_mtx);

}

/**
 * Helper function to perform encryption
 * 
 * @param name name of input file
 * 
 */
void encrypt(std::string name) {
    std::list <Eigen::Matrix<unsigned char, 4, 4>> :: iterator it;
    clock_t t;
    t = clock();

    keygen(name);
    keyexp();
    print_keys();
    namespace fs = boost::filesystem;

    fs::path pth{name};
    pth = pth.filename();
    std::string newname = pth.string();
    newname = newname.append(".ezip");
    std::ofstream datafile(newname);
    long long length = 0;

    for(it = data_mtx.begin(); it != data_mtx.end(); ++it) {
        length += 16;
        Eigen::Matrix<unsigned char, 4, 4>* curr = &(*it);
        for (int i = 0; i < 10; i++) {
            encrypt_round(curr, i);
        }

        for(int r = 0; r < 4; r++) {
            for(int c = 0; c < 4; c++) {
                datafile  << it->array()(r,c);
            }
        }

    }


    datafile.close();
    t = clock() - t;
    printf("\n Encrypted ~%d Bytes in %f seconds\n", length, (float)t/CLOCKS_PER_SEC);
}

/**
 * Helper function to perform decryption 
 * 
 * @param name name of the input file
 */
void decrypt(std::string name) {
    clock_t t;
    t = clock();
    printf("\nEncrypting...\n");
    std::list <Eigen::Matrix<unsigned char, 4, 4>> :: iterator it; 

    keyexp();
    print_keys();
    namespace fs = boost::filesystem;

    fs::path pth{name};
    pth = pth.filename();
    std::string newname = pth.string();
    newname = newname.substr(0, newname.length() - 5);
    std::ofstream datafile(newname);

    unsigned long long count = 0;
    char * byte;

    for(it = data_mtx.begin(); it != data_mtx.end(); ++it) {
        Eigen::Matrix<unsigned char, 4, 4>* curr = &(*it);
        for (int i = 9; i != -1; i--) {
            decrypt_round(curr, i);
        }
    }
    unsigned long long length = parse_metadata();
    for(it = data_mtx.begin(); it != data_mtx.end(); ++it) {
        Eigen::Matrix<unsigned char, 4, 4>* curr = &(*it);
        for(int r = 0; r < 4; r++) {
            for(int c = 0; c < 4; c++) {
                if (count < length) {
                    count += 1;
                    byte = (char *)&(it->array()(r,c));
                    datafile.write((byte), 1);
                }
            }
        }
    }


    datafile.close();
    t = clock() - t;
    printf("\n Decrypted %d Bytes in %f seconds\n", length, (float)t/CLOCKS_PER_SEC);
}