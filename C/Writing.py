import sys

def Writing_Output(output_file,Average_EMD,Average_Manhattan):
	C_file = open(output_file,'w')
	C_file.write("%s %s \n" % ("Average Correct Search Results EMD:", str(Average_EMD)))
	C_file.write("%s %s \n" % ("Average Correct Search Results Manhattan:", str(Average_Manhattan)))
	C_file.close()
