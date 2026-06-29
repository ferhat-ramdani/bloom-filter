#ifndef BST_H
#define BST_H

typedef struct _node {
  char *word;              /* data stored : a word        */
  struct _node *left;      /* pointer to the left child   */
  struct _node *right;     /* pointer to the right child  */
} node;

/* Allocate memory for a new node. */
node *create_node(char *word, node *left, node *right);

/* Free the memory allocated for the tree t */
void free_bst(node *t);

/* Inserts word in the tree t */
node *insert_bst(node *t, char *word);

#endif /* BST_H */