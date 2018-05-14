#Nathaniel Fuller
#fullern1@umbc.edu
#cmsc 455 hw 1

t = 0.0
dt = 0.1
h = 0.0
v = 0.0
a = 0.0
F = 0.0
Rho = 1.293
g = 9.80665
# Ft = force of thrust
Ft = [6, 13.2, 4.8]
F = 0.0
thrust = 0.0
massB = .0340
massEStart = .0242
massEFinal = .0094
massTotal = massB+massEStart
bodyCD = .45
bodyA = .000506
finsCD = .01
finsA = .00496
fdBody = (bodyCD*Rho*bodyA*v)/2
fdFins = (finsCD*Rho*finsA*v)/2
fg = massTotal*g

print("Values:\nTime (s), Height (m), Vel (m/s), Accel (m/s^2), Force (N), Mass (kg)")
while (v >= 0):
    #print out values ---------------------------- 
    #print: time, height, velocity, acceleration, force, mass
    print round(t,4), "s,", round(h,4), "m,", round(v,4), "m/s,", round(a,4), "m/s^2,", round(F,4), "N,", round(massTotal,4), "kg"

    #do computations -----------------------------
    t += dt
    
    #get correct estimated force of thrust
    if (t < 0.4):
        thrust = Ft[int(t*10)-1]
    elif (t >= .4) and (t < 1.9):
        thrust = 4.4
    else:
        thrust = 0.0

    #force
    F = thrust - (((bodyCD*Rho*bodyA*(v*v))/2)+((finsCD*Rho*finsA*(v*v))/2)+fg)

    #mass of rocket
    massTotal = massTotal - 0.0001644*thrust

    #force of gravity
    fg = massTotal*g

    #acceleration
    a = F/massTotal

    #change in velocity
    vChange = a*dt
    v = v+vChange

    #change in distance
    hChange = v*dt
    h = h+hChange
    
