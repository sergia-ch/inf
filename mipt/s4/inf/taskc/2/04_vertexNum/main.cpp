#include "tree.h"
#include "randomTree.h"
#include "treeStupidCounter.h"
#include "treeThreadCounter.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

Tree* T;

int mainRand()
{
    srand(time(NULL));
    randomTree b(10000000);

    //cout << "generated:" << endl;
    //cout << b.printTree();

    cout << "num=" << treeStupidCounter::count(&b) << endl;

    treeThreadCounter tHC;
    cout << "num1=" << tHC.count(&b, 1) << endl;

    return(0);
}

void printHelpExit(char* name)
{
    cout << "Usage: " << name << " random vertN | test threadsN | both vertN threadsN" << endl;
    exit(1);
}

int main(int argc, char** argv)
{
    if(argc <= 2)
        printHelpExit(argv[0]);

    unsigned N = atoi(argv[2]);

    if(argv[1][0] == 'r')
    {
        srand(time(NULL));
        randomTree b(N);
        cout << b.printTree() << endl;
    }
    else if(argv[1][0] == 't')
    {
        T = new Tree;
        T->readCin();

        cerr << "Using " << N << " threads" << endl;

        treeThreadCounter tHC;
        cout << tHC.count(T, N) << endl;
    }
    else if(argv[1][0] == 'b' && argc == 4)
    {
        int N1 = atoi(argv[3]);
        srand(time(NULL));
        randomTree b(N);
        treeThreadCounter tHC;
        cout << tHC.count(&b, N1) << endl;
    }
    else
        printHelpExit(argv[0]);

    return(0);
}
