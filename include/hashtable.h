#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct _link {
  char *word;
  struct _link *next;
} link;

typedef struct _table {
  link **buckets;
  int M; /* number of buckets */
  int size; /* number of words in table */
} table;

/* Returns an empty hashtable with M buckets */
table *create_table(int M);

/* Adds a word to the hashtable */
void add_word(table *t, char *word);

/* Frees the hashtable*/
void free_table(table *t);




#endif /* HASHTABLE_H */