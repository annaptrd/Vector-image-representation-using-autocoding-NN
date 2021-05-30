import sys
import math

from scipy.optimize import linprog

def EMD_Distance(query_image,input_image,numofclusters):
	rows=len(query_image)
	columns=len(query_image)
	
	pixels_of_cluster=int((rows*columns)/numofclusters) #aritmos twn pixels kathe cluster
	cluster_rows=int(math.sqrt(pixels_of_cluster)) #arithmos twn grammwn kathe cluster
	cluster_columns=int(math.sqrt(pixels_of_cluster)) #arithmos twn sthlwn kathe cluster
	numofclusters_in_a_row_and_column=int(rows/cluster_rows) #posa cluster symperilambanei mia grammh h mia sthlh
	#print("Pixels of each cluster=",pixels_of_cluster)
	#print("Rows in a cluster=",cluster_rows)
	#print("Columns in a cluster=",cluster_columns)
	#print("Clusters in a row or column=",numofclusters_in_a_row_and_column)
	
	query_weights=[]
	input_weights=[]
	centroid_row_coordinates_query=[]
	centroid_column_coordinates_query=[]
	centroid_row_coordinates_input=[]
	centroid_column_coordinate_input=[]
	for cluster in range(0,numofclusters): #gia kathe cluster
		query_weight=0
		input_weight=0
		#print("CLUSTER=",cluster)
		rowposition=int( cluster/numofclusters_in_a_row_and_column ) #ypologizoyme se poia parallhlh grammh briskomaste
		rowposition*=cluster_rows #h grammh poy ksekinaei to cluster ayto
		#print("rowposition=",rowposition)
		columnposition=cluster #arxikopoieitai h katakoryfh poy brisketai to cluster
		while(columnposition> (math.sqrt(numofclusters)-1) ):#an exoume perasei ta sqrt(numofclusters) tote kanoyme mia epanalaipsi wste na pame sth katallhlh katakoryfo
			columnposition-=numofclusters_in_a_row_and_column
		columnposition=columnposition*cluster_columns #h sthlh poy ksekinaei to cluster ayto
		#print("columnposition=",columnposition)
		for i in range(0,cluster_rows): #gia oles tis grammes poy perilambanei to cluster
			for j in range(0,cluster_columns): #gia oles tis sthles poy perilambanei to cluster
				query_weight+=float(query_image[i+rowposition][j+columnposition]) #ypologizoume to synoliko weight toy query
				input_weight+=float(input_image[i+rowposition][j+columnposition]) #ypologizoume to synoliko weight tou input
		
		#print("query_weight=",query_weight)
		query_weights.append(query_weight)#apothikeyoume to synoliko baros toy query sto vector
		#print("input_weight=",input_weight)
		input_weights.append(input_weight)#apothikeyoume to synoliko baros toy query sto vector
		
		centroid_row_coordinates_query.append(rowposition + int((cluster_rows/2)) ) #ypologizoyme th grammh toy kentroy toy cluster tou query
		centroid_column_coordinates_query.append(columnposition + int((cluster_columns/2)) ) #ypologizoyme th sthlh toy kentroy toy cluster tou query
		centroid_row_coordinates_input.append(rowposition + int((cluster_rows/2)) )
		centroid_column_coordinate_input.append(columnposition + int((cluster_columns/2)) )
		
	#print("centroid_row_coordinates_query=",centroid_row_coordinates_query)
	#print("centroid_column_coordinates_query=",centroid_column_coordinates_query)
	#print("centroid_row_coordinates_input=",centroid_row_coordinates_input)
	#print("centroid_column_coordinate_input=",centroid_column_coordinate_input)
	
	distances=[]
	objective_array=[]
	for input_cluster in range(0,numofclusters):
		input_cluster_distances=[]
		for query_cluster in range(0,numofclusters):
			if( (centroid_row_coordinates_input[input_cluster] - centroid_row_coordinates_query[query_cluster]) < 0): #ypologizoume th diafora twn grammwn metaksy query-input
				x=centroid_row_coordinates_query[query_cluster] - centroid_row_coordinates_input[input_cluster]
			else:
				x=centroid_row_coordinates_input[input_cluster] - centroid_row_coordinates_query[query_cluster]
			x*=x
			if( (centroid_column_coordinate_input[input_cluster] - centroid_column_coordinates_query[query_cluster]) < 0 ): #ypologizoume th diafora twn sthlwn metaksy query-input
				y=centroid_column_coordinates_query[query_cluster] - centroid_column_coordinate_input[input_cluster]
			else:
				y=centroid_column_coordinate_input[input_cluster] - centroid_column_coordinates_query[query_cluster]
			y*=y
			input_cluster_distances.append( math.sqrt(x+y) )
			objective_array.append(math.sqrt(x+y)) #h eyklideia apostash mpainei sthn antikeimeniki synarthsh
			#print("Input=",input_cluster," Query=",query_cluster," distance=",math.sqrt(x+y))
			
		distances.append(input_cluster_distances) #apothikeyetai h apostash
			
	
	#find the ΣΣdf
	left_eq=[]
	
	for input_cluster in range(0,numofclusters):#gemizoume toys pinakes gia ta flows
		constraint_for_this_input_cluster=[] #ena array gia to aristero meros ths eksiswshs aytou tou input cluster
		for before_clusters in range(0,numofclusters*input_cluster): #gemizoyn me mhdenika oi akmes twn input clusters prin apo ayto
			constraint_for_this_input_cluster.append(0)
			
		for these_clusters in range(0,numofclusters): #gemizei me assous to input cluster gia tis akmes poy dinoun maza sta query clusters
			constraint_for_this_input_cluster.append(1)
		
		for after_clusters in range(0,numofclusters*(numofclusters-input_cluster-1)): #oles oi ypoloipes akmes gemizoyn me 0
			constraint_for_this_input_cluster.append(0)
		
		left_eq.append(constraint_for_this_input_cluster) #prostithetai to array sto synoliko
		
		
	
	for query_cluster in range(0,numofclusters):
		constraint_for_this_query_cluster=[]
		for time in range(0,numofclusters): #ginontai toses epanalipseis wste na gemizei swsta to array
			for before_clusters in range(0,query_cluster): #gemizoun me mhdenika ta queries ektos toy sygkekrimenou poy gemizoume
				constraint_for_this_query_cluster.append(0)
			
			constraint_for_this_query_cluster.append(1) #gemizei me asso h akmh toy sygkekrimenou query cluster
			
			for after_clusters in range(0,numofclusters-query_cluster-1): #gemizoun me 0 oi akmes pros ta ypoloipa query clusters
				constraint_for_this_query_cluster.append(0)
				
		left_eq.append(constraint_for_this_query_cluster) #prostithetai to array sto synoliko
	
	
	
	#print("Objective_array=",objective_array)
	#print("left_eq=",left_eq)
	
	
	right_eq=[]
	
	for input_cluster in range(0,numofclusters): #prostithentai ta barh me th seira
		right_eq.append(input_weights[input_cluster])
	
	for query_cluster in range(0,numofclusters): #prostithentai ta barh me th seira
		right_eq.append(query_weights[query_cluster])
	
	#print("Query_WEIGHTS=",query_weights)
	#print("INPUT_WEIGHTS=",input_weights)
	#print("Right_eq=",right_eq)
	
	singlebound=(0,math.inf)
	
	bnd=[]
	for cluster in range(0,numofclusters):
		for cluster in range(0,numofclusters):
			bnd.append( singlebound )
	
	#print(bnd)
	
	
	opt = linprog(c=objective_array ,A_eq=left_eq, b_eq=right_eq, bounds=bnd, method="revised simplex")		
			
	return opt.fun
			
	
	
	
