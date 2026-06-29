#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "space_time_tests.h"
#include "filter.h"
#include "processor.h"
#include "hashtable.h"
#include "bst.h"

#define LN2 (0.69314718056)
#define COEF 8

// int space_test_bloom_filter(int bytes) {
//   return (int) (bytes - sizeof(unsigned) * LN2 * COEF - sizeof(int)) / (sizeof(unsigned char) * COEF);
// }

void bloom_filter_complexity(int elts, int *bytes, float *time, char **words) {
  // create filter
  int m = COEF * elts;
  int k = (int) (LN2 * COEF);
  filter *f = create_filter(m, k);

  // generate and add elts words
  int i = 0;
  clock_t start = clock();
  for (i = 0; i < elts; i++) {
    add_filter(f, words[i]);
  }
  clock_t end = clock();

  // record time and space
  *time = (float)(end - start) / CLOCKS_PER_SEC;
  *bytes = sizeof(filter) + sizeof(bitarray) + m * sizeof(unsigned char) + sizeof(unsigned) * k;

  // free filter
  free(f);
}

void hash_table_complexity(int elts, int *bytes, float *time, char **words) {
  // create table
  int m = 2 * elts;
  table *t = create_table(m);

  // insert elts words and record time
  int i;
  clock_t start = clock();
  for (i = 0; i < elts; i++) {
    add_word(t, words[i]);
  }
  clock_t end = clock();

  // record time and space
  *time = (float)(end - start) / CLOCKS_PER_SEC;

  *bytes = sizeof(table) + m * sizeof(link *) + elts * sizeof(link);
  for(i = 0; i < m; i++) {
    link *lnk = t->buckets[i];
    while(lnk != NULL) {
      *bytes += strlen(lnk->word) + 1;
      lnk = lnk->next;
    }
  }

  // free table
  free_table(t);
}

void search_tree_complexity(int elts, int *bytes, float *time, char **words) {
  // create tree
  node *t = NULL;

  // insert elts words and record time
  int i;
  clock_t start = clock();
  for (i = 0; i < elts; i++) {
    t = insert_bst(t, words[i]);
  }
  clock_t end = clock();

  // record time and space
  *time = (float)(end - start) / CLOCKS_PER_SEC;
  *bytes = elts * sizeof(node);
  for(i = 0; i < elts; i++) {
    *bytes += strlen(words[i]) + 1;
  }

  // free tree
  free_bst(t);
}

void generate_stats() {
  int step = 10000;
  int start = step;
  int i;
  printf("Generating statistics...\n");
  printf("%-18s%-28s%-10s\t\t%-10s\n", "Nb elts", "Hashmap", "Bloom Filter", "BST");
  for(i = 0; i < 20; i++) {
    int elts = start + step * i;
    int bytes;
    float time;

    printf("%-10d", elts);

    // generates elts words
    char **words = malloc(elts * sizeof(char *));
    int j;
    for (j = 0; j < elts; j++) {
      int size = rand() % MAX_WORD_LENGTH + 1;
      words[j] = generate_word(size);
    }

    // test space and time complexity of bloom filter
    bloom_filter_complexity(elts, &bytes, &time, words);
    printf("| %-9d o %-5.2f s |\t", bytes, time);

    // test space and time complexity of hash table
    hash_table_complexity(elts, &bytes, &time, words);
    printf("| %-9d o %-5.2f s |\t", bytes, time);

    // test space and time complexity of search tree
    search_tree_complexity(elts, &bytes, &time, words);
    printf("|%-9d o %-5.2f s |\n", bytes, time);

    // free words
    for (j = 0; j < elts; j++) {
      free_word(words[j]);
    }
    free(words);
  }
}
