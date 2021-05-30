import sys

def Manhattan_Distance(query_image,input_image):
	rows = len(query_image)
	columns=len(query_image[0])
	#print("Columns=",columns)
	#print("Rows=",rows)
	#print(query_image)
	distance = 0.0
	for i in range(0,rows): #ypologizoume th diafora toy query kai input
		for j in range(0,columns):
			if(query_image[i][j]-input_image[i][j]<0): 
				distance+=float(input_image[i][j]-query_image[i][j])
			else:
				distance+=float(query_image[i][j]-input_image[i][j])
	return distance;
    
