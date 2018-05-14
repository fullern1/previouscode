#Nathaniel Fuller
#CMSC 455 hw6

# time_matmul.c  fine how large matrix multiple can be 
#                check that time increases order n^3   
#                doubling N takes 8 times as long      
#                can be days for 10,000 by 10,000      

from time import time

for N in [100, 200, 400, 800]: # N<1600 is OK, takes minutes 
    print "multiply N by N matrices, N=%d" %(N)
    a = [[0 for j in range(N)] for i in range(N)]
    b = [[0 for j in range(N)] for i in range(N)]
    c = [[0 for j in range(N)] for i in range(N)]
    for i in range(N):
      for j in range(N):
        a[i][j] = 1.0+i
        b[i][j] = 1.0+j
    print "initialized"
    t1 = time()
    for i in range(N):
      for j in range(N):
        c[i][j] = 0.0
        for k in range(N):
          c[i][j] = c[i][j] + a[i][k]*b[k][j] # most time spent here! 

    t2 = time()
    dt = t2-t1
    print "N=%d, c=%g, raw time=%g" %(N, c[5][5], dt)
    t2 = 1.0e9*(t2-t1)/(N*N*N)
    print "order N^3 normalized time=%g \n" %(t2)

# end time_matmul.py
