#include "Reading.h"
#include "Reduced_Space.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"
#include "../Functions_for_both_algorithms/Modulos.h"
#include "LSH.h"

#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cmath>

#define MULTIPLIER 2
#define BUCKET_PARAMETER 8

using namespace std;

int main(int argc,char **argv){
	string input_file_original;
	string input_file_new_space;
	string query_file_original;   
    string query_file_new_space;
	string output_file;
	
	vector<vector <int> > input_vector_original;
	vector<vector <int> > input_vector_new_space;
	vector<vector <int> > query_vector_original;
	vector<vector <int> > query_vector_new_space;
	
	int rows=0;
	int columns=0;
    int k=4;
	int L=5;
	int M=pow(2,(int) (32/k));
	long int m=M/4-5;
	
	Read_Arguements_of_Main(argc,argv,&input_file_original,&input_file_new_space,&query_file_original,&query_file_new_space,&output_file,&k,&L);
	//cout<<"\n\nInputFile_original="<<input_file_original<<" Input_file_new_space= "<<input_file_new_space<<" Query_file_original="<<query_file_original<<" Query_file_new_space="<<query_file_new_space<<"  Output_file="<<output_file<<" k="<<k<<" L="<<L<<"\n";
	
	ReadMNIST(input_file_original,&input_vector_original,&rows,&columns);//Diavasma arxeio input ston arxiko xwro
	int size=rows*columns;
	ReadMNIST_LS(input_file_new_space, &input_vector_new_space,&rows,&columns);//diavasma arxeiou input ston reduced xwro
	
	
	int Num_of_Buckets=( input_vector_original.size() )/BUCKET_PARAMETER;
	int W=MULTIPLIER*Compute_W(input_vector_original,size);
	srand((unsigned)time(0));
	
	vector <int> modulo_Exponents_of_m;
	Calculate_the_Modulo_Exponents(&modulo_Exponents_of_m,m,M,size);//modulo_Exponents einai enas vector pou apothikeyoume tis m^x mod M times wste na mh tis ksanaypologizoyme
	
	vector <Hash> g_hash;
	vector <vector <vector <int> > > all_h_values_of_all_g;
	Hash_The_Train_File(&all_h_values_of_all_g,&g_hash,input_vector_original,Num_of_Buckets,L,k,M,modulo_Exponents_of_m,W);
	
	//QUERIES
	ReadMNIST_LS(query_file_new_space,&query_vector_new_space,&rows,&columns);//diavasma toy arxeiou query ston reduced xwro
	clock_t start = clock();
	vector <int> reduced_neighbors;
	vector <int> reduced_distances;
	find_true_neighbors_of_new_space(input_vector_new_space,query_vector_new_space,&reduced_neighbors,&reduced_distances);//briskoume ton pragmatika kontinotero eksantlitika
	//double average=Calculate_Average(reduced_neighbors,"/home/mike/Desktop/project3/train-labels.idx1-ubyte","/home/mike/Desktop/project3/t10k-labels.idx1-ubyte");
	//cout<<"AVERAGE="<<average<<endl;
	clock_t end = clock();
	double time_reduced = double(end - start)/CLOCKS_PER_SEC;//xronos reduced
	cout<<"REDUCED_TIME="<<time_reduced<<endl;
	ReadMNIST(query_file_original,&query_vector_original,&rows,&columns);
	for(int i=0;i<(int) query_vector_original.size();i++){
		reduced_distances[i]=Manhattan_Distance(query_vector_original[i],input_vector_original[reduced_neighbors[i]]);//ypologizoyme thn reduced apostash ston arxiko xwro me thn eikona poy brikame ston reduced xwro
	}
		Hash_The_Queries_And_Calculate_Neighbors(input_vector_original,query_vector_original,all_h_values_of_all_g,g_hash,k,L,M,modulo_Exponents_of_m,W,output_file,reduced_neighbors,reduced_distances,time_reduced);

}






