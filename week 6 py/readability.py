# TODO
from cs50 import get_string


def main():
    text = get_string("Text: ")
    sent = 0
    spaces = 0
    let = 0
    numb = 0

    for i in range(0, len(text)):
        numb = text[i]
        if ((ord(numb) > 64 and ord(numb) < 91) or (ord(numb) > 96 and ord(numb) < 123)):
            let += 1
        if (ord(numb) == 32):
            spaces += 1
        if (ord(numb) == 63 or ord(numb) == 46 or ord(numb) == 33):
            sent += 1

    spaces += 1

    index = 0.0588 * ((let / spaces) * 100) - 0.296 * ((sent / spaces) * 100) - 15.8

    result = round(index)

    if (index > 15.49):
        print("Grade 16+")

    elif (index > 0.99):
        print("Grade", result)
    else:
        print("Before Grade 1")


main()
