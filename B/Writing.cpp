#include "Writing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void Writing_to_the_output_file(string output_file, int query, int reduced_neighbor,int LSH_neighbor,int true_neighbor,int distance_Reduced,int distance_LSH,int distanceTrue) {
    ofstream ofile;
    ofile.open(output_file, fstream::app);
    ofile << "Query: " << query + 1 << "\n";
    ofile << "Nearest neighbor Reduced: " <<reduced_neighbor<< "\n";
    ofile << "Nearest neighbor LSH: " <<LSH_neighbor<< "\n";
    ofile << "Nearest neighbor True: " <<true_neighbor<< "\n";
    ofile << "Distance Reduced: " <<distance_Reduced<< "\n";
    ofile << "DistanceLSH: " <<distance_LSH<< "\n";
    ofile << "DistanceTrue: " <<distanceTrue<< "\n";

    ofile.close();

}
