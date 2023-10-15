# Word Matching Game

Welcome to the Word Matching Game implemented in C! This program challenges users to guess a randomly selected 5-letter word from a predefined list. Below is an overview of its features:

## Features:

1. **Word Selection:**
   - A random 5-letter word is chosen from the "word_list.txt" file for the user to guess.

2. **Guessing Mechanism:**
   - Users have 6 chances to guess the correct word.
   - Valid guesses are restricted to 5-letter words from the provided list.

3. **Letter Matching:**
   - Reveals any correct letters in a guessed word.

4. **Safeguards:**
   - Safeguards are implemented to ensure correct user input.
   - The program checks for the correct guess or completion of the correct word through other guesses.

5. **Game Statistics:**
   - Displays the number of games won after the user quits the game.
   - Calculates and shows the user's win percentage.

## How to Play:

1. Compile the program:
   ```bash
   gcc -o word_matching_game word_matching_game.c
