#include <iostream>
#include <vector>
#include "Pool.h"
using namespace std;
int main() {
    vector <string> filenames = {
            "movies.txt",
            "tv_shows.txt",
            "livestreams.txt"
    };
    Pool *pool = new Pool();
    *pool+=filenames; //using overloading operator '+=' to load the pool from filenames
    pool->menu();
    return 0;
}