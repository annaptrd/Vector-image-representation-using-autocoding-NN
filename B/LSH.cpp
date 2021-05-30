#include <iostream>
#include <fstream>
#include <algorithm>
#include <sys/time.h>

#include "LSH.h"
#include "Hash.h"
#include "Nearest_Neighbor.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include "../Functions_for_both_algorithms/h_Function.h"
#include "Writing.h"


void Hash_The_Train_File(vector <vector <vector <int> > > *all_h_values_of_all_g, vector <Hash> *g_hash, vector<vector <int> > input_vector, int Num_of_Buckets, int L, int k, int M, vector <int> modulo_Exponents_of_m, int W) {
    int size = input_vector[0].size();
    int TRAIN_IMAGES = input_vector.size();
    Hash g_h(Num_of_Buckets);
    for (int g = 0; g < L; g++) {//kataskeyh twn g hashtables gia ta train images
        (*g_hash).push_back(g_h); //h domh einai ena vector apo antikeimena hash(dld ena vector poy sth kathe thesi exei deikth poy deixnei se lista)
        vector <vector <int> > h_function;
        random_numbers_generating(&h_function, k, W, size); //apothikeyoume sto vector h_function toys tyxaioys arithmoys s gia tis k h
        (*all_h_values_of_all_g).push_back(h_function); //prosthetoume ola ta si twn k h wste na xrhsimopoihthoun kai apo ta query
        for (int picture = 0; picture < TRAIN_IMAGES; picture++) {//gia oles tis eikones
            vector <int> h_values;
            Compute_the_values_of_h(&h_values, input_vector[picture], h_function, k, M, modulo_Exponents_of_m, W);
            unsigned int value_of_g = Compute_the_value_of_g(h_values, k);
            //cout<<"Value="<<value_of_g<<endl;
            (*g_hash)[g].InsertItem(picture, value_of_g);
        }
        //cout << "teleiwse h g = " << g << endl;
    }
}

void Compute_the_values_of_h(vector <int>* h_values, vector <int> p, vector <vector<int> > h_function, int k, int M, vector <int> modulo_Exponents_of_m, int W) {
    int size = p.size();
    for (int h = 0; h < k; h++) {//gia kathe h
        vector <int> a;
        for (int dimension = 0; dimension < size; dimension++) {//gia oles tis diastaseis
            int sub = p[dimension] - h_function[h][dimension]; //ypologismos toy pi-si
            float result = sub / W;
            if (sub >= 0) {//ypologismos tou floor
                a.push_back((int) result);
            } else {//ypologismos tou floor an exoyme arnhtiko
                a.push_back(((int) result) - 1);
            }
        }
        int value_of_h = Compute_the_value_of_h(a, modulo_Exponents_of_m, M, size); //kalesma ths synarthshs gia ton ypologismo ths eksiswshs sth selida 20
        (*h_values).push_back(value_of_h);
    }
}

unsigned int Compute_the_value_of_g(vector <int> h_values, int k) {
    int metatopisi = (int) 32 / k; //xrhsimopoeitai gia to concatenation
    unsigned int num_of_bucket;
    for (int h = 0; h < k; h++) {
        if (h == 0) {
            num_of_bucket = h_values[0];
        } else {
            num_of_bucket = (num_of_bucket) | (h_values[h] << (metatopisi * h)); //analogws poses h exoume tha metakinountai metatopish*h bits kathe fora
        }
    }
    return num_of_bucket;
}

void Hash_The_Queries_And_Calculate_Neighbors(vector<vector <int> > input_vector, vector<vector <int> > query_vector, vector <vector <vector <int> > > all_h_values_of_all_g, vector <Hash> g_hash, int k, int L, int M, vector <int> modulo_Exponents_of_m, int W, string output_file,vector <int> reduced_neighbors,vector <int> reduced_distances,double time_reduced) {
    int QUERY_IMAGES = query_vector.size();
    double sum_reduced=0.0;
    double sum_LSH=0.0;
    double timeLSH = 0.0;
    double timeTRUE = 0.0;
    for (int query = 0; query < QUERY_IMAGES; query++) {
        int best_distance=0;
        int nearest_neighbor;
        int LSH_neighbor;
        int LSH_distance;
        double lsh_for_query=0.0;
        for (int g = 0; g < L; g++) {
            vector <int> h_values;
            Compute_the_values_of_h(&h_values, query_vector[query], all_h_values_of_all_g[g], k, M, modulo_Exponents_of_m, W);
            unsigned int value_of_g = Compute_the_value_of_g(h_values, k);
            cout << "query=" << query << "  g=" << g << " value_of_g=" << value_of_g << endl;
            int index = g_hash[g].hashFunction(value_of_g);
            vector <int> pictures_of_bucket;
            
            clock_t start = clock();
            g_hash[g].Loadhash(&pictures_of_bucket, index);
            Calculate_The_LSH_Neighbor(pictures_of_bucket, query, query_vector[query], input_vector, &nearest_neighbor, &best_distance);
			clock_t end = clock();
			lsh_for_query += double(end - start)/CLOCKS_PER_SEC;
            
            cout<<"Neighbor="<<nearest_neighbor<<" and distance="<<best_distance<<"\n"<<endl;
            if(g==0){ //briskoume ton kalytero lsh geitona
            	LSH_neighbor=nearest_neighbor;
            	LSH_distance=best_distance;
            }
            else{
            	if(best_distance<LSH_distance){
            		LSH_neighbor=nearest_neighbor;
            		LSH_distance=best_distance;
            	}
            }
            
        }
        if(L>3){
        	timeLSH+=lsh_for_query/(L-2);
        }
        else{
        	timeLSH+=lsh_for_query;
        }
        cout<<"Final lsh="<<best_distance<<endl<<endl;

        clock_t start = clock();
        int true_best_distance=0;
        int true_nearest_neighbor;
        find_the_true_distance(input_vector, query_vector[query], &true_best_distance,&true_nearest_neighbor);
        cout<<"The true distance="<<true_best_distance<<" and the true_nearest_neighbor="<<true_nearest_neighbor<<endl;
        clock_t end = clock();
		timeTRUE += double(end - start)/CLOCKS_PER_SEC;
		
    	sum_reduced+= ( (double)reduced_distances[query] / (double)true_best_distance );
    	cout<<"Sum_Reduced="<<sum_reduced<<endl;
    	sum_LSH+=( (double)LSH_distance / (double)true_best_distance );
    	cout<<"sum_LSH="<<sum_LSH<<endl;
    	
        Writing_to_the_output_file(output_file,query,reduced_neighbors[query],LSH_neighbor,true_nearest_neighbor,reduced_distances[query],LSH_distance,true_best_distance);
    }
    sum_reduced/=QUERY_IMAGES; //ypologizetai aproximation factor toy reduced
    sum_LSH=sum_LSH/QUERY_IMAGES; //ypologizetai aproximation factor toy lsh
	ofstream ofile;
    ofile.open(output_file, fstream::app);
    ofile<<"\n"<<"tReduced: "<<time_reduced<<" secs\n";
    ofile<<"tLSH: "<<timeLSH<<" secs\n";
    ofile<<"tTrue: "<<timeTRUE<<" secs\n";
    ofile <<"Approximation Factor LSH: " <<sum_LSH<< "\n";
	ofile << "Approximation Factor Reduced: " <<sum_reduced<< "\n";
    ofile.close();
}



void Calculate_The_LSH_Neighbor(vector <int> pictures_of_bucket, int query, vector <int> query_vector, vector <vector <int> > input_vector, int* nearest_neighbor, int* best_distance) {
    int num_of_pics = pictures_of_bucket.size();
    for (int i = 0; i < num_of_pics; i++) {
		int distance = Manhattan_Distance(query_vector, input_vector[pictures_of_bucket[i]]);
		if(*best_distance==0){
			*best_distance=distance;
			*nearest_neighbor=pictures_of_bucket[i];
		}
		else{
			if(distance<*best_distance){
				*best_distance=distance;
				*nearest_neighbor=pictures_of_bucket[i];
			}
		}
    }
}



