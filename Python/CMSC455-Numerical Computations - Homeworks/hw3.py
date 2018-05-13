#Nathaniel Fuller
#CMSC 455 HW3

from gauleg import gaulegf
import math
import numpy as np

def f(x):
  return math.sin(x)

def trap_int(f, xmin, xmax, nstep): # integrate f(x) from xmin to xmax
  area=(f(xmin)+f(xmax))/2.0
  h = (xmax-xmin)/nstep
  for i in range(1,nstep):
    x = xmin+i*h
    area = area + f(x)

  return area*h # trapezoidal method

print "-------------------------------------------------------------"
print "test_passing_function.py running"
print "1 a) f(x) = sin(x)\n"
xmin = 0.0
xmax = 1.0
n = 16
while (n <= 128):
  area = trap_int(f, xmin, xmax, n)
  print "number of points:", n
  print "trap_int area under f(x) from ",xmin," to ",xmax," = ",area
  print "error:", (area-(1.0-math.cos(1.0))), "\n"
  n = n*2

print "-------------------------------------------------------------"
print "1 b) f(x) = sin(x)\n"
print "calling x,w = gaulegf(0.0, 1.0, 8)"

x,w = gaulegf(0.0, 1.0, 8)

area = 0.0
for i in range(1, 9):
  area += w[i]*f(x[i])

print "area=", area
print "error:", (area-(1.0-math.cos(1.0))), "\n"

print "calling x,w = gaulegf(0.0, 1.0, 16)"

x,w = gaulegf(0.0, 1.0, 16)

area = 0.0
for i in range(1, 17):
  area += w[i]*f(x[i])

print "area=", area
print "error:", (area-(1.0-math.cos(1.0))), "\n"

print "-------------------------------------------------------------"
print "2) \n"
range1 = np.arange(-2.1, 2.1, 0.1)
range2 = np.arange(-0.1, 3.1, 0.1)

area = 0.1*0.1
n = 0

for i in range1:
  for j in range2:
    if ((i-2)**2 + (j-2)**2 > 1) and (i**2 + (j-2)**2 < 4) and (i**2 + j**2 < 9):
      n = n+1

print "number of dots:", n
print "area:", n*area

range1 = np.arange(-2.1, 2.1, 0.01)
range2 = np.arange(-0.1, 3.1, 0.01)

area = 0.01*0.01
n = 0

for i in range1:
  for j in range2:
    if ((i-2)**2 + (j-2)**2 > 1) and (i**2 + (j-2)**2 < 4) and (i**2 + j**2 < 9\
):
      n = n+1

print "number of dots:", n
print "area:", n*area

range1 = np.arange(-2.1, 2.1, 0.001)
range2 = np.arange(-0.1, 3.1, 0.001)

area = 0.001*0.001
n = 0

for i in range1:
  for j in range2:
    if ((i-2)**2 + (j-2)**2 > 1) and (i**2 + (j-2)**2 < 4) and (i**2 + j**2 < 9\
\
):
      n = n+1

print "number of dots:", n
print "area:", n*area

