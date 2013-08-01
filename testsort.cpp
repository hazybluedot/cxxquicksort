#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <vector>
#include <random>

#include "util.h"
#include "quicksort.h"

using std::vector;
using std::cout;
using std::endl;

bool verbose=false;
bool quiet=false;

int main(int argc, char* argv[]) {
    int opt, N=10;
    int algorithm = 1;
    while((opt = getopt(argc, argv, "vqn:N:a:")) != -1) {
	switch(opt) {
	case 'v':
	    verbose = true; break;
	case 'q':
	    quiet = true; break;
	case 'n':
	case 'N':
	    N = atoi(optarg); break;
        case 'a':
            algorithm = atoi(optarg); break;
	default:
	    fprintf(stderr, "Usage: %s [-N size] [-v] [-q]\n",
		    argv[0]);
	    exit(EXIT_FAILURE);
	}
    }

    vector<int> stuff(N);
    std::generate(stuff.begin(), stuff.end(), Enumerator<int>(1));
    std::random_shuffle(stuff.begin(), stuff.end());

    if (!quiet)
	cout << "Initial Stuff: " << streamifier(stuff) << endl;
    int passes = 0;
    if (verbose)
        cout << "Algorithm " << algorithm << std::endl;
    if (algorithm == 1)
        passes = quicksort(stuff.begin(), stuff.end());
    else if (algorithm == 2)
        passes = quicksort2(stuff.begin(), stuff.end());
    else if (algorithm == 3)
        passes = quicksort3(stuff.begin(), stuff.end());
    else
        passes = quicksort4(stuff.begin(), stuff.end());

    if (!quiet) {
	cout << "Sorted Stuff: " << streamifier(stuff) << endl;
	cout << "With " << passes << " passes" <<endl;
    }
}
