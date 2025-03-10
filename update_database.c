/***************************************************************************************************************************************************
*Author         :Dharshan S.
*Date           :27/2/25
*File           :save_database.c
*Title          :To save database.
*Description    :The Database in Database_file is restored back to the memory for further usage 
****************************************************************************************************************************************************/
#include "inverted_search.h"

int update_database_from_file(hash_table *arr, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Error opening file for updating database");
        return 0;
    }

    char line[1024];
    if (fgets(line, sizeof(line), fp) && line[0] != '#')
    {
        printf("Error: Not a valid database file!\n");
        fclose(fp);
        return 0;
    }
    rewind(fp);

    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] != '#')
            continue;

        char *token = strtok(line, "#;");
        if (!token)
            continue;

        int index = atoi(token);
        token = strtok(NULL, ";");
        if (!token)
            continue;

        char data[256];
        strcpy(data, token);
        token = strtok(NULL, ";");
        if (!token)
            continue;

        int file_count = atoi(token);

        word *temp = arr[index].link;
        word *prev = NULL;

        while (temp && strcmp(temp->word, data) != 0)
        {
            prev = temp;
            temp = temp->link;
        }

        if (!temp)
        {
            word *new_word = malloc(sizeof(word));
            strcpy(new_word->word, data);
            new_word->f_count = 0; // Will be updated when adding files
            new_word->filetable = NULL;
            new_word->link = NULL;

            if (!prev)
                arr[index].link = new_word;
            else
                prev->link = new_word;

            temp = new_word;
        }

        int initial_file_count = temp->f_count; // Track before updating
        file *last_file = temp->filetable;
        while (last_file && last_file->link)
            last_file = last_file->link;

        while ((token = strtok(NULL, ";#")))
        {
            char file_name[256];
            strcpy(file_name, token);

            token = strtok(NULL, ";#");
            if (!token)
                continue;

            int word_count = atoi(token);

            file *file_temp_ptr = temp->filetable;
            file *file_prev = NULL;
            int file_found = 0;

            while (file_temp_ptr)
            {
                if (strcmp(file_temp_ptr->f_name, file_name) == 0)
                {
                    file_temp_ptr->word_Count += word_count;
                    file_found = 1;
                    break;
                }
                file_prev = file_temp_ptr;
                file_temp_ptr = file_temp_ptr->link;
            }

            if (!file_found)
            {
                file *new_file = malloc(sizeof(file));
                strcpy(new_file->f_name, file_name);
                new_file->word_Count = word_count;
                new_file->link = NULL;

                if (!file_prev)
                    temp->filetable = new_file;
                else
                    file_prev->link = new_file;

                temp->f_count++; // Increment file count only when a new file is added
            }
        }

        // Ensure f_count is accurate
        if (temp->f_count != initial_file_count)
            temp->f_count = initial_file_count + (temp->f_count - initial_file_count);
    }

    fclose(fp);
    printf("Database successfully updated from %s\n", filename);
    return 1;
}
