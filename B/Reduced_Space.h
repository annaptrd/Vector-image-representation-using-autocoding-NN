#include <vector>
#include <string>

#ifndef Reduced_Space_H
#define Reduced_Space_H

using namespace std;

void find_true_neighbors_of_new_space(vector<vector <int> > input_vector_new_space,vector<vector <int> > query_vector_new_space,vector <int>* true_best_neighbor_new_space,vector <int>* true_best_distance_new_space);

double Calculate_Average(vector <int> reduced_neighbors,string input_labels_file,string query_labels_file);

#endif
