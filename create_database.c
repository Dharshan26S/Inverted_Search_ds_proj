/***************************************************************************************************************************************************
*Author         :DHARSHAN S.
*Date           :27/2/25
*File           :create_database.c
*Title          :To create the database
*Description    :The list of the files can be provided by storing all the file names in another file, FileList the names of the files which 
		        :are to be documented are provided by this file. When a file is added or removed, FileList is changed accordingly.
		        :So read the file names and start indexing.
****************************************************************************************************************************************************/
#include "inverted_search.h"


int create_database(Slist *head, hash_table *htable)
{
	// Pointer to traverse the linked list
    Slist *temp = head;
    while (temp)
    {
		// Open file for reading
        FILE *fp = fopen(temp->filename, "r");
        if (!fp)
        {
            perror("Error opening file");
            temp = temp->link;
            continue;
        }
        
		// Buffer to store words from the file
        char word_buffer[NAMELENGTH];
        while (fscanf(fp, "%s", word_buffer) != EOF)
        {
			// Get index based on first character
			int index = 0;
            if(word_buffer[0] >= 'a' && word_buffer[0] <='z')
			{
				index = word_buffer[0] - 'a';
			}
			else if(word_buffer[0] >= 'A' && word_buffer[0] <='Z')
			{
				index = word_buffer[0] - 'A';
			}
			else{
				index = 26;
			}
            if (index < 0 || index >= SIZE)
                continue;
            
			// Pointer to traverse the word list
            word *wordptr = htable[index].link;
            word *prev_wordptr = NULL;

			// Compare the word and check if already present
            while (wordptr && strcmp(wordptr->word, word_buffer) != 0)
            {
                prev_wordptr = wordptr;
                wordptr = wordptr->link;
            }
            
			// If word not present
            if (!wordptr)
            {
				// Allocate memory for new word node
                wordptr = (word *)malloc(sizeof(word));
                if (!wordptr)
                {
                    perror("Memory allocation failed");
                    fclose(fp);
                    return FAILURE;
                }
                strcpy(wordptr->word, word_buffer);
                wordptr->filetable = NULL;
                wordptr->f_count = 0;
                wordptr->link = NULL;
                
                if (prev_wordptr)
                    prev_wordptr->link = wordptr;     // Add word node to the list
                else
                    htable[index].link = wordptr;     // Insert at head
			}

			// File node handling
			file *sub_fileptr = wordptr->filetable;
			file *fprev_fileptr = NULL;

			// Check if already the file name exist
			while (sub_fileptr && strcmp(sub_fileptr->f_name, temp->filename) != 0)
			{
				fprev_fileptr = sub_fileptr;
				sub_fileptr = sub_fileptr->link;
			}

			// if new file is creating
			if (!sub_fileptr)
			{
				// Allocate memory for new file node
				sub_fileptr = (file *)malloc(sizeof(file));
				if (!sub_fileptr)
				{
					perror("Memory allocation failed");
					fclose(fp);
					return FAILURE;
				}
				strcpy(sub_fileptr->f_name, temp->filename);
				sub_fileptr->word_Count = 1;
				sub_fileptr->link = NULL;

				if (fprev_fileptr)
					fprev_fileptr->link = sub_fileptr; // Add file node to the list
				else
					wordptr->filetable = sub_fileptr; // Insert at head

				wordptr->f_count++; // Increment file count
			}
			else
			{
				// if already the file added to the word, increment wordcount
				sub_fileptr->word_Count++;
			}
		}
        
        fclose(fp);
        temp = temp->link;
    }

	return SUCCESS;
}