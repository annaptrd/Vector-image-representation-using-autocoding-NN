def readingArguments(argv):
	n=len(argv)
	for i in range(1,n):#diavasma twn parametrwn apo th grammh
		if(argv[i]=="-d"):
			training_set_file=argv[i+1]
		elif(argv[i]=="-od"):
			training_set_output_file=argv[i+1]
		elif(argv[i]=="-q"):
			test_set_file=argv[i+1]
		elif(argv[i]=="-oq"):
			test_set_output_file=argv[i+1]

	return training_set_file , training_set_output_file , test_set_file , test_set_output_file
	
