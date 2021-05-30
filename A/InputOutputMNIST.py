
import struct as st
import numpy as np

def readMNIST(filename):
    imagesfile = open(filename, 'rb')

    # magic number
    imagesfile.seek(0)
    magic = st.unpack('>4B', imagesfile.read(4))

    print("Magic number: {0} ".format(magic))

    # dimensions
    numberOfImages = st.unpack('>I', imagesfile.read(4))[0]
    rows = st.unpack('>I', imagesfile.read(4))[0]
    columns = st.unpack('>I', imagesfile.read(4))[0]

    print("rows: {0} ".format(rows))
    print("cols: {0} ".format(columns))

    # store images
    nBytesTotal = numberOfImages*rows*columns*1
    images_collection = np.asarray(st.unpack('>'+'B'*nBytesTotal, imagesfile.read(nBytesTotal))).reshape((numberOfImages,rows, columns))
    images_collection = images_collection.reshape(images_collection.shape[0], 28, 28, 1)
    images_collection = images_collection.astype('float32')
    images_collection /= 255
    imagesfile.close()
    return images_collection



def writeMNIST(images_collection, filename, D):
    magicnumber = 2052
    numberOfImages = len(images_collection)
    rows = 1
    columns = D
    imagesfile = open(filename, 'wb')

    # magic number
    output = st.pack('>I', magicnumber)
    imagesfile.write(output)

    output = st.pack('>I', numberOfImages)
    imagesfile.write(output)

    output = st.pack('>I', 1)
    imagesfile.write(output)

    output = st.pack('>I', D)
    imagesfile.write(output)


    m = np.amin(images_collection)
    n = np.amax(images_collection)

    print(" images_collection xi = [%d,%d]" % (m,n))

    normalizer = lambda x: 25500 * (x - m) / (n - m)

    images_collection = normalizer(images_collection)

    m = np.amin(images_collection)
    n = np.amax(images_collection)

    print(" images_collection xi (norm) = [%d,%d]" % (m, n))

    images_collection = images_collection.astype('int16')

    m = np.amin(images_collection)
    n = np.amax(images_collection)

    print(" images_collection xi (norm) = [%d,%d]" % (m, n))

    bytes = images_collection.flatten(order ='C').tobytes(order='C')

    imagesfile.write(bytes)

    #images_collection = np.asarray(st.unpack('>'+'B'*nBytesTotal, imagesfile.read(nBytesTotal))).reshape((numberOfImages,rows, columns))
    imagesfile.close()

    # return images_collection
