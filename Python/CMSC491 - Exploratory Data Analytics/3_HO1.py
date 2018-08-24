import sqlite3 as lite
import sys
import statistics
con = lite.connect('UMBC.db')
cur = con.cursor()
myStmt = "select salary from instructor"
cur.execute(myStmt)
data = cur.fetchall()
salaries = []
for rec in data:
    salaries.append(rec[0])
con.close()
salaries.sort()
for salary in salaries: print salary

print "mean:", statistics.mean(salaries)
print "median:", statistics.median(salaries)
print "mode:", statistics.mode(salaries)
print "std:", statistics.stdev(salaries)
