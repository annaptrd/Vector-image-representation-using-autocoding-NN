from tensorflow.keras.layers import Conv2D, BatchNormalization, MaxPooling2D, UpSampling2D
from keras.layers import Dropout, Flatten, Dense, Reshape


def encoder(input_img, filterSize, numberOfLayers, numberOfFilters, add_dropout, project_to_latent_dimension, latent_dimension):
    conv = input_img
    # xwrizw ta layers dia 3 kai dinw ena trito edw
    if numberOfLayers >= 3:
        for i in range(numberOfLayers//3):
            conv = Conv2D(numberOfFilters, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)
            if add_dropout:
                conv = Dropout(0.2)(conv)  # meta apo peiramata eidame oti to 0.2 einai to idaniko
        conv = MaxPooling2D(pool_size=(2, 2))(conv)

        # ena trito edw
        for i in range(numberOfLayers // 3):
            conv = Conv2D(numberOfFilters*2, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)
            if add_dropout:
                conv = Dropout(0.2)(conv)
        conv = MaxPooling2D(pool_size=(2, 2))(conv)

        # kai o,ti perissepsei edw
        for i in range(numberOfLayers // 3 + numberOfLayers % 3):
            conv = Conv2D(numberOfFilters*4, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)
            if add_dropout:
                conv = Dropout(0.2)(conv)
    else:  # gia tin periptwsi pou exoume <3 layers
        conv = Conv2D(numberOfFilters, filterSize, activation='relu', padding='same')(conv)
        conv = BatchNormalization()(conv)
        if add_dropout:
            conv = Dropout(0.2)(conv)
        conv = MaxPooling2D(pool_size=(2, 2))(conv)
        if numberOfLayers > 1:
            conv = Conv2D(numberOfFilters * 2, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)
            if add_dropout:
                conv = Dropout(0.2)(conv)
            conv = MaxPooling2D(pool_size=(2, 2))(conv)

    if project_to_latent_dimension:
        conv = Flatten()(conv)
        conv = Dense(latent_dimension, activation='relu', input_shape=(6272,))(conv)

    return conv



def decoder(conv, filterSize, numberOfLayers, numberOfFilters, project_to_latent_dimension, latent_dimension):
    # idios xwrismos me ton encoder alla mirrored
    # to teleutaio 1/3 twn layers edw (h o,ti perissepse an den einai akrivws)

    #

    if project_to_latent_dimension:
        conv = Dense(6272, activation='relu', input_shape=(latent_dimension,))(conv)
        conv = Reshape((7,7,128))(conv)

    if numberOfLayers >= 3:
        for i in range(numberOfLayers // 3 + numberOfLayers % 3):
            conv = Conv2D(numberOfFilters * 4, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)

        conv = UpSampling2D((2,2))(conv)

        # to allo 1/3 twn layers
        for i in range(numberOfLayers // 3):
            conv = Conv2D(numberOfFilters * 2, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)

        conv = UpSampling2D((2, 2))(conv)

        # to 1/3 twn layers
        for i in range(numberOfLayers // 3):
            conv = Conv2D(numberOfFilters, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)

        decoded = Conv2D(1, (3, 3), activation='sigmoid', padding='same')(conv)  # 28 x 28 x 1
    else:
        if numberOfLayers > 1:
            conv = Conv2D(numberOfFilters * 2, filterSize, activation='relu', padding='same')(conv)
            conv = BatchNormalization()(conv)
            conv = UpSampling2D((2, 2))(conv)
        conv = Conv2D(numberOfFilters, filterSize, activation='relu', padding='same')(conv)
        conv = BatchNormalization()(conv)
        conv = UpSampling2D((2, 2))(conv)
        decoded = Conv2D(1, (3, 3), activation='sigmoid', padding='same')(conv)  # 28 x 28 x 1

    return decoded