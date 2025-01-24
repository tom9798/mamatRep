import sys
def phase_5():
    # Simulating the stack and input
    input_data = input("Enter two integers: ")
    values = list(map(int, input_data.split()))

    if len(values) < 2:
        print("Invalid input")

    num1 = values[0]
    num1_masked = num1 & 0x0F

    if num1_masked == 0x0F:
        print("Bomb exploded!")

    sum_counter = 0
    counter = 0
    array = [10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6, 5]
    #        0   1  2   3  4  5   6   7   8  9  10 11 12 13 14 15   indexes

    while True:
        counter += 1
        if counter > 15:
            break
        num1 = array[num1 % 16]
        sum_counter += num1

        if num1 == 0x0F:
            break

    if counter != 15:
        # print all the values
        print("sum: ", sum_counter, ", counter: ", counter)
        explode_bomb()

    if sum_counter != values[1]:
        # print all the values
        print("sum: ", sum_counter, ", counter: ", counter)
        explode_bomb()


def explode_bomb():
    print("Bomb exploded!")
    sys.exit(1)

# run it with the inputs
phase_5()
