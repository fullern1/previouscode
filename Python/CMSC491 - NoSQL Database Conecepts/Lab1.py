import pymongo
import sys

# connect to mongodb
try:
    conn = pymongo.MongoClient('localhost:27017')
    db = conn.cmsc491
except pymongo.errors.ConnectionFailure as e:
    print "problem connecting to cmsc491", e
    sys.exit(1)

# read in data to mongodb collections from txt files
hlc = db.Accounts
in_str = open("Accounts.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print in_lst[i]
    hlc.insert(in_lst[i])

hlc = db.Branch
in_str = open("Branch.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print in_lst[i]
    hlc.insert(in_lst[i])

hlc = db.Customers
in_str = open("Customers.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print in_lst[i]
    hlc.insert(in_lst[i])

hlc = db.Loans
in_str = open("Loans.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print in_lst[i]
    hlc.insert(in_lst[i])

# find info from Customers collection about 'Smith'
print "\n Smith's Info:"
rs = db.Customers.find({"name": "Smith"},
                       {"_id": 0,"name": 1, "street": 1, "city": 1, "accounts": 1, "loans": 1})
for res in rs:
    print res

# find info from Loans collection about 'Smith'
print "\n Smith's Loans:"
rs = db.Loans.find({"customers": "Smith"},
                   {"_id": 0, "customers": 1, "loanNo": 1, "branch": 1, "amt": 1})
for res in rs:
    print res

# find branch names from Loans collection then find data about branches from Branch collection
print "\n Branch Info:"

rs = db.Loans.find({"customers": "Smith"},
                   {"_id": 0, "branch": 1})
branchNames = []
for i in rs:
    branchNames.append(i["branch"])

cusBranches = []
for j in branchNames:
    rs2 = db.Branch.find({"name": j},
                         {"_id": 0, "name": 1, "city": 1})
    for k in rs2:
        cusBranches.append(k)

for res in cusBranches:
    print res

# find information from Accounts collection about 'Smith'
rs = db.Accounts.find({"customers": "Smith"},
                      {"_id": 0, "balance": 1, "acctno": 1, "customers": 1, "branch": 1})
print "\n Accounts Info:"
for res in rs:
    print res

# drop collections after use to avoid duplication from multiple runs
db.Accounts.drop()
db.Branch.drop()
db.Customers.drop()
db.Loans.drop()
