def dec2bin(x):
    bin = '0'
    for i in range(23):
        x *= 2
        if x >= 1:
            bin += '1'
            x -= 1
        else:
            bin += '0'
    print(bin)
