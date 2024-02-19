from cs50 import get_int


def main():
    height = get_height()
    print_pyramid(height)


def get_height():
    height = get_int("Height: ")
    if (height < 1 or height > 8):
        return get_height()
    return height


def print_pyramid(n):
    i = 1
    while i <= n:
        print_space(n-i)
        print_symbol(i)
        print_space(2)
        print_symbol(i)
        i += 1
        print()


def print_symbol(n):
    for i in range(n):
        print("#", end="")


def print_space(n):
    for i in range(n):
        print(" ", end="")


main()
