# TODO
import cs50 as cs

x = 0

while (x == 0):
    height = str(input("Height: "))  # gets height

    if (height != ""):
        if (ord(height[0]) > 47 and ord(height[0]) < 58):  # checks if ascii is number
            if (int(height) > 0 and int(height) < 9):
                height = int(height)  # converts tu number
                x = 1

for i in range(1, height+1):
    print(" "*(height-i) + "#"*i + "  " + "#"*i)