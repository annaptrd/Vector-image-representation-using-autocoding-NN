import sys
from tensorflow import keras
from mlxtend.data import loadlocal_mnist
import struct as st
import numpy as np


def readingArguements(argv):
	n=len(argv)
	for i in range(1,n):#diavasma twn parametrwn apo th grammh
		if(argv[i]=="-d"):
			input_file=argv[i+1]
		elif(argv[i]=="-l1"):
			input_labels_file=argv[i+1]
		elif(argv[i]=="-q"):
			query_file=argv[i+1]
		elif(argv[i]=="-l2"):
			query_labels_file=argv[i+1]
		elif(argv[i]=="-o"):
			output_file=argv[i+1]
			
	return input_file , input_labels_file , query_file , query_labels_file , output_file
	

def file_normalization(input_file , input_labels_file , query_file , query_labels_file):

	input_set, input_labels = loadlocal_mnist(images_path=input_file,labels_path=input_labels_file)#ta bytes twn arxeiwn apothikeyontai stoys pinakes training_set kai training_labels
	query_set, query_labels = loadlocal_mnist(images_path=query_file,labels_path=query_labels_file)#ta bytes twn arxeiwn apothikeyontai stoys pinakes test_set kai test_labels

	input_set = input_set/255#kanonikopoihsh twn pixels sto (0,1)
	query_set = query_set/255#kanonikopoihsh twn pixels sto (0,1)

	input_set = input_set.reshape(input_set.shape[0],28,28,1)#metattroph toy arxeioy eikonwn wste na einai ths morfhs pinaka 28*28*1
	query_set = query_set.reshape(query_set.shape[0],28,28,1)#metattroph toy arxeioy eikonwn wste na einai ths morfhs pinaka 28*28*1

	input_labels=keras.utils.to_categorical(input_labels, 10) #one-hot encode our data.
	query_labels=keras.utils.to_categorical(query_labels, 10) #one-hot encode our data.
	
	
	for image in range(0,len(input_set)): #normalize ta pixels wste na exoyn idio synoliko athroisma oles oi eikones 
		weight_image=0
		for i in range(0,len(input_set[image])):
			for j in range(0,len(input_set[image][i])):
				weight_image+=input_set[image][i][j] #briskoume to synoliko athroisma ths eikonas
		input_set[image]/=weight_image #diairoume me to synoliko athroisma ola ta pixels
		
		weight_image=0
		for i in range(0,len(input_set[image])):
			for j in range(0,len(input_set[image][i])):
				weight_image+=input_set[image][i][j]
				
		#print("IMAGE+",image," And WEIGHT=",weight_image)
	

	for query in range(0,len(query_set)): 
		weight_query=0
		for i in range(0,len(query_set[query])):
			for j in range(0,len(query_set[query][i])):
				weight_query+=query_set[query][i][j]
		query_set[query]/=weight_query
		
		weight_query=0
		for i in range(0,len(query_set[query])):
			for j in range(0,len(query_set[query][i])):
				weight_query+=query_set[query][i][j]
		#print("Query=",query," AND weight=",weight_query)
		
	
	return input_set , input_labels , query_set , 	query_labels
	

