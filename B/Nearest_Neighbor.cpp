#include "Nearest_Neighbor.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"

#include <iostream>

using namespace std;

void find_the_true_distance(vector <vector <int> > input_vector, vector <int> query, int* true_best_distance,int* true_nearest_neighbor) {//euresh kontinotero geitona se olo to dataset
    for (unsigned pic = 0; pic < input_vector.size(); pic++) {
        int distance = Manhattan_Distance(query, input_vector[pic]);
        if(*true_best_distance==0){//ama eimaste sth prvth epanalipsi
        	//cout<<"Distance="<<distance<<endl;
        	*true_best_distance=distance;
        	*true_nearest_neighbor=pic;
        }
        else{
        	if(distance<*true_best_distance){//ama brikame neo kalytero geitona tote aytos einai o proswrinos best
        		//cout<<"Distance="<<distance<<endl;
        		*true_best_distance=distance;
        		*true_nearest_neighbor=pic;
        	}
        }
    }
}
