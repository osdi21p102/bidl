import os
import sys
import random
n = 2000
accounts = 10000

names = []

chs="qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890"

op = ['create_account', 'send_payment']

template1 = "{\"Args\":[\"%s\", \"%s\", \"%s\", \"%s\", \"%s\"]}"
template2 = "{\"Args\":[\"%s\", \"%s\", \"%s\", \"%s\"]}"


def getName():
    res = ""
    for i in range(64):
        idx = random.randint(0, len(chs) - 1)
        res += chs[idx]
    return res

def getAccount():
    idx = random.randint(0, len(names) - 1)
    return names[idx]


for i in range(accounts):
    name = getName()
    names.append(name)
    print(template1 % (op[0], name, name, "1000000", "1000000"))

#for i in range(n - accounts):
#    name1 = getAccount()
#    name2 = getAccount()
#    while name2 == name1:
#        name2 = getAccount()
#    print(template2 % (op[1], "10", name1, name2))
