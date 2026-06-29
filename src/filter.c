#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

filter *create_filter(int m, int k) {
  filter *f = (filter *)malloc(sizeof(filter));
  f->weights = (unsigned *)malloc(sizeof(unsigned) * k);
  f->ba = create_bitarray(m);
  f->k = k;
  for(int i = 0; i < k; i++)
    f->weights[i] = (rand() % 253) + 3;
  return f;
}

void free_filter(filter *f) {
  if(f != NULL) {
    if(f->ba != NULL)
      free_bitarray(f->ba);
    if(f->weights != NULL) 
      free(f->weights);
    free(f);
  }
}

void hash(filter *f, char *str, unsigned hashes[]) {
  if(f == NULL || str == NULL || hashes == NULL)
    return;
  int i = 0, j = 0;
  for(i = 0; i < f->k; i++) {
    unsigned h = 0;
    for(j = 0; str[j] != '\0'; j++)
      h = f->weights[i] * h + str[j];
    hashes[i] = h %  f->ba->m;
  }
}

void add_filter(filter *f, char *str) {
  if(f == NULL || str == NULL)
    return;
  int i = 0;
  unsigned hashes[f->k];
  hash(f, str, hashes);
  for(i = 0; i < f->k; i++)
    set_bitarray(f->ba, hashes[i]);
}

int is_member_filter(filter *f, char *str) {
  if(f == NULL || str == NULL)
    return 0;
  int i = 0;
  unsigned hashes[f->k];
  for(i = 0; i < f->k; i++) {
    hash(f, str, hashes);
    if(get_bitarray(f->ba, hashes[i]) == 0)
      return 0;
  }
  return 1;
}

void display_weights(filter *f) {
  if(f == NULL)
    return;
  for(int i = 0; i < f->k; i++)
    printf("%u ", f->weights[i]);
  printf("\n");
}
