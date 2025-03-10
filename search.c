/***************************************************************************************************************************************************
*Author         :Dharshan S.
*Date           :27/2/25
*File           :search.c
*Title          :To search the words.
*Description    :Each word is now used to search in the linkedlist. The word has to be compared with
		        :each word in the linked list. When found, the file details can be retrieved. Since the
		        :linkedlist is in sorted order, the complexity of searching the word in the complete list
		        :can be avoided. While string comparison, if the word in linkedlist is greater than the
		        :word to be search, it shows the word doesnt exists in the list,
****************************************************************************************************************************************************/
#include "inverted_search.h"

int search_word(hash_table *arr, char *search_key)
{
    // Get the index based on the first character
    // Get index based on first character
    int index = 0;
    if (search_key[0] >= 'a' && search_key[0] <= 'z')
    {
        index = search_key[0] - 'a';
    }
    else if (search_key[0] >= 'A' && search_key[0] <= 'Z')
    {
        index = search_key[0] - 'A';
    }
    else
    {
        index = 26;
    }

    if (index < 0 || index >= SIZE)
    {
        printf("Invalid word!\n");
        return FAILURE;
    }

    word *word_temp_ptr = arr[index].link;

    // Traverse the linked list at the given index
    while (word_temp_ptr)
    {
        if (strcmp(word_temp_ptr->word, search_key) == 0)
        {
            file *file_temp_ptr = word_temp_ptr->filetable;

            // Print word and its occurrences in files
			printf("\nWord %s is present in %d file/files\n", word_temp_ptr->word, word_temp_ptr->f_count);
                
            if (file_temp_ptr)
            {
                printf("In %s word is present %d times\n", file_temp_ptr->f_name, file_temp_ptr->word_Count);
                file_temp_ptr = file_temp_ptr->link;

                while (file_temp_ptr)
                {
                    printf("In %s word is present %d times\n", file_temp_ptr->f_name, file_temp_ptr->word_Count);
                    file_temp_ptr = file_temp_ptr->link;
                }
            }
            else
            {
                printf(" %-22s |   %-4s  |\n", "-", "-");
            }

            return SUCCESS;
        }
        word_temp_ptr = word_temp_ptr->link;
    }

    // If word is not found
    printf("\nWord \"%s\" not found in the database.\n", search_key);
	return FAILURE;
}


