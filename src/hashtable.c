#include <stdlib.h>
#include "hashtable.h"
#include <string.h>

link *create_link(char *word, link *next) {
  link *lnk = malloc(sizeof(link));
  lnk->word = malloc(strlen(word)+1);
  strcpy(lnk->word, word);
  lnk->next = next;
  return lnk;
}

void free_link(link *lnk) {
  if(lnk == NULL) return;
  free_link(lnk->next);
  free(lnk->word);
  free(lnk);
}

link *insert_link(link *lnk, char *word) {
  return create_link(word, lnk);
}

table *create_table(int M) {
  table *t = malloc(sizeof(table));
  t->buckets = malloc(M * sizeof(link *));
  for (int i = 0; i < M; i++) {
    t->buckets[i] = NULL;
  }
  t->M = M;
  t->size = 0;
  return t;
}

unsigned hash_str(char *str) {
  unsigned h = 0;
  int i;
  for(i = 0; str[i] != '\0'; i++) 
      h = 31 * h + str[i];
  return h;
}

void add_word(table *t, char *word) {
  int h = hash_str(word) % t->M;
  t->buckets[h] = insert_link(t->buckets[h], word);
  t->size++;
}

void free_table(table *t) {
  for (int i = 0; i < t->M; i++) {
    free_link(t->buckets[i]);
  }
  free(t->buckets);
  free(t);
}
