
#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <time.h>


#include "Clustering.h"
#include "ClassicClustering.h"
#include "LshClustering.h"
#include "HypercubeClustering.h"
#include "../Functions_for_both_algorithms/Reading.h"
#include "ClusteringReading.h"
#include "ImageCollection.h"
#include "../Functions_for_both_algorithms/Calculate_Distances.h"

using namespace std;

int partition (vector<int> &arr, int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
     
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            int num=arr[i];
            arr[i]=arr[j];
            arr[j]=num;
          
        } 
    }
    int num=arr[i + 1];
    arr[i + 1]=arr[high];
    arr[high]=num;
    return (i + 1); 
} 
  

void quickSort(vector<int> &arr, int low, int high) 
{ 
    if (low < high) 
    { 
       
        int pi = partition(arr, low, high); 
  
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void Read_Class_File(string classes_file,vector <vector < int > >* clusters){
	ifstream MyReadFile(classes_file);
	char output[100000];
	int metritis=0;
	while (!MyReadFile.eof()) {
		MyReadFile >> output;
		int index=0;
		while(output[index]!=','){
			index++;
		}
		vector <int> cluster;
		while(output[index]!='}'){
			index++;
			vector <int> number;
			while(output[index]!=',' and output[index]!='}'){
				number.push_back( (output[index]-'0') );
				index++;
			}
			int image=0;
			for(int i=0;i<(int)number.size();i++){
				int dec=1;
				for (int j=1;j<((int) number.size()-i);j++){
					dec*=10;
				}
				image+=dec*number[i];
			}
			//cout<<"Image="<<image<<endl;
			cluster.push_back(image);
		}
		(*clusters).push_back(cluster);
		metritis++;
	}
}

double find_objective_function(ImageCollection collection_OS,vector <vector < int > > clusters){
	vector <vector <int> > centroid_clusters;
	for(int cluster=0;cluster<(int) clusters.size(); cluster++){
		vector <int> median_vector;
		for(int dimension=0; dimension<(int) collection_OS[0].size(); dimension++){
			vector <int> pixels;
			for(int image=0;image<(int) clusters[cluster].size();image++){
				pixels.push_back( collection_OS[ clusters[cluster][image] ][dimension] );
				//cout<<"dimension="<<collection_OS[ clusters[cluster][image] ][dimension]<<endl;
			}
			quickSort(pixels,0,pixels.size()-1);
			//cout<<"PIXEL="<<pixels[392]<<endl;
			int index=(int) collection_OS[0].size()/2;
			median_vector.push_back(pixels[index]);
		}
		centroid_clusters.push_back(median_vector);
	}
	
	double objective_fun=0.0;
	vector <double> distances;
	double max_distance=0.0;
	for(int cluster=0; cluster<(int) clusters.size() ; cluster++){
		for(int image=0;image<(int) clusters[cluster].size();image++){
			int min_distance=100000;
			for(int centroid=0;centroid<(int) centroid_clusters.size();centroid++){
				double distance=Manhattan_Distance(collection_OS[ clusters[cluster][image] ],centroid_clusters[centroid]);
				if(distance<min_distance){
					min_distance=distance;
				}
			}
			if(min_distance>max_distance){
				max_distance=min_distance;
			}
			//cout<<"MINDISTANCE="<<min_distance<<endl;
			distances.push_back(min_distance);
		}
	}
	//cout<<"MAXDISTANCE="<<max_distance<<endl;
	for(int i=0;i<(int) distances.size();i++){
		distances[i]=distances[i]/(double)max_distance;
	}
	//cout<<"SIZE="<<distances.size();
	for(int i=0;i<(int) distances.size();i++){
		objective_fun+=distances[i];
	}
	cout<<"OBJECTIVEFUN="<<objective_fun<<endl;
	return objective_fun;

}

// ./cluster –d <input file original space> -i <input file new space>  -n <classes from NN as clusters file> –c <configuration file> -o <output file>
//"${OUTPUT_PATH}" -i train-images.idx3-ubyte -d train-images.idx3-uhalfword -c config.txt  -o output.txt -complete -m Classic

int main(int argc, char * argv[]) {
    string input_file_original_space = "", output = "", config = "", method = "Classic", input_file_latentspace = "",classes_file="";
    bool complete = true;
    bool error = false;

    // classic:
    int K;

    // LSH:
    int L = 3, k_lsh = 4;

    // Hypercube
    int M_cube = 10, k_cube = 3, probes = 2;

    // LSH+Hypercube
    int W = 1000;

    for (int i = 0; i < argc; i++) {
        if (string(argv[i]) == "-i") {
            input_file_latentspace = argv[i + 1];
        }
        if (string(argv[i]) == "-c") {
            config = argv[i + 1];
        }
        if (string(argv[i]) == "-o") {
            output = argv[i + 1];
        }

        if (string(argv[i]) == "-d") {
            input_file_original_space = argv[i + 1];
        }
        if (string(argv[i]) == "-n") {
        	classes_file=argv[i + 1];
        }
    }

    if (input_file_latentspace == "") {
        printf("input is missing \n");
        error = true;
    }

    if (output == "") {
        printf("output is missing \n");
        error = true;
    }

    if (config == "") {
        printf("config is missing \n");
        error = true;
    }

    if (method == "") {
        printf("method is missing \n");
        error = true;
    }
    
    if(classes_file==""){
    	printf("Class file is missing \n");
    }

    if (error) {
        printf("lathos parametroi \n");
        printf("prepei na einai: -i  <input  file>  -c  <configuration  file>  -o  <output  file>  ");
        return 0;
    }
	
	//vector <vector < int > > clusters;
	//Read_Class_File(classes_file,&clusters);
	
	
	
    ifstream configfile(config); //anoigei to arxeio 
    if (configfile.is_open() && configfile.good()) {
        string line = "";
        while (getline(configfile, line)) {
            stringstream command(line);
            string data[2] = {"", ""};
            command >> data[0] >> data[1];

            if (data[0] == "number_of_clusters:") {
                K = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_vector_hash_tables:") {
                L = atoi(data[1].c_str());
            }
            if (data[0] == "number_of_vector_hash_functions:") {
                k_lsh = atoi(data[1].c_str());
            }
            //            if (data[0] == "max_number_M_hypercube:") {
            //                M_cube = atoi(data[1].c_str());
            //            }
            //            if (data[0] == "number_of_hypercube_dimensions:") {
            //                k_cube = atoi(data[1].c_str());
            //            }
            //            if (data[0] == "number_of_probes:") {
            //                probes = atoi(data[1].c_str());
            //            }

        }

        cout << "number_of_clusters              : " << K << endl;
        cout << "number_of_vector_hash_tables    : " << L << endl;
        cout << "number_of_vector_hash_functions : " << k_lsh << endl;
        //        cout << "max_number_M_hypercube          : " << M_cube << endl;
        //        cout << "number_of_hypercube_dimensions  : " << k_cube << endl;
        //        cout << "number_of_probes                : " << probes << endl;
        //        
        ImageCollection collection_OS;

        ImageCollection collection_LS;


        int numberOfImages = ReadMNIST_NumberOfImages(input_file_original_space.c_str(), &collection_OS);

        cout << "Number of images in input file is: " << numberOfImages << endl;

        ReadMNIST(input_file_original_space.c_str(), &collection_OS, &collection_OS.rows, &collection_OS.columns);

        ReadMNIST_LS(input_file_latentspace.c_str(), &collection_LS, &collection_LS.rows, &collection_LS.columns);
        

        cout << "New Space:" << endl;
        cout << "The rows are " << collection_LS.rows << " and the columns are " << collection_LS.columns << "\n";

        int dimensions_LS = collection_LS.rows * collection_LS.columns;

        cout << "  Collection Size=" << collection_LS.size() << endl;
        cout << "  Collection dimensions=" << dimensions_LS << endl;


        cout << "Original Space:" << endl;
        cout << "The rows are " << collection_OS.rows << " and the columns are " << collection_OS.columns << "\n";

        int dimensions_OS = collection_OS.rows * collection_OS.columns;

        cout << "  Collection Size=" << collection_OS.size() << endl;
        cout << "  Collection dimensions=" << dimensions_OS << endl;
		
		
		
		
        Clustering * clustering_OS;
        Clustering * clustering_LS;

        // trim because of speed
//        int SPEED_LIMIT = 5000;
//
//        collection_OS.resize(SPEED_LIMIT);
//
//        collection_LS.resize(SPEED_LIMIT);

        if (method == "Classic") { //analogws ti methodo kalei tin antisoixi clustering
            clustering_OS = new ClassicClustering(&collection_OS, K);
            clustering_LS = new ClassicClustering(&collection_LS, K);
        } else if (method == "LSH") {
            clustering_OS = new LshClustering(&collection_OS, K, L, k_lsh, W);
        } else if (method == "Hypercube") {
            clustering_OS = new HypercubeClustering(&collection_OS, K, k_cube, W, M_cube, probes, dimensions_OS);
        } else {
            cout << "Unsupported method: " << method << "  \n";
            return -1;
        }

        int limit = (int) log(W); //to limit gia na stamataei - xrisimo sto debugging mou

        string s = string(output);
        ofstream fp(s.c_str());

        cout << "***************************************************\n";
        cout << "             Clustering for latent space \n";
        cout << "***************************************************\n";

        clock_t tStart_LS = clock(); //metraw to xrono poy pairnei to clustering kai ton ektypwnw sto arxeio

        AssignmentDefinition * result_LS = clustering_LS->execute(limit);

        double clustertime_ls = (clock() - tStart_LS) / CLOCKS_PER_SEC; //metraw to xrono poy pairnei to clustering kai ton ektypwnw sto arxeio

        cout << "Calculating new centers " << endl;
        result_LS->centers = clustering_OS->update(K, result_LS);

        cout << "***************************************************\n";
        cout << "                   Results \n";
        cout << "***************************************************\n";
        clustering_LS->printResults(result_LS);

        //write output file

        if (method == "Classic")
            fp << endl; // "Algorithm: Lloyds"  << endl;
        else if (method == "LSH")
            fp << "Algorithm: Range Search LSH" << endl;
        else if (method == "Hypercube")
            fp << "Algorithm:  Range Search Hypercube" << endl;
        else
            fp << "Algorithm: Unsupported method" << endl;

        fp << "NEW SPACE" << endl;

        for (int i = 0; i < K; i++) {
            fp << "CLUSTER-" << i << " " << "{size: " << result_LS->cluster_to_points[i].size() << ", centroid: ";
            cout << "CLUSTER-" << i << " " << "{size: " << result_LS->cluster_to_points[i].size() << ", centroid: ";

            vector<int> & temp = (*(result_LS->centers))[i]; //pairnw tis syntetagmenes gia to kentro i
            unsigned int s = temp.size();
            for (unsigned l = 0; l < s - 1; l++) {
                fp << temp[l] << ",";
                cout << temp[l] << ",";
            }
            fp << temp[s - 1]; //to ksexwrisa apla gia na min vazei , sto teleytaio stoixeio
            cout << temp[s - 1]; //to ksexwrisa apla gia na min vazei , sto teleytaio stoixeio

            fp << "}" << endl;
            cout << "}" << endl;
        }

        fp << "clustering_time: " << clustertime_ls << " sec" << endl;

        vector<float> sil_ls = clustering_OS->silhouette(result_LS);
        fp << "Silhouette: [" << sil_ls[0];
        cout << "Silhouette: [" << sil_ls[0];

        for (unsigned int i = 1; i < sil_ls.size(); i++) {
            fp << "," << sil_ls[i];
            cout << "," << sil_ls[i];
        }
        cout << "]" << endl;
        fp << "]" << endl;
        fp << endl;


        
        cout << "***************************************************\n";
        cout << "             Clustering for original space \n";
        cout << "***************************************************\n";

        clock_t tStart = clock();
        AssignmentDefinition * result_OS = clustering_OS->execute(limit);
        double clustertime_os = (clock() - tStart) / CLOCKS_PER_SEC;

        fp << "ORIGINAL SPACE" << endl;
        for (int i = 0; i < K; i++) {
            fp << "CLUSTER-" << i << " " << "{size: " << result_OS->cluster_to_points[i].size() << ", centroid: ";

            vector<int> & temp = (*(result_OS->centers))[i]; //pairnw tis syntetagmenes gia to kentro i
            unsigned int s = temp.size();
            for (unsigned l = 0; l < s - 1; l++) {
                fp << temp[l] << ",";
            }
            fp << temp[s - 1]; //to ksexwrisa apla gia na min vazei , sto teleytaio stoixeio

            fp << "}" << endl;
        }
        fp << "clustering_time: " << clustertime_os << " sec" << endl;

        vector<float> sil_os = clustering_OS->silhouette(result_OS);
        fp << "Silhouette: [" << sil_os[0];
        cout << "Silhouette: [" << sil_os[0];

        for (unsigned int i = 1; i < sil_os.size(); i++) {
            fp << "," << sil_os[i];
            cout << "," << sil_os[i];
        }
        cout << "]" << endl;
        fp << "]" << endl;
        fp << endl;
        
        
        fp<<"CLASSES AS CLUSTERS"<<endl;
        
        
        set<int> points;
        int temporary, tem;
        complete=false;
        if (complete == true) {//an dothei complete ektypwnw kathe cluster me to centroid k me ta simeia tou
            fp << endl;
            fp << endl;
            for (int i = 0; i < K; i++) {
                fp << "CLUSTER-" << i << " {";
                temporary = result_OS->cluster_to_points[i].size();
                points = result_OS->cluster_to_points[i];
                tem = 0;
                for (auto it = points.begin(); it != points.end(); ++it) {
                    fp << *it;
                    if (tem < temporary - 1) { //ayto to kanw mono gia na min mpainei , sto teleytaio
                        fp << ",";
                    }
                    tem++;

                }
                fp << "}" << endl;
            }
        }

        if (result_OS != nullptr) {
            delete result_OS;
        }

        //        if (result_LS != nullptr) {
        //            delete result_LS;
        //        }

        delete clustering_OS;

        //        delete clustering_LS;
    } else {
        cout << "Failed to open file.." << config;
    }

    return 0;
}





