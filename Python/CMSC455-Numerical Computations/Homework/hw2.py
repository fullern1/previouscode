#Nathaniel Fuller
#CMSC 455 Hw2

from numpy import array
from numpy import polyfit
from numpy import polyval
import numpy as np
import warnings
warnings.simplefilter('ignore', np.RankWarning)
#without ignore warnings n=18 and 19 give:
#RankWarning: Polyfit may be poorly conditioned
# warnings.warn(msg, RankWarning)

def frange(start, stop, step):
    i = start
    while i < stop:
        yield i
        i += step

times = []
thrust = [0,6,13.2,4.8,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,4.4,0]

#add times 0.0 through 1.9 to array
for i in frange(0.0, 2.0, 0.1):
    times.append(i)

print "Hw 2 - Least Square Fit - Errors:"

j = range(3,20)
for i in j:
    pf=polyfit(times,thrust,i)
    pv=polyval(pf,times)
    err=abs(thrust-pv)

    print "n="+str(i)+", max="+str(max(err))+", avg="+str(sum(err)/len(err))+", rms="+str((sum(err*err)/len(err))**(1/2.0))

