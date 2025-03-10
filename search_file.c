/***************************************************************************************************************************************************
*Author         :Dharshan S.
*Date           :27/2/25
*File           :search_file.c
*Title          :To search the file.
*Description    :Each word is now used to search in the linkedlist. The word has to be compared with
		        :each word in the linked list. When found, the file details can be retrieved. Since the
		        :linkedlist is in sorted order, the complexity of searching the word in the complete list
		        :can be avoided. While string comparison, if the word in linkedlist is greater than the
		        :word to be search, it shows the word doesnt exists in the list,
                :File with maximum words will be printed as output
****************************************************************************************************************************************************/

#include "inverted_search.h"

int search_file(hash_table *arr, char *search_keys[], int word_count)
{
    if (word_count <= 0)
    {
        printf("No words provided for search.\n");
        return FAILURE;
    }

    // Structure to track file occurrences
    typedef struct file_result
    {
        char f_name[NAMELENGTH];
        int total_count;
        struct file_result *link;
    } file_result;

    file_result *file_list = NULL;

    printf("\n---------------------- SEARCH RESULTS ----------------------\n");

    // Process each word entered by the user
    for (int i = 0; i < word_count; i++)
    {
        // Get index based on first character
			int index = 0;
            if(search_keys[i][0] >= 'a' && search_keys[i][0] <='z')
			{
				index = search_keys[i][0] - 'a';
			}
			else if(search_keys[i][0] >= 'A' && search_keys[i][0] <='Z')
			{
				index = search_keys[i][0] - 'A';
			}
			else{
				index = 26;
			}

        if (index < 0 || index >= SIZE)
        {
            printf("Invalid word: %s\n", search_keys[i]);
            continue;
        }

        word *word_temp_ptr = arr[index].link;
        int found = 0;  // Flag to check if word exists

        while (word_temp_ptr)
        {
            if (strcmp(word_temp_ptr->word, search_keys[i]) == 0)
            {
                found = 1;
                printf("\nWord: '%s' is present in %d file(s)\n", word_temp_ptr->word, word_temp_ptr->f_count);
                printf("-------------------------------------------------\n");
                printf("| %-20s | %-10s |\n", "File Name", "Occurrences");
                printf("-------------------------------------------------\n");

                file *file_temp_ptr = word_temp_ptr->filetable;
                while (file_temp_ptr)
                {
                    printf("| %-20s | %-10d |\n", file_temp_ptr->f_name, file_temp_ptr->word_Count);

                    // Update file count tracking
                    file_result *fptr = file_list;
                    file_result *prev = NULL;

                    while (fptr && strcmp(fptr->f_name, file_temp_ptr->f_name) != 0)
                    {
                        prev = fptr;
                        fptr = fptr->link;
                    }

                    if (!fptr)
                    {
                        fptr = (file_result *)malloc(sizeof(file_result));
                        if (!fptr)
                        {
                            perror("Memory allocation failed");
                            return FAILURE;
                        }
                        strcpy(fptr->f_name, file_temp_ptr->f_name);
                        fptr->total_count = file_temp_ptr->word_Count;
                        fptr->link = NULL;

                        if (prev)
                            prev->link = fptr;
                        else
                            file_list = fptr;
                    }
                    else
                    {
                        fptr->total_count += file_temp_ptr->word_Count;
                    }

                    file_temp_ptr = file_temp_ptr->link;
                }
                printf("-------------------------------------------------\n");
            }
            word_temp_ptr = word_temp_ptr->link;
        }

        if (!found)
        {
            printf("\nWord \"%s\" not found in the database.\n", search_keys[i]);
        }
    }

    // Find file with max occurrences
    file_result *max_file = file_list;
    file_result *temp = file_list;

    while (temp)
    {
        if (temp->total_count > max_file->total_count)
        {
            max_file = temp;
        }
        temp = temp->link;
    }

    // Print file with maximum occurrences
    if (max_file)
    {
        printf("\n---------------- MAXIMUM OCCURRENCES ----------------\n");
        printf("File with highest word occurrences: %s\n", max_file->f_name);
        printf("Total occurrences of searched words: %d\n", max_file->total_count);
        printf("-----------------------------------------------------\n");
    }
    else
    {
        printf("\nNo matches found for given words.\n");
    }

    // Free allocated memory
    while (file_list)
    {
        file_result *temp = file_list;
        file_list = file_list->link;
        free(temp);
    }

    return SUCCESS;
}
