#Nathaniel Fuller
#CMSC 455 project

import numpy as np

def func(i, j):
    return np.exp(np.sin(60*i))+np.sin(50*np.exp(j))+np.sin(80*np.sin(i))+np.sin(np.sin(70*j))-np.sin(10*(i+j))+(i*i+j*j)/4

xMin=0
yMin=0
minVal=100 #large number guaranteed to not be min

xArray=np.arange(-1,1.001,0.001)
yArray=np.arange(-1,1.001,0.001)

for i in xArray:
    for j in yArray:
        currVal = func(i,j)
        if currVal < minVal:
            minVal = currVal
            xMin = i
            yMin = j

print "Global search done"
print "Min:",minVal
print "X:  ",xMin
print "Y:  ",yMin

dx = 0.00001
while (dx > 0.00000000001):
    A=[func(xMin-dx,yMin+dx),
       func(xMin,yMin+dx),
       func(xMin+dx,yMin+dx),
       func(xMin-dx,yMin),
       minVal,
       func(xMin+dx,yMin),
       func(xMin-dx,yMin-dx),
       func(xMin,yMin-dx),
       func(xMin+dx,yMin-dx)]

    newMin = min(A)

    if newMin==minVal:
        dx=dx/10
    else:
        if newMin==A[0]:
            xMin=xMin-dx
            yMin=yMin+dx
        elif newMin==A[1]:
            yMin=yMin+dx
        elif newMin==A[2]:
            xMin=xMin+dx
            yMin=yMin+dx
        elif newMin==A[3]:
            xMin=xMin-dx
        elif newMin==A[5]:
            xMin=xMin+dx
        elif newMin==A[6]:
            xMin=xMin-dx
            yMin=yMin-dx
        elif newMin==A[7]:
            yMin=yMin-dx
        elif newMin==A[8]:
            xMin=xMin+dx
            yMin=yMin-dx
    minVal=newMin

print "Local search done:"
print "Min:",minVal
print "X:  ",xMin
print "Y:  ",yMin




