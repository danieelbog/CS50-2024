# Specification

## Design and Implementation

Design and implement a program, `readability`, that computes the Coleman-Liau index of text.

Implement your program in a file called `readability.c` in a directory called `readability`.

## User Input

Your program must prompt the user for a string of text using `get_string`.

## Text Analysis

Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z. Any sequence of characters separated by spaces should count as a word, and any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.

## Output

Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.

-   If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number.
-   If the index number is less than 1, your program should output "Before Grade 1".

## Coleman-Liau Formula

Now it’s time to put all the pieces together! Recall that the Coleman-Liau index is computed using the formula:

\[ \text{index} = 0.0588 \times L - 0.296 \times S - 15.8 \]

where \( L \) is the average number of letters per 100 words in the text, and \( S \) is the average number of sentences per 100 words in the text.

Modify `main` in `readability.c` so that instead of outputting the number of letters, words, and sentences, it instead outputs (only) the grade level as defined by the Coleman-Liau index (e.g., "Grade 2" or "Grade 8" or the like). Be sure to round the resulting index number to the nearest integer!
