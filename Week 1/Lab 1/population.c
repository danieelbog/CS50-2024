#include <cs50.h>
#include <stdio.h>

int get_start_size();
int get_end_size(int minSize);
int calcualte_years_until_threshold(int startSize, int endSize);

int main(void)
{
    int startSize = get_start_size();
    int endSize = get_end_size(startSize);

    int years = calcualte_years_until_threshold(startSize, endSize);

    printf("Years: %i\n", years);
}

int get_start_size()
{
    int size = get_int("Start size: ");
    if (size < 9)
    {
        return get_start_size();
    }

    return size;
}

int get_end_size(int minSize)
{
    int size = get_int("End size: ");
    if (size < minSize)
    {
        return get_end_size(minSize);
    }

    return size;
}

int calcualte_years_until_threshold(int startSize, int endSize)
{
    int years = 0;
    while (startSize < endSize)
    {
        int newLlamas = startSize / 3;
        int passedAway = startSize / 4;

        startSize = startSize + newLlamas - passedAway;
        years++;
    }

    return years;
}