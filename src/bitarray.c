#include <stdlib.h>
#include <stdio.h>
#include "bitarray.h"

bitarray *create_bitarray(int m) {
  bitarray *a = (bitarray *)malloc(sizeof(bitarray));
  a->array = (unsigned char *)malloc(sizeof(unsigned char) * m);
  a->m = m;
  for(int i = 0; i < m; i++)
    a->array[i] = 0;
  return a;
}

void free_bitarray(bitarray *a) {
  if(a != NULL) {
    if(a->array != NULL) 
      free(a->array);
    free(a);
  }
}

void set_bitarray(bitarray *a, int pos) {
  a->array[pos] = 1;
}

void reset_bitarray(bitarray *a, int pos) {
  a->array[pos] = 0;
}

unsigned char get_bitarray(bitarray *a, int pos) {
  return a->array[pos];
}

void clear_bitarray(bitarray *a) {
  for(int i = 0; i < a->m; i++)
    a->array[i] = 0;
}

void display_bitarray(bitarray *a) {
  if(a == NULL) 
    return;
  for(int i = 0; i < a->m; i++)
    printf("%d", a->array[i]);
  printf("\n");
}
