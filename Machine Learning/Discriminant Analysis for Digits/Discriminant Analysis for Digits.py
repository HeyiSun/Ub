from PIL import Image
from mnist import MNIST
import numpy as np
import os

def bigw(x):
    return -1.0/2.0*np.linalg.pinv(x)

def smallw(x,y):
    return np.dot(np.linalg.pinv(x),y)

def discriminant(x,i,args):
    avg,cova,prob=args
    first=np.diag(np.dot(np.dot(x,bigw(cova[i])),np.transpose(x)))
    second=np.dot(np.transpose(smallw(cova[i],np.transpose([avg[i]]))),np.transpose(x))
    third1=-1.0/2.0*np.dot(np.dot(avg[i],np.linalg.pinv(cova[i])),np.transpose(avg[i])) 
    third2=np.log(prob[i]/np.sum(prob))
    return first+second+third1+third2

def classify(x,arg):
    output=list([])
    for i in range(10):
        output=np.append(output,discriminant(x,i,arg))
    return output

def var(x):
    a=[]
    for i in range(len(x)):
        a.append(x[i,i])
    return a
"""***********************************************Start Here*********************************************"""
mndata=MNIST(os.path.split(os.path.realpath(__file__))[0])
images,labels=mndata.load_training()
t_images,t_labels=mndata.load_testing()


avg=[]
for i in range(10):
    avg.append([])

idx=0
for i in images:
    label=labels[idx]
    avg[label].append(images[idx])
    idx=idx+1

prob=[]
cova=avg.copy()
"""mean value"""
for i in range(len(avg)):
    prob.append(len(avg[i]))
    avg[i]=np.mean(np.transpose(avg[i]),1)
#print(np.sum(prob))
"""covariance matrix"""
for i in range(len(cova)):
    cova[i]=np.cov(np.transpose(cova[i]))

args=(avg,cova,prob)
true=0
false=0
idx=0

"""make the deicision and calculate the accuracy"""
a=np.argmax(classify(t_images,args).reshape(10,10000),0)
for i in range(len(t_images)):
    if(a[i]==t_labels[i]):
        true=true+1
    else:
        false=false+1
    
print('accuracy='+str(100*true/(true+false))+'%')

"""Produce the images of mean and variance"""
for i in range(10):
    img = Image.fromarray(np.reshape(avg[i],(28,28)).astype(np.uint8))
    img.save('mean_of_'+str(i)+'.bmp')
    #img.show()
for i in range(10):
    img1 = Image.fromarray(np.reshape(var(cova[i]),(28,28)).astype(int))
    img1.save('variance_of_'+str(i)+'.png')
