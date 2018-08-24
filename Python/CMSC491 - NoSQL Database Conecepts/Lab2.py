import pymongo
import sys
# connect to mongodb
try:
    conn = pymongo.MongoClient('localhost:27017')
    db = conn.cmsc491
    conn.drop_database('cmsc491')
except pymongo.errors.ConnectionFailure as e:
    print("problem connecting to cmsc491", e)
    sys.exit(1)
# read in data to mongodb collections from txt files
hlc = db.cars
in_str = open("Cars_txt.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print(in_lst[i])
    hlc.insert_one(in_lst[i])
hlc = db.tests
in_str = open("Tests_txt.txt").read()
in_lst = eval(in_str)
for i in range(0, len(in_lst)):
    print(in_lst[i])
    hlc.insert_one(in_lst[i])
    
# part (c)
brake_tests = db.tests.find({'name' : 'Brake'})
valid_tags = ['ABC123', 'NOP901', 'DEF456', 'TUV234']
for doc in brake_tests:
    print("Car with tag ", doc.get('carTag'), " had brakes checked. Result was: ", doc.get('results'))
print("Expected:")
for tag in valid_tags:
    print(tag)