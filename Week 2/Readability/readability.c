#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string next);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

int count_words(string text)
{
    int counter = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            counter++;
        }
    }
    return counter;
}