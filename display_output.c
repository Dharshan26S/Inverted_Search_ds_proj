/***************************************************************************************************************************************************
*Author         :Dharshan S.
*Date           :27/2/25
*File           :display_output.c
*Title          :To display  the results.
*Description    :When all the words are searched the ouput list is formed. In this the file with max count
		        :(representing maximum word match ) can be selected and displayed. 
****************************************************************************************************************************************************/
#include "inverted_search.h"

int display(hash_table *arr)
{
    int flag = 0;

    // Check if the database is empty
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i].link != NULL)
        {
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        printf("DATABASE is empty\n");
        return 0;
    }

    word *word_temp_ptr;
    file *file_temp_ptr;

    printf("---------------------------------------------------------------------------------\n");
    printf("| Index |       Word         |   File Count  |       File Name        | Count  |\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i].link != NULL)
        {
            word_temp_ptr = arr[i].link;

            while (word_temp_ptr)
            {
                // Print index, word, and file count inside a formatted table
                printf("|  %-3d  | [%-16s] |      %-4d     |", i, word_temp_ptr->word, word_temp_ptr->f_count);
                
                file_temp_ptr = word_temp_ptr->filetable;
                if (file_temp_ptr)
                {
                    printf(" %-22s |  %-4d  |\n", file_temp_ptr->f_name, file_temp_ptr->word_Count);
                    file_temp_ptr = file_temp_ptr->link;

                    while (file_temp_ptr)
                    {
                        printf("|       |                    |               | %-22s |  %-4d  |\n", file_temp_ptr->f_name, file_temp_ptr->word_Count);
                        file_temp_ptr = file_temp_ptr->link;
                    }
                }
                else
                {
                    printf(" %-22s |  %-4s  |\n", "-", "-");
                }

                word_temp_ptr = word_temp_ptr->link;
            }
            printf("----------------------------------------------------------------------------------\n");
        }
    }
    return 1;
}
