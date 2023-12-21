# Scrabble Game

## Background

In the game of Scrabble, players create words to score points, and the number of points is the sum of the point values of each letter in the word.

```plaintext
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
1 3 3 2 1 4 2 4 1 8 5 1 3 1 1 3 10 1 1 1 1 4 4 8 4 10

For example, if we wanted to score the word Code, we would note that in general Scrabble rules, the C is worth 3 points, the o is worth 1 point, the d is worth 2 points, and the e is worth 1 point. Summing these, we get that Code is worth 3 + 1 + 2 + 1 = 7 points.

### Implementation Details

Complete the implementation of scrabble.c, such that it determines the winner of a short scrabble-like game, where two players each enter their word, and the higher scoring player wins.

We've stored the point values of each letter of the alphabet in an integer array named POINTS.
We have a prototype for a helper function called compute_score() that takes a string as input and returns an int.
In main(), the program prompts the two players for their words using the get_string() function. These values are stored inside variables named word1 and word2.
In compute_score(), your program should compute, using the POINTS array, and return the score for the string argument. Characters that are not letters should be given zero points, and uppercase and lowercase letters should be given the same point values.
For example, ! is worth 0 points while A and a are both worth 1 point.

Though Scrabble rules normally require that a word be in the dictionary, no need to check for that in this problem!

In main(), your program should print, depending on the players’ scores, Player 1 wins!, Player 2 wins!, or Tie!.
```
