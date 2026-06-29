#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

#define MAX_WORD_LENGTH 100
#define TOKENS 1000 /* number of tokens inside filter */
#define N 10000 /* number of test tokens */
#define MAX_K 40
#define MAX_M (20 * TOKENS)

/* Generates a random word of size size */
char *generate_word(int size);

/* Frees the memory associated with the word */
void free_word(char *word);

/* Stores n random generated words in a file */
void store_words(char *filename, int n);

/* Reads words from a file and puts them in filter */
void read_words_from_file(FILE *w_file, filter *f);

/* Reads words from a filename and puts them in filter */
void read_words_from_filename(char *w_filename, filter *f);

/* Computes false positive rate for given parameters */
double compute_false_positives(int m, int k, FILE *w_file, FILE *sw_file);

/* Analyzes and displays statistics for various parameters */
void analyse_stats(char *w_filename, char *sw_filename);

/* Function to write stats to file */
void store_stats(double rates[][MAX_K]);

/* Open a file in read mode and returns it*/
FILE *read_file(char *filename);

/* Closes a file */
void close_file(FILE *file);

#endif // PROCESSOR_H 