import numpy as np
from scipy.optimize import minimize
from scipy.io import loadmat
from math import sqrt
import time
import pickle

def initializeWeights(n_in, n_out):
    """
    # initializeWeights return the random weights for Neural Network given the
    # number of node in the input layer and output layer

    # Input:
    # n_in: number of nodes of the input layer
    # n_out: number of nodes of the output layer
       
    # Output: 
    # W: matrix of random initial weights with size (n_out x (n_in + 1))"""

    epsilon = sqrt(6) / sqrt(n_in + n_out + 1)
    W = (np.random.rand(n_out, n_in + 1) * 2 * epsilon) - epsilon
    return W


def sigmoid(z):
    
    return 1.0/(1.0+np.exp(-1.0*z))
    """# Notice that z can be a scalar, a vector or a matrix
    # return the sigmoid of input z"""

    # your code here


def preprocess():
    """ Input:
     Although this function doesn't have any input, you are required to load
     the MNIST data set from file 'mnist_all.mat'.

     Output:
     train_data: matrix of training set. Each row of train_data contains 
       feature vector of a image
     train_label: vector of label corresponding to each image in the training
       set
     validation_data: matrix of training set. Each row of validation_data 
       contains feature vector of a image
     validation_label: vector of label corresponding to each image in the 
       training set
     test_data: matrix of training set. Each row of test_data contains 
       feature vector of a image
     test_label: vector of label corresponding to each image in the testing
       set

     Things to do for preprocessing step:
     - remove features that have the same value for all data points
           with corresponding labels
     - convert original data set from integer to double by using double()
           function
     - normalize the data to [0, 1]
     - divide the original data set to training, validation and testing set"""

    mat = loadmat('mnist_all.mat') #loads the MAT object as a Dictionary
    train_data = np.concatenate((mat['train0'], mat['train1'],
                                 mat['train2'], mat['train3'],
                                 mat['train4'], mat['train5'],
                                 mat['train6'], mat['train7'],
                                 mat['train8'], mat['train9']), 0)
    #print(mat['train0'].shape)
    train_label = np.concatenate((np.ones((mat['train0'].shape[0], 1), dtype='uint8'),
                                  2 * np.ones((mat['train1'].shape[0], 1), dtype='uint8'),
                                  3 * np.ones((mat['train2'].shape[0], 1), dtype='uint8'),
                                  4 * np.ones((mat['train3'].shape[0], 1), dtype='uint8'),
                                  5 * np.ones((mat['train4'].shape[0], 1), dtype='uint8'),
                                  6 * np.ones((mat['train5'].shape[0], 1), dtype='uint8'),
                                  7 * np.ones((mat['train6'].shape[0], 1), dtype='uint8'),
                                  8 * np.ones((mat['train7'].shape[0], 1), dtype='uint8'),
                                  9 * np.ones((mat['train8'].shape[0], 1), dtype='uint8'),
                                  10 * np.ones((mat['train9'].shape[0], 1), dtype='uint8')), 0)
    test_label = np.concatenate((np.ones((mat['test0'].shape[0], 1), dtype='uint8'),
                                 2 * np.ones((mat['test1'].shape[0], 1), dtype='uint8'),
                                 3 * np.ones((mat['test2'].shape[0], 1), dtype='uint8'),
                                 4 * np.ones((mat['test3'].shape[0], 1), dtype='uint8'),
                                 5 * np.ones((mat['test4'].shape[0], 1), dtype='uint8'),
                                 6 * np.ones((mat['test5'].shape[0], 1), dtype='uint8'),
                                 7 * np.ones((mat['test6'].shape[0], 1), dtype='uint8'),
                                 8 * np.ones((mat['test7'].shape[0], 1), dtype='uint8'),
                                 9 * np.ones((mat['test8'].shape[0], 1), dtype='uint8'),
                                 10 * np.ones((mat['test9'].shape[0], 1), dtype='uint8')), 0)
    test_data = np.concatenate((mat['test0'], mat['test1'],
                                mat['test2'], mat['test3'],
                                mat['test4'], mat['test5'],
                                mat['test6'], mat['test7'],
                                mat['test8'], mat['test9']), 0)
    validation_data=np.concatenate((train_data[0:1000],
                                   train_data[6000:7000],
                                   train_data[12000:13000],
                                   train_data[18000:19000],
                                   train_data[24000:25000],
                                   train_data[30000:31000],
                                   train_data[36000:37000],
                                   train_data[42000:43000],
                                   train_data[48000:49000],
                                   train_data[54000:55000]),0)
    tmp=train_data.copy()
    train_data=np.concatenate((tmp[1000:6000],
                                   tmp[7000:12000],
                                   tmp[13000:18000],
                                   tmp[19000:24000],
                                   tmp[25000:30000],
                                   tmp[31000:36000],
                                   tmp[37000:42000],
                                   tmp[43000:48000],
                                   tmp[49000:54000],
                                   tmp[55000:60000]),0)
    
    validation_label=np.concatenate((train_label[0:1000],
                                   train_label[6000:7000],
                                   train_label[12000:13000],
                                   train_label[18000:19000],
                                   train_label[24000:25000],
                                   train_label[30000:31000],
                                   train_label[36000:37000],
                                   train_label[42000:43000],
                                   train_label[48000:49000],
                                   train_label[54000:55000]),0)
    tmp=train_label.copy()
    train_label=np.concatenate((tmp[1000:6000],
                                   tmp[7000:12000],
                                   tmp[13000:18000],
                                   tmp[19000:24000],
                                   tmp[25000:30000],
                                   tmp[31000:36000],
                                   tmp[37000:42000],
                                   tmp[43000:48000],
                                   tmp[49000:54000],
                                   tmp[55000:60000]),0)
    # remove features that have same value for all points in the training data
    # convert data to double
    # normalize data to [0,1]
    
    # Split train_data and train_label into train_data, validation_data and train_label, validation_label
    # replace the next two lines
    
       
    #Simplify the features
    feature_size=train_data.shape[1]
    sample_size=train_data.shape[0]
    for j in range(feature_size-1,-1,-1):
        #print(j)
        flag=0
        tmp_pixal=train_data[1,j]
        for i in range(sample_size):
            if(train_data[i,j]!=tmp_pixal):
                flag=1
                break
        if(flag==0):
            #print("delete"+str(j))
            train_data=np.delete(train_data,j,1)
            test_data=np.delete(test_data,j,1)
            validation_data=np.delete(validation_data,j,1)
            
    
    #Change the type
    train_data=train_data.astype(float);
    validation_data=validation_data.astype(float)
    test_data=test_data.astype(float);
    
    #Normalization
    train_data=train_data/255
    validation_data=validation_data/255
    test_data=test_data/255
    
    #Reset the label to 0~9
    test_label=test_label-1
    train_label=train_label-1
    validation_label=validation_label-1
    
    print("preprocess done!")
    return train_data, train_label, validation_data, validation_label, test_data, test_label


def nnObjFunction(params, *args):
    """
    % nnObjFunction computes the value of objective function (negative log 
    %   likelihood error function with regularization) given the parameters 
    %   of Neural Networks, thetraining data, their corresponding training 
    %   labels and lambda - regularization hyper-parameter.

    % Input:
    % params: vector of weights of 2 matrices w1 (weights of connections from
    %     input layer to hidden layer) and w2 (weights of connections from
    %     hidden layer to output layer) where all of the weights are contained
    %     in a single vector.
    % n_input: number of node in input layer (not include the bias node)
    % n_hidden: number of node in hidden layer (not include the bias node)
    % n_class: number of node in output layer (number of classes in
    %     classification problem
    % training_data: W of training data. Each row of this matrix
    %     represents the feature vector of a particular image
    % training_label: the vector of truth label of training images. Each entry
    %     in the vector represents the truth label of its corresponding image.
    % lambda: regularization hyper-parameter. This value is used for fixing the
    %     overfitting problem.
       
    % Output: 
    % obj_val: a scalar value representing value of error function
    % obj_grad: a SINGLE vector of gradient value of error function
    % NOTE: how to compute obj_grad
    % Use backpropagation algorithm to compute the gradient of error function
    % for each weights in weight matrices.

    %%%%%%%%%%%%%%%%i%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % reshape 'params' vector into 2 matrices of weight w1 and w2
    % w1: matrix of weights of connections from input layer to hidden layers.
    %     w1(i, j) represents the weight of connection from unit j in input 
    %     layer to unit i in hidden layer.
    % w2: matrix of weights of connections from hidden layer to output layers.
    %     w2(i, j) represents the weight of connection from unit j in hidden 
    %     layer to unit i in output layer."""
    
    n_input, n_hidden, n_class, training_data, training_label, lambdaval = args

    w1 = params[0:n_hidden * (n_input + 1)].reshape((n_hidden, (n_input + 1)))   #50*samples
    w2 = params[(n_hidden * (n_input + 1)):].reshape((n_class, (n_hidden + 1)))  #10*50   
    
    # Your code here
    xx=np.concatenate((training_data,np.ones((training_data.shape[0],1))),1) #training_data with node xx samples*785
    hhh=sigmoid(np.dot(np.concatenate((training_data,np.ones((training_data.shape[0],1))),1),w1.T))#hidden node without bias    hh sample*50 
    hh=np.concatenate((hhh,np.ones((hhh.shape[0],1))),1) #add bias for hidden node   hh samples*51
    oo=sigmoid(np.dot(np.concatenate((hhh,np.ones((hhh.shape[0],1))),1),w2.T))#oo  samples*10
    
    #通过label计算yy   samples*10
    yy=np.zeros(oo.shape)
    for i in range(training_label.shape[0]):
        yy[i][training_label[i]]=1
    
    #calculate the Error and Gradience
    Error=np.sum(yy*np.log(oo)+(1-yy)*np.log(1-oo))*(-1)/training_data.shape[0]
    grad_w2=np.dot((oo-yy).T,hh)/training_data.shape[0]
    grad_w1=np.dot(((1-hhh)*hhh*np.dot((oo-yy),np.delete(w2,w2.shape[1]-1,1))).T,xx)/training_data.shape[0]
    
    #Regularization
    Error=Error+lambdaval*(np.sum(w1**2)+np.sum(w2**2))/(2*training_data.shape[0])
    grad_w2=grad_w2+lambdaval*w2/training_data.shape[0]
    grad_w1=grad_w1+lambdaval*w1/training_data.shape[0]
    
    obj_grad = np.concatenate((grad_w1.flatten(), grad_w2.flatten()),0)
    obj_val=Error
    #print('Error Func='+str(obj_val))
    return (obj_val, obj_grad)
    #
    # Make sure you reshape the gradient matrices to a 1D array. for instance if your gradient matrices are grad_w1 and grad_w2
    # you would use code similar to the one below to create a flat array
    # obj_grad = np.concatenate((grad_w1.flatten(), grad_w2.flatten()),0)
    #obj_grad = np.array([])

    


def nnPredict(w1, w2, data):
    """% nnPredict predicts the label of data given the parameter w1, w2 of Neural
    % Network.

    % Input
    % w1: matrix of weights of connections from input layer to hidden layers.
    %     w1(i, j) represents the weight of connection from unit i in input 
    %     layer to unit j in hidden layer.
    % w2: matrix of weights of connections from hidden layer to output layers.
    %     w2(i, j) represents the weight of connection from unit i in input 
    %     layer to unit j in hidden layer.
    % data: matrix of data. Each row of this matrix represents the feature 
    %       vector of a particular image
       
    % Output: 
    % label: a column vector of predicted labels"""
    xx=np.concatenate((data,np.ones((data.shape[0],1))),1) #add bias
    hhh=sigmoid(np.dot(xx,w1.T))
    hh=np.concatenate((hhh,np.ones((hhh.shape[0],1))),1)
    oo=sigmoid(np.dot(hh,w2.T)) #hidden node without bias    hh sample*50
    
    labels=np.argmax(oo,1)
    return np.transpose([labels])


"""**************Neural Network Script Starts here********************************"""


train_data, train_label, validation_data, validation_label, test_data, test_label = preprocess()

#  Train Neural Network

# set the number of nodes in input unit (not including bias unit)
n_input = train_data.shape[1]

# set the number of nodes in hidden unit (not including bias unit)
n_hidden = 50

# set the number of nodes in output unit
n_class = 10

# initialize the weights into some random matrices
initial_w1 = initializeWeights(n_input, n_hidden)
initial_w2 = initializeWeights(n_hidden, n_class)

# unroll 2 weight matrices into single column vector
initialWeights = np.concatenate((initial_w1.flatten(), initial_w2.flatten()), 0)

# set the regularization hyper-parameter
lambdaval = 0

args = (n_input, n_hidden, n_class, train_data, train_label, lambdaval)

# Train Neural Network using fmin_cg or minimize from scipy,optimize module. Check documentation for a working example

opts = {'maxiter': 50}  # Preferred value.

nn_params = minimize(nnObjFunction, initialWeights, jac=True, args=args, method='CG', options=opts)

# In Case you want to use fmin_cg, you may have to split the nnObjectFunction to two functions nnObjFunctionVal
# and nnObjGradient. Check documentation for this function before you proceed.
# nn_params, cost = fmin_cg(nnObjFunctionVal, initialWeights, nnObjGradient,args = args, maxiter = 50)


# Reshape nnParams from 1D vector into w1 and w2 matrices
w1 = nn_params.x[0:n_hidden * (n_input + 1)].reshape((n_hidden, (n_input + 1)))
w2 = nn_params.x[(n_hidden * (n_input + 1)):].reshape((n_class, (n_hidden + 1)))

# Test the computed parameters

predicted_label = nnPredict(w1, w2, train_data)

# find the accuracy on Training Dataset

print('\n Training set Accuracy:' + str(100 * np.mean((predicted_label == train_label).astype(float))) + '%')

predicted_label = nnPredict(w1, w2, validation_data)

# find the accuracy on Validation Dataset

print('\n Validation set Accuracy:' + str(100 * np.mean((predicted_label == validation_label).astype(float))) + '%')

predicted_label = nnPredict(w1, w2, test_data)

# find the accuracy on Validation Dataset

print('\n Test set Accuracy:' + str(100 * np.mean((predicted_label == test_label).astype(float))) + '%')
