#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit_card_number = get_long_long("Number: ");

    int card_numbers_to_check_sum = 0;
    long credit_card_number_to_check = credit_card_number / 10;

    while (credit_card_number_to_check > 0)
    {
        int number = credit_card_number_to_check % 10 * 2;
        if (number < 10)
        {
            card_numbers_to_check_sum += number;
        }
        else
        {
            card_numbers_to_check_sum += number % 10;
            number /= 10;
            card_numbers_to_check_sum += number;
        }

        credit_card_number_to_check /= 100;
    }

    credit_card_number_to_check = credit_card_number;
    while (credit_card_number_to_check > 0)
    {
        card_numbers_to_check_sum += credit_card_number_to_check % 10;
        credit_card_number_to_check /= 100;
    }

    if (card_numbers_to_check_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int length = 2;
        while (credit_card_number >= 100)
        {
            credit_card_number /= 10;
            length++;
        }

        if ((credit_card_number == 34 || credit_card_number == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if (credit_card_number >= 51 && credit_card_number <= 55 && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (credit_card_number >= 40 && credit_card_number <= 49 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}