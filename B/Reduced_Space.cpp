#include "Reduced_Space.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include "Nearest_Neighbor.h"
#include "Reading.h"

void find_true_neighbors_of_new_space(vector<vector <int> > input_vector_new_space,vector<vector <int> > query_vector_new_space,vector <int>* true_best_neighbor_new_space,vector <int>* true_best_distance_new_space){
	//cout<<"query_vector_new_space.size()"<<query_vector_new_space.size()<<endl;
	for(int i=0;i<(int) query_vector_new_space.size();i++){//gia ola ta query
		//cout<<"For query "<<i<<endl;
		int true_best_distance=0;
		int true_best_neighbor;
		find_the_true_distance(input_vector_new_space,query_vector_new_space[i],&true_best_distance,&true_best_neighbor);//psaxnoume se olo to dataset gia na broume to geitona
		//cout<<"BEST NEIGHBOR="<<true_best_neighbor<<"  and BEST DISTANCE="<<true_best_distance<<endl;
		(*true_best_neighbor_new_space).push_back(true_best_neighbor);
		(*true_best_distance_new_space).push_back(true_best_distance);
	}
}

double Calculate_Average(vector <int> reduced_neighbors,string input_labels_file,string query_labels_file){//synarthsh gia sygkriseis metaksy B kai C wste na ypologistei to average sto reduced xwro
	vector <int> input_labels;
	vector <int> query_labels;
	Read_Labels(input_labels_file,&input_labels);
	Read_Labels(query_labels_file,&query_labels);
	double average=0.0;
	for(int i=0;i< int (query_labels.size()) ; i++){//
		//cout<<"LABEL="<<input_labels[reduced_neighbors[i]]<<endl;
		if(input_labels[reduced_neighbors[i]]==query_labels[i]){
			average+=1.0;
		}
	}
	average/=double(query_labels.size());
	return average;
}
