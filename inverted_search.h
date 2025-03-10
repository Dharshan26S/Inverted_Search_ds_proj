#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define EMPTYLIST -3

#define FILE_DB "database_files.txt"
#define SIZE 27
#define NAMELENGTH 20

//inverted table

typedef struct file_table
{
	char f_name[NAMELENGTH];
	int word_Count;
	struct file_table *link;
}file;

typedef struct word_data
{
	char word[NAMELENGTH];
	struct word_data *link;
	file *filetable;
	int f_count;
}word;

typedef struct database
{
	int index;
	word *link;
}hash_table;

typedef struct node
{
	char filename[100];
	struct node *link;
}Slist;

extern int updatedone;  // Declare external variable

int validate_file(int argc, char *argv[], Slist **head);
int insert_at_last(Slist **head, char *data);
void print_list(Slist *head);
int is_file_in_database(const char *filename);
void save_filenames_to_database(Slist *head);
int is_file_empty(const char *filename);

void initialize_hashtable(hash_table *htable);
int create_database(Slist *head, hash_table *htable);
int display(hash_table *arr);
int search_word(hash_table *arr, char *search_key);
int save_database(hash_table *arr, const char *filename);
int update_database_from_file(hash_table *htable, const char *filename);
int search_file(hash_table *arr, char *search_keys[], int word_count);
#endif // INVERTED_INDEX_