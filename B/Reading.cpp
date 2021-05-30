#include "Reading.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

void Read_Arguements_of_Main(int argc,char **argv,string* input_file_original,string* input_file_new_space,string* query_file_original,string* query_file_new_space,string* output_file,int* k,int* L){
    for (int ar = 0; ar < argc - 1; ar++) {
        if (strcmp(argv[ar], "-d") == 0) {
            *input_file_original = argv[ar + 1];
        } else if (strcmp(argv[ar], "-i") == 0) {
            *input_file_new_space = argv[ar + 1];
        } else if (strcmp(argv[ar], "-q") == 0) {
        	*query_file_original = argv[ar + 1];
        } else if (strcmp(argv[ar], "-s") == 0) {
        	*query_file_new_space = argv[ar + 1];
        } else if (strcmp(argv[ar], "-o") == 0) {
            *output_file = argv[ar + 1];
        } else if (strcmp(argv[ar], "-k") == 0) {
            *k = atoi(argv[ar + 1]);
        } else if (strcmp(argv[ar], "-L") == 0) {
            *L = atoi(argv[ar + 1]);
        }
    }
}

void ReadMNIST(string input_file, vector<vector <int> >* all_images , int *rows, int *columns) {
    ifstream file(input_file, ios::binary);
    if (file.is_open()) {
		//cout<<"Mpike"<<endl;
        int magic_number = 0;
        int num_of_images = 0;
        file.read((char*) &magic_number, sizeof (magic_number));
        magic_number = ReverseInt(magic_number);
        //cout<<"The magic number is:"<<magic_number<<"\n";
        file.read((char*) &num_of_images, sizeof (num_of_images));
        num_of_images = ReverseInt(num_of_images);
        //cout<<"Number of images are:"<<num_of_images<<"\n";
        file.read((char*) rows, sizeof (int));
        *rows = ReverseInt(*rows);
        file.read((char*) columns, sizeof (int));
        *columns = ReverseInt(*columns);
        //cout<<"The Rows are "<<*rows<<" and the Columns are "<<*columns<<"\n";
        int flag = 0;
        while (1) {
            vector<int> image;
            for (int j = 0; j<*columns; j++) {
                for (int k = 0; k<*rows; k++) {
                    unsigned char pixel = 0;
                    file.read((char*) &pixel, sizeof (pixel));
                    if (file.eof()) {
                        flag = 1;
                        break;
                    }
                    image.push_back((int) pixel);
                }
                if (flag == 1) {
                    break;
                }
            }
            if (flag == 1) {
                break;
            }
            (*all_images).push_back(image);
        }
    } else {
        cout << "File " << input_file << " can't be opened\n";

    }
}

void ReadMNIST_LS(string input_file, vector<vector <int> >* all_images , int *rows, int *columns) {//synarthsh gia diavasma twn reduced arxeiwn
    ifstream file(input_file, ios::binary);
    if (file.is_open()) {
		//cout<<"Mpike"<<endl;
        int magic_number = 0;
        int num_of_images = 0;
        file.read((char*) &magic_number, sizeof (magic_number));
        magic_number = ReverseInt(magic_number);
        //cout<<"The magic number is:"<<magic_number<<"\n";
        file.read((char*) &num_of_images, sizeof (num_of_images));
        num_of_images = ReverseInt(num_of_images);
        //cout<<"Number of images are:"<<num_of_images<<"\n";
        file.read((char*) rows, sizeof (int));
        *rows = ReverseInt(*rows);
        file.read((char*) columns, sizeof (int));
        *columns = ReverseInt(*columns);
        //cout<<"The Rows are "<<*rows<<" and the Columns are "<<*columns<<"\n";
        int flag = 0;
        while (1) {
            vector<int> image;
                for (int j = 0; j<*columns; j++) {
                for (int k = 0; k<*rows; k++) {
                    unsigned char pixel1 = 0,pixel2=0;
                    unsigned short pixel;
                    file.read((char*) &pixel1, sizeof (pixel1)); // diavazoume to prwto pixel
                    file.read((char*) &pixel2, sizeof (pixel2)); // diavazoume to deutero pixel
                    
                    pixel = pixel2;
                    pixel = pixel << 8;//kanoume mia olisthisi
                    pixel += pixel1;//enwnoume ton arithmo
                    
                    if (file.eof()) {
                        flag = 1;
                        break;
                    }
                    
                    //cout <<"PIXEL="<< pixel << endl;
                    image.push_back((int) pixel);
                }
                if (flag == 1) {
                    break;
                }
            }
            if (flag == 1) {
                break;
            }
            (*all_images).push_back(image);
        }
    } else {
        cout << "File " << input_file << " can't be opened\n";

    }
}

void Read_Labels(string input_file,vector <int>* labels){ //arxeia gia diavasma twn arxikwn arxeiwn
	ifstream file(input_file, ios::binary);
    if (file.is_open()) {
        int magic_number = 0;
        int num_of_images = 0;
        file.read((char*) &magic_number, sizeof (magic_number));
        magic_number = ReverseInt(magic_number);
        //cout<<"The magic number is:"<<magic_number<<"\n";
        file.read((char*) &num_of_images, sizeof (num_of_images));
        num_of_images = ReverseInt(num_of_images);
        //cout<<"Number of images are:"<<num_of_images<<"\n";
        int flag = 0;
        while (1) {
            for (int j = 0; j<num_of_images; j++) {
                unsigned char label = 0;
                file.read((char*) &label, sizeof (label));
                if (file.eof()) {
                    flag = 1;
                    break;
                }
                (*labels).push_back((int) label);
            }
            if (flag == 1) {
                break;
            }
        }
    } else {
        cout << "File " << input_file << " can't be opened\n";
    }
}

int ReverseInt(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8)&255;
    ch3 = (i >> 16)&255;
    ch4 = (i >> 24)&255;
    return ((int) ch1 << 24)+((int) ch2 << 16)+((int) ch3 << 8) + ch4;
}

