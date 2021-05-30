import sys
import warnings
import math
import time

from reading_and_converting import readingArguements , file_normalization
from Average import Calculate_Average
from Writing import Writing_Output

warnings.filterwarnings('ignore')

input_file , input_labels_file , query_file , query_labels_file , output_file  = readingArguements(sys.argv) 	#reading the arguements

input_set , input_labels , query_set , query_labels=  file_normalization(input_file , input_labels_file , query_file , query_labels_file)		#normalize the files

#numofclusters=int(input("Enter the number of clusters: "))
numofclusters=16
start = time.time()
Average_EMD=Calculate_Average(query_set,input_set,query_labels,input_labels,"EMD",numofclusters)
end = time.time()
print("The time for EMD is:",end - start," secs")

start = time.time()
Average_Manhattan=Calculate_Average(query_set,input_set,query_labels,input_labels,"Manhattan",numofclusters)
end = time.time()
print("The time for Manhattan is:",end - start," secs")

Writing_Output(output_file,Average_EMD,Average_Manhattan)
