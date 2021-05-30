import sys
from EMD import EMD_Distance
from Manhattan import Manhattan_Distance
from Quicksort import quickSort

def Calculate_Average(query_set,input_set,query_labels,input_labels,metric,numofclusters):
	average_correct=0.0
	for query in range(0,len(query_set)):  #gia kathe query
		best_distances=[]
		best_neighbors=[]
		for input_image in range(0,len(input_set)):  #gia kathe input
			if(metric=="Manhattan"): #an h metrikh poy psaxnoume einai h manhattan
				distance=Manhattan_Distance(query_set[query],input_set[input_image]) #ypologizoume th manhattan apostash aytou toy query me ayto to input
			elif(metric=="EMD"): #an h metrikh poy psaxnoume einai h EMD
				distance=EMD_Distance(query_set[query],input_set[input_image],numofclusters) #ypologizoume thn EMD apostash aytou toy query me ayto to input
			#print("Image=",input_image," and distance=",manhattan_distance)
			best_distances.append(distance) 
			best_neighbors.append(input_image)
		
		quickSort(best_distances,best_neighbors,0,len(best_distances)-1) #ginetai taksinomisi toy pinaka twn apostasewn kai toy pinaka twn neighbors wste na paroume toys 10 prwtoys
		print("The Labels of Query ",query," are ",query_labels[query]," and the neighbor's are:")
		correct_images=0
		for neighbor in range(0,10): #gia tous 10 prwtous geitones
			flag=0
			for i in range(0,len(query_labels[query])): #elegxoume an to label tou input einai idio me tou query
				if(query_labels[query][i]!=input_labels[best_neighbors[neighbor]][i]):
					flag=1
			
			if(flag==0): #an einai idio tote ayksanetai o metrhths
				correct_images+=1
			
			print("Neighbor ",best_neighbors[neighbor]," with distance ",best_distances[neighbor],"    And labels=",input_labels[best_neighbors[neighbor]]," Correct=",correct_images)
		
		average_correct+=correct_images/10.0 #prostithetai to average aytou tou query
		print("Average so far=",average_correct)
		
	average_correct/=float (len(query_labels)) #to synoliko average
	return average_correct
