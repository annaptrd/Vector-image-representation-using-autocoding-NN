import matplotlib.pyplot as plt


def printGraphs(total_loss, total_val_loss, numberOfFilters, numberOfLayers, numberOfEpochs, filterSize_dim, filterSize, batchSize, learningRate, latent_dimension):
    # ektypwsi grafikwn opws stis diafaneies
    # ston x i kathe yperparametros
    # ston y to loss h to total loss

    x = numberOfFilters
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Filters')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Number of Filters')
    plt.show()

    x = numberOfLayers
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Layers')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Number of Layers')
    plt.show()

    x = numberOfEpochs
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Epochs')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Number of Epochs')
    plt.show()

    x = filterSize_dim
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Filter Size Dimension')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Filter Size Dimension')
    plt.show()

    x = batchSize
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Batch Size')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Batch Size')
    plt.show()

    x = learningRate
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Learning Rate')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Learning Rate')
    plt.show()

    x = latent_dimension
    y = total_loss
    plt.plot(x, y)
    plt.xlabel('Latent Dimension')
    plt.ylabel('Total Loss')
    plt.title('Loss ~ Latent Dimension')
    plt.show()

    x = numberOfFilters
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Filters')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Number of Filters')
    plt.show()

    x = numberOfLayers
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Layers')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Number of Layers')
    plt.show()

    x = numberOfEpochs
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Number of  Epochs')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Number of Epochs')
    plt.show()

    x = filterSize_dim
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Filter Size Dimension')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Filter Size Dimension')
    plt.show()

    x = batchSize
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Batch Size')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Batch Size')
    plt.show()

    x = learningRate
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Learning Rate')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Learning Rate')
    plt.show()

    x = latent_dimension
    y = total_val_loss
    plt.plot(x, y)
    plt.xlabel('Latent Dimension')
    plt.ylabel('Total Val Loss')
    plt.title('Val Loss ~ Latent Dimension')
    plt.show()