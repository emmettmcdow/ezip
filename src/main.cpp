#include "main.hpp"
using namespace std;
using namespace Eigen;

fstream inf;

extern char *optarg;
extern int optind, optopt;



void usage (void)
{
    fprintf (stderr, "Usage:\n");
    fprintf (stderr, "\t-o <operation> (choices: e - encrypt, d - decrypt, b - both/debug, -k - see keys)\n");
    fprintf (stderr, "\t-f <data input>\n\n");
}

int main(int argc, char *argv[]) {

    /** Parse command line arguments.  */
    int c;
    char* operation;
    char* data_loc;


    while ((c = getopt(argc, argv, "hP:o:f:")) != -1)
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
        default:
            fprintf (stderr, "Invalid command line arguments - %c", c);
            usage ();
            exit (-1);
        }
    }


    inf.open(data_loc, ifstream::in);
    if (inf.fail()) {
        printf("\nFailed to open file\n");
        return 1;
    }
    if (*operation == 'k'){
        string byte;
        string str = "";
        regex valid ("[A-F0-9]*");
        printf("\n Original Data: \n");
        while(inf.good()) {
            inf >> byte;

            cout << hex << byte << endl;

            str.append(byte);

        }
        inf.close();

        if (!regex_match(str, valid)) {
            printf("\n INVALID KEY\n");
            return -1;
        }

        unsigned int newkey[4];
        newkey[0] = stol(str.substr(0,8), 0, 16);
        newkey[1] = stol(str.substr(8,8), 0, 16);
        newkey[2] = stol(str.substr(16,8), 0, 16);
        newkey[3] = stol(str.substr(24,8), 0, 16);

/*         ss << hex << str.substr(8,8);
        cout << str.substr(8,8) << endl;
        ss >> newkey[1];

        ss << hex << str.substr(16,8);
        cout << str.substr(16,8) << endl;
        ss >> newkey[2];

        ss << hex << str.substr(24,8);
        cout << str.substr(24,8) << endl;
        ss >> newkey[3]; */
        printf("\n Parsed Key");
        printf("\n%d", newkey[0]);
        printf("\n%d", newkey[1]);
        printf("\n%d", newkey[2]);
        printf("\n%d", newkey[3]);

        printf("\n\n Generated Keys: \n");
        keygen(newkey);
        for (int i = 0; i < 44; i += 1) {
            cout <<" "<< setw(8) << setfill('0') << hex << static_cast<int>(keys[i]);
            if ((i + 1) % 4 == 0) {printf("\n");};
        }
        printf("\n");


        

    } else if (*operation == 'b') {
        printf("\nInput Data: \n");
        unsigned char byte;
        Matrix<unsigned char, 4, 4> data_matrix;
        int row = 0;
        int col = 0;
        while(inf.good()) {
            if(row > 3) {
                break;
            }

            inf >> byte;

            printf("%d ", byte);

            data_matrix.array()(row, col) = byte;

            col += 1;
            if (col > 3) {
                printf("\n");
                row += 1;
                col = 0;
            }
        }
        inf.close();

    /*     sub_block(&data_matrix);
        printf("\nSubbed Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        }

        sub_block_i(&data_matrix);
        printf("\nDesubbed Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        } */

    /*     row_shift(&data_matrix);
        printf("\nShifted Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        }

        row_shift_i(&data_matrix);
        printf("\nUnshifted Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        } */

    /*     mix_columns(&data_matrix);
        printf("\nMixed Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        }

        mix_columns_i(&data_matrix);
        printf("\nUnmixed Data:\n");
        for(int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                printf("%d ", data_matrix.array()(row, col));
            }
            printf("\n");
        } */
    }






}