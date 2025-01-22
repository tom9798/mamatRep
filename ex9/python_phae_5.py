def phase_5(input):
    try:
        num1, num2 = map(int, input.split())
    except ValueError:
        explode_bomb()
        return

    num1 = num1 % 16  # masking the last 4 bits of the first integer
    if num1 == 0xf:
        print("BOOM!!!")
        return

    sum = 0  # sum = 0
    count = 0  # counter = 0
    values = [10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5]  # the array

    while num1 != 0xf:  # while loop until num1 % 16 == 15
        sum += values[num1-1]
        num1 += 1
        count += 1
        print("sum: ", sum)

    if count != 0xf or sum != num2:  # check if the counter is 15 and compare the sum with the second integer
        print("BOOM!!!")
        return

    print("Bomb defused")
    return

# run it with the inputs
phase_5("0 115")
