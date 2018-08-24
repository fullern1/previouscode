import sqlite3 as lite
import linear_algebra as la

last_yr = [39500, 59500, 61000, 63000, 70000, 70000, 78500, 79000, 86000, 89000, 91500, 94000]

con = lite.connect("UMBC.db")
cur = con.cursor()
myStmt = "select salary from instructor order by salary"
cur.execute(myStmt)
data = cur.fetchall()
salaries = []
for rec in data:
    salaries.append(rec[0])
con.close()
salaries.sort()
print "Last year salaries", last_yr
print "Current salaries", salaries

raises = la.vector_subtract(salaries, last_yr)
print "Raises from last year", raises

adjustment = la.scalar_multiply(1.05, salaries)
print "Adjusted for cost of living", adjustment

