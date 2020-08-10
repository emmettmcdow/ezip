#include "main.hpp"
using namespace std;
using namespace Eigen;

fstream inf;

extern char *optarg;
extern int optind, optopt;



void usage (void)
{
    fprintf (stderr, "Usage:\n");
    fprintf (stderr, "\t-o <operation> (choices: e - encrypt, d - decrypt, b - both/debug)\n");
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

    unsigned char byte;
    Matrix<unsigned char, 4, 4> data_matrix;
    int row = 0;
    int col = 0;

    printf("\nInput Data: \n");
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

    mix_columns(&data_matrix);
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
    }



}