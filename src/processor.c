#include <stdio.h>
#include <stdlib.h>
#include "processor.h"


char *generate_word(int size) {
  char *word = (char *)malloc((size+1) * sizeof(char));
  int i = 0;
  for(i = 0; i < size; i++)
    word[i] = 'a' + (rand() % 26);
  word[size] = '\0';
  return word;
}

void free_word(char *word) {
  free(word);
}

void store_words(char *filename, int n) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error: Cannot open file %s\n", filename);
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    int word_length = rand() % 20 + 2;
    char *word = generate_word(word_length);
    fprintf(file, "%s\n", word);
    free_word(word);
  }

  fclose(file);
}

void read_words_from_file(FILE *w_file, filter *f) {
  // Move the file pointer to the beginning of the file
  fseek(w_file, 0, SEEK_SET);

  char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
  while (fscanf(w_file, "%s ", word) != EOF) {
    add_filter(f, word);
  }
  free(word);
}

void read_words_from_filename(char *w_filename, filter *f) {
  FILE *w_file = fopen(w_filename, "r");
  
  if (w_file == NULL) {
    printf("Error: Cannot open file.\n");
    return;
  }

  char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
  while (fscanf(w_file, "%s ", word) != EOF) {
    add_filter(f, word);
  }
  free(word);
}

int search_words(FILE *sw_file, filter *f) {
  // Move the file pointer to the beginning of the file
  fseek(sw_file, 0, SEEK_SET);

  char *word = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
  int false_positives = 0;
  while (fscanf(sw_file, "%s ", word) != EOF) {
    if (is_member_filter(f, word))
      false_positives++;
  }
  free(word);
  return false_positives;
}

double compute_false_positives(int m, int k, FILE *w_file, FILE *sw_file) {
  double rate_sum = 0.0;
  int iterations = 2;
  int i = 0;

  for(i = 0; i < iterations; i++) {
    filter *f = create_filter(m, k);
    read_words_from_file(w_file, f);
    int false_positives = search_words(sw_file, f);
    double rate = (double)false_positives / N;
    rate_sum = rate_sum + rate;
    free_filter(f);
  }

  return (double) (rate_sum / iterations);
}

void print_parameters() {
  printf("Parameters:\n\n");
  printf("max k: \t\t\t\t%d\n", MAX_K);
  printf("max m: \t\t\t\t%d\n", MAX_M);
  printf("number of filter words: \t%d\n", TOKENS);
  printf("number of test words: \t\t%d\n", N);
  printf("\n");
}

void analyse_stats(char *w_filename, char *sw_filename) {
  int m, k, min, i;
  int step = TOKENS / 2;
  double rates[MAX_M][MAX_K]; // Array to store stats
  FILE *w_file = fopen(w_filename, "r");
  FILE *sw_file = fopen(sw_filename, "r");
  
  if (w_file == NULL || sw_file == NULL) {
    printf("Error: Cannot open file.\n");
    return;
  }

  // Print parameters
  print_parameters();

  // Generate N random words and store them in a file
  char *gw_filename = "data/generated.txt";
  store_words(gw_filename, N);

  // Calculate and store average false positive rate for each (m, k) pair
  printf("  m  \tbest rec k\tbest theor k\n");
  for (m = step; m <= MAX_M; m = m + step) {
    min = 1;
    i = m/step - 1;
    for (k = 0; k < MAX_K; k++) {
      rates[i][k] = compute_false_positives(m, k, w_file, sw_file);
      if (rates[i][k] < rates[i][min])
        min = k;
    }
    printf("%5d\t  %2d\t\t   %2.3f\n", m, min, ((float)m / (float)TOKENS) * 0.7);
  }

  // Close files
  fclose(w_file);
  fclose(sw_file);
  store_stats(rates);
}

void store_stats(double rates[][MAX_K]) {
  char filename[100];
  FILE *file;
  
  // Construct file path
  sprintf(filename, "stats/%d_%d.txt", MAX_K, MAX_M);
  
  // Open file for writing
  file = fopen(filename, "w");
  
  if (file == NULL) {
    printf("Error opening file.\n");
    return;
  }
  
  // Write stats to file
  for (int i = 0; i < MAX_M / (TOKENS / 2); i++) {
    for (int j = 0; j < MAX_K; j++) {
      fprintf(file, "%.6lf ", rates[i][j]);
    }
    fprintf(file, "\n");
  }
  
  // Close file
  fclose(file);
}

FILE *read_file(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error: Cannot open file %s\n", filename);
    exit(1);
  }
  return file;
}

void close_file(FILE *file) {
  fclose(file);
}
