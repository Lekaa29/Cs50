# TODO

number = 0
number = int(input("Number: "))
sumx = 0
sum = 0
x = 0
test = 0
type = ""

if (number > 999999999999 and number < 10000000000000):  # checking length
    test = number // 100000000000
if (number > 99999999999999 and number < 1000000000000000):
    test = number // 10000000000000
if (number > 999999999999999 and number < 10000000000000000):
    test = number // 100000000000000

if (test == 34 or test == 37):
    type = "AMEX"
elif test == 51 or test == 52 or test == 53 or test == 54 or test == 55:
    type = "MASTERCARD"
elif ((test // 10) == 4):
    type = "VISA"
else:
    type = "INVALID"


if (type != "INVALID"):   # checks if is right size
    while (number > 9):
        x = number % 10
        sum = sum + x
        number = number // 10
        x = number % 10
        if ((x*2) < 10):
            sumx = sumx + (x*2)
        else:
            x = (x*2) % 10
            sumx = sumx + 1 + x

        number = number // 10
    sum = sum + number

if (((sumx+sum) % 10) == 0):

    print(type)  # prints result
else:
    print("INVALID")
