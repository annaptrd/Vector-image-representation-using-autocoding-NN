from keras.models import load_model, Model
import tensorflow as tf
import sys

model_file= "my_h5_model_for_reducer.h5"

fc_nodes=3

def build_model(model_file):
    model = load_model(model_file)
    reducer = tf.keras.Sequential()
    flag = 0
    flag2 = 0
    D = 0

    for layer in model.layers:  # diavazetai to modelo kai krateitai mono to encoder kommati
        if (layer.get_output_at(0).get_shape().as_list()[1] == 6272):
            flag = 1
        if (flag == 1 and layer.get_output_at(0).get_shape().as_list()[1] != 6272):
            flag2 = 1
            flag = 0
        elif (flag2 == 1):
            break

        reducer.add(layer)

    D = reducer.layers[-1].get_output_at(0).get_shape().as_list()[1]

    reducer.summary()

    return reducer, D