#include <stdlib.h>
#include "bst.h"
#include <string.h>

int equal(char *s1, char *s2) {
  return strcmp(s1, s2) == 0;
}

int less(char *s1, char *s2) {
  return strcmp(s1, s2) < 0;
}

node *create_node(char *word, node *left, node *right) {
  node *n = (node *)malloc(sizeof(node));
  n->word = strcpy((char *)malloc(strlen(word) + 1), word);
  n->left = left;
  n->right = right;
  return n;
}

void free_bst(node *t) {
  if(t != NULL) {
    free(t->word);
    free_bst(t->left);
    free_bst(t->right);
    free(t);
  }
}

node *insert_bst(node *t, char *word) {
  if(t == NULL) 
    return create_node(word, NULL, NULL);
  if(less(t->word, word))
    t->right = insert_bst(t->right, word);
  if(less(word, t->word)) 
    t->left = insert_bst(t->left, word);
  return t;
}
