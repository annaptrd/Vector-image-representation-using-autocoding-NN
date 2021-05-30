import sys
import numpy as np
from tensorflow.keras import layers, losses, optimizers, metrics
from tensorflow.keras.optimizers import RMSprop
import matplotlib.pyplot as plt
import warnings
#from classification_results import printGraphs, print_classification_reports, display_graph_option, image_classification
from InputOutputMNIST import readMNIST, writeMNIST
from reading_and_converting import readingArguments
from autoencoding import build_model

model_file = "my_h5_model_for_reducer.h5"
learningRate = 0.001

warnings.filterwarnings('ignore')

np.set_printoptions(threshold=sys.maxsize)

training_set_file , training_set_output_file , test_set_file , test_set_output_file = readingArguments(sys.argv)  # reading the arguements

training_set = readMNIST(training_set_file)

test_set = readMNIST(test_set_file)

reducer, D = build_model(model_file)  # construction of the  new model

reducer.compile(loss=losses.MeanSquaredError(), optimizer=RMSprop(learning_rate=learningRate))

new_training_set =  reducer.predict(training_set)

new_test_set =  reducer.predict(test_set)

print("D = " , D)

print("Training set dimensions: ", end='')
print(training_set.shape)

print("Test set dimensions: ", end='')
print(test_set.shape)

print("New training set dimensions: ", end='')
print(new_training_set.shape)

print("New test set dimensions: ", end='')
print(new_test_set.shape)



writeMNIST(new_training_set, training_set_output_file, D)

writeMNIST(new_test_set, test_set_output_file, D)
