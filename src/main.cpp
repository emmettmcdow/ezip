#include "main.hpp"
//using namespace std;
//using namespace Eigen;



extern char *optarg;
extern int optind, optopt;



void usage (void)
{
    fprintf (stderr, "Usage:\n");
    fprintf (stderr, "\t-o <operation> (choices: e - encrypt, d - decrypt, b - both/debug, -k - see keys)\n");
    fprintf (stderr, "\t-f <data input>\n\n");
    fprintf (stderr, "\t-k <key location> \n\n")
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
    
    }


}