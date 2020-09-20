import csv
import hashlib

with open('UserInfo.csv') as csvfile:
    with open('UserInfo_Hashed.csv', 'w') as newfile:
        reader = csv.DictReader(csvfile)
        for i,r in enumerate(reader):
            if i is 0:
                newfile.write(','.join(r) + '\n')
                    
            hashing = hashlib.sha256((r['Password']).encode('utf-8')).hexdigest()

            r["Password"] = hashing

            hashing2 = hashlib.sha256((r['CC']).encode('utf-8')).hexdigest()
            r["CC"] = hashing2

            newfile.write(','.join(r.values()) + '\n')
