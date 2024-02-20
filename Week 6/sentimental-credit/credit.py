from cs50 import *


def main():
    number = cs50.get_string("Number: ")
    number_lenght = len(number)

    if (number_lenght != 13 and number_lenght != 15 and number_lenght != 16):
        print("INVALID")
        return

    sum_numbers = 0
    i = number_lenght - 1
    while (i >= 0):
        sum_numbers += int(number[i])
        temp_sum_multiplied_numbers = int(number[i-1]) * 2
        if (i - 1 >= 0):
            if (temp_sum_multiplied_numbers < 10):
                sum_numbers += temp_sum_multiplied_numbers
            else:
                temp_sum_multiplied_numbers_str = str(temp_sum_multiplied_numbers)
                sum_numbers += int(temp_sum_multiplied_numbers_str[0])
                sum_numbers += int(temp_sum_multiplied_numbers_str[1])
        i -= 2

    if (sum_numbers % 10 != 0):
        print("INVALID")
        return

    if ((int(number[:2]) == 34 or int(number[:2]) == 37) and number_lenght == 15):
        print("AMEX")
    elif ((int(number[:2]) >= 51 and int(number[:2]) <= 55) and number_lenght == 16):
        print("MASTERCARD")
    elif ((int(number[:2]) >= 40 and int(number[:2]) <= 49) and (number_lenght == 13 or number_lenght == 16)):
        print("VISA")
    else:
        print("INVALID")
        return


main()
