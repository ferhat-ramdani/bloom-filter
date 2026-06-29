#include "processor.h"
#include "filter.h"
#include "menu.h"
#include "space_time_tests.h"
#include <stdio.h>

filter *cur_filter = NULL;
int quit = 0;

void print_menu() {
  printf("Menu usage : \n");
  printf("-----Basic commands-----\n");
  printf("\tc <m> <k>:\tCreate filter with parameters m and k\n");
  printf("\ti <entry>:\tInsert <entry> into the current filter\n");
  printf("\tf <entry>:\tFind <entry> in the current filter\n");
  printf("\td:\t\tDisplay the filter\n");

  printf("\n");

  printf("-----Test and File commands-----\n");
  printf("\tg <size>:\tGenerate <size> random words and stores them in words\\generated.txt\n");
  printf("\tv <m> <k> <keys_file> <test_file>:\tVerify existance of entires of <test_file> in a new filter filled with the entries of <keys_file> with parameters <m> and <k> and display false-postive rate\n");
  printf("\tr <filename>:\tRead the file <filename> in the current filter\n");
  printf("\tt:\t\tLaunch tests with various m and k and displays statistics\n");
  printf("\ts:\t\tDisplay space and time comparaisons between bloom filter, hashmap and binary searth tree\n");

  printf("\n");

  printf("-----Help and Quit commands-----\n");
  printf("\th:\tPrint menu\n");
  printf("\tq:\tQuit the menu\n");

}

void read_command() {
  char command;
  int param1, param2;
  scanf(" %c", &command);
  switch(command) {
    case 'g':
      scanf("%d", &param1);
      store_words("data/generated.txt", param1);
      break;
    case 'c':
      scanf("%d %d", &param1, &param2);
      if(cur_filter != NULL)
        free_filter(cur_filter);
      cur_filter = create_filter(param1, param2);
      break;
    case 'r':
      char filename[100];
      scanf("%s", filename);
      read_words_from_filename(filename, cur_filter);
      break;
    case 'v':
      scanf("%d %d", &param1, &param2);
      char filter_tokens[100], test_tokens[100];
      scanf("%s %s", filter_tokens, test_tokens);
      FILE *ft = read_file(filter_tokens);
      FILE *tt = read_file(test_tokens);
      double fp = compute_false_positives(param1, param2, ft, tt);
      printf("False positive rate : %f\n", fp);
      close_file(ft);
      close_file(tt);
      break;
    case 'i':
      char entry[100];
      scanf("%s", entry);
      add_filter(cur_filter, entry);
      break;
    case 'f':
      char search[100];
      scanf("%s", search);
      if(is_member_filter(cur_filter, search))
        printf("Entry maybe in filter\n");
      else
        printf("Entry not in filter\n");
      break;
    case 't':
      analyse_stats("data/1000words.txt", "data/generated.txt");
      break;
    case 's':
      generate_stats();
      break;
    case 'd':
      if(cur_filter == NULL)
        printf("No filter created\n");
      else
        display_bitarray(cur_filter->ba);
      break;
    case 'h':
      print_menu();
      break;
    case 'q':
      quit = 1;
      free_filter(cur_filter);
      break;
    default:
      printf("Unknown command\n");
  }
  printf("\n");
}

void start_menu() {
  print_menu();
  while(!quit) {
    read_command();
  }
}