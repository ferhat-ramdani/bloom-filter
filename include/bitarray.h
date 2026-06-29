#ifndef BITARRAY_H
#define BITARRAY_H

typedef struct _bitarray {
  unsigned char *array; /* Array of bits */
  int m; /* Number of bits */
} bitarray;

/* Return a pointer to an empty bitarray that can store m bits */
bitarray *create_bitarray(int m);

/* Free the memory associated with the bitarray */
void free_bitarray(bitarray *a);

/* Set position pos in the bitarray to 1 */
void set_bitarray(bitarray *a, int pos);

/* Set position pos in the bitarray to 0 */
void reset_bitarray(bitarray *a, int pos);

/* Get the value at position pos in the bitarray */
unsigned char get_bitarray(bitarray* a, int pos);

/* Set all positions in the bitarray to 0 */
void clear_bitarray(bitarray *a);

/* Display the bitarray */
void display_bitarray(bitarray *a);

#endif // BITARRAY_H