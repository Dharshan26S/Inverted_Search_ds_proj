/***************************************************************************************************************************************************
*Author         :Dharshan S.
*Date           :27/2/25
*File           :save_database.c
*Title          :To save database.
*Description    :The Database in memory is stored in a file in a particular format
****************************************************************************************************************************************************/
#include "inverted_search.h"

int save_database(hash_table *arr, const char *filename)
{

    if (!is_file_empty(filename))
    {
        printf("Updating existing database file: %s\n", filename);
        update_database_from_file(arr, filename);
    }
    else{
        printf("Creating new database file: %s\n", filename);
    }
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("Error opening file for saving database");
        return 0;
    }

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
        fprintf(fp, "DATABASE is empty\n");
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i].link != NULL)
        {
            word *word_temp_ptr = arr[i].link;

            while (word_temp_ptr)
            {
                // Write index, word, and file count in the required format
                fprintf(fp, "#%d;%s;%d", i, word_temp_ptr->word, word_temp_ptr->f_count);
                
                file *file_temp_ptr = word_temp_ptr->filetable;
                
                // Write file names and word counts
                while (file_temp_ptr)
                {
                    fprintf(fp, ";%s;%d", file_temp_ptr->f_name, file_temp_ptr->word_Count);
                    file_temp_ptr = file_temp_ptr->link;
                }
                
                fprintf(fp, ";#\n");
                word_temp_ptr = word_temp_ptr->link;
            }
        }
    }

    fclose(fp);
    printf("Database successfully saved to %s\n", filename);
    return 1;
}
