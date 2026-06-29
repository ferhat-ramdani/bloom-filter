#ifndef SPACE_TIME_H
#define SPACE_TIME_H

/* 
 * Here we define function to compare the time and space complexity
 * of the structures : bloom filter, hash table and search tree.
 */

/* Creates a bloom filter of elts elements, then records the time and space (bytes) taken */
void bloom_filter_complexity(int elts, int *bytes, float *time, char ** words);

/* Creates a hash table of elts elements, then records the time and space (bytes) taken */
void hash_table_complexity(int elts, int *bytes, float *time, char ** words);

/* Creates a search tree of elts elements, then records the time and space (bytes) taken */
void search_tree_complexity(int elts, int *bytes, float *time, char **  words);

/* Generates statistics for different number of elements and stores them in stats folder*/
void generate_stats();

#endif /* SPACE_TIME_H */