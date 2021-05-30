#include <vector>
#include <string>

#ifndef READING_H
#define READING_H

using namespace std;

void Read_Arguements_of_Main(int argc,char **argv,string* input_file_original,string* input_file_new_space,string* query_file_original,string* query_file_new_space,string* output_file,int* k,int* L);

void ReadMNIST(string input_file, vector<vector <int> >* all_images , int *rows, int *columns);

void ReadMNIST_LS(string input_file, vector<vector <int> >* all_images , int *rows, int *columns);

void Read_Labels(string input_file,vector <int>* labels);

int ReverseInt(int i);

#endif
