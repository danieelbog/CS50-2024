# Credit Card Validator

## Introduction

A program to validate credit card numbers using Luhn's algorithm. This program checks if a credit card number is a valid American Express, MasterCard, or Visa card number based on their respective formats and checksums.

## Background

Credit card numbers have specific formats and a built-in checksum. American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers. Luhn's algorithm is employed to determine the syntactic validity of a credit card number.

## Luhn's Algorithm

1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2. Add the sum to the sum of the digits that weren’t multiplied by 2.
3. If the total’s last digit is 0, the number is valid.

## Example

For example, considering David’s Visa: 4003600000000014.

1. Underline every other digit, starting with the number’s second-to-last digit: 4003600000000014.
2. Multiply each underlined digit by 2: 1•2 + 0•2 + 0•2 + 0•2 + 0•2 + 6•2 + 0•2 + 4•2 = 2 + 0 + 0 + 0 + 0 + 12 + 0 + 8 = 20.
3. Add the sum to the sum of the digits not multiplied by 2: 20 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20.
4. The last digit in the sum is 0, making David’s card valid.

## Implementation Details

The program is written in C and resides in the `credit` directory. It prompts the user for a credit card number, performs the necessary checks, and outputs whether it is a valid American Express, MasterCard, Visa, or invalid card number.

### Usage

1. Compile the code using a C compiler.
2. Run the executable.
3. Enter the credit card number when prompted.

### Example

```bash
$ ./credit
Number: 4003600000000014
VISA
