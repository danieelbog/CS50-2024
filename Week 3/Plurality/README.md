# Understanding plurality.c

Let's explore `plurality.c` and go through the provided distribution code.

The line `#define MAX 9` is a syntax indicating that `MAX` is a constant (equal to 9) to be used throughout the program. It represents the max number of candidates an election can have.

The file defines a struct named `candidate` with fields: a string `name` for the candidate’s name and an int `votes` for the number of votes.

Now, in the `main` function, find where the program:

-   Sets `candidate_count` (number of candidates).
-   Copies command-line arguments into the `candidates` array.
-   Asks the user for the number of voters.
-   Lets each voter type in a vote, calling the `vote` function for each candidate voted for.
-   Finally, calls the `print_winner` function to print the winner(s) of the election.

Further down, you'll see that the `vote` and `print_winner` functions are left blank, and it's up to you to complete them!

## Specification

Complete the implementation of `plurality.c` to simulate a plurality vote election.

### `vote` function:

-   Takes a single argument, a string called `name` (candidate's name).
-   If `name` matches a candidate's name, update their vote total and return true.
-   If `name` doesn't match any candidate, no vote totals change, and return false.

### `print_winner` function:

-   Print the name of the candidate with the most votes, and then print a newline.
-   If there's a tie, output the names of each winning candidate on separate lines.

Don't modify anything else in `plurality.c` except for the implementations of `vote` and `print_winner` functions.

Happy coding!
