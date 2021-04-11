import binascii


def convertToHex(path):

    with open(path, "rb") as file:
        string = file.read()

    string = binascii.hexlify(string).decode()

    string = [string[i:i + 2] for i in range(0, len(string), 2)]

    for a in range(0, len(string)):
        string[a] = "0x" + string[a]

    print(len(string))

    string = ','.join(string)

    print(string)


def main():
    path = ""  # add path to the file you want to convert

    convertToHex(path)


if __name__ == '__main__':
    main()
