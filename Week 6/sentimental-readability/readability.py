def main():
    text = input("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    index = get_r_index(letters, words, sentences)
    print_index(index)


def count_letters(text):
    counter = 0
    for c in text:
        if (c.isalpha()):
            counter += 1
    return counter


def count_words(text):
    counter = 0
    for c in text:
        if (c.isspace()):
            counter += 1
    return counter + 1


def count_sentences(text):
    counter = 0
    for c in text:
        if (c == "!" or c == "." or c == "?"):
            counter += 1
    return counter


def get_r_index(letters, words, sentences):
    L = letters / words * 100
    S = sentences / words * 100
    return round(0.0588 * L - 0.296 * S - 15.8)


def print_index(index):
    if (index >= 16):
        print("Grade 16+")
    elif (index < 1):
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


main()
