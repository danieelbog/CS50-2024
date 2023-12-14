#include <cs50.h>
#include <stdio.h>

int get_height();

int main(void)
{
    int height = get_height();

    const string symbol = "#";
    const string spaceSymbol = " ";
    const int middle_space = 2;

    int left_current_available_space = height;
    int right_current_available_space = height;
    int middle_available_space = middle_space;

    for (int i = 0; i < height; i++)
    {
        if (left_current_available_space > 0)
        {
            left_current_available_space--;
            for (int j = 0; j < left_current_available_space; j++)
            {
                printf("%s", spaceSymbol);
            }
        }

        for (int j = left_current_available_space; j < height; j++)
        {
            printf("%s", symbol);
        }

        for (int j = 0; j < middle_space; j++)
        {
            printf("%s", spaceSymbol);
        }

        if (right_current_available_space > 0)
        {
            right_current_available_space--;
        }

        for (int j = right_current_available_space; j < height; j++)
        {
            printf("%s", symbol);
        }

        printf("\n");
    }
}

int get_height()
{
    int height = get_int("Height: ");
    if (height < 1 || height > 8)
    {
        return get_height();
    }

    return height;
}