/***************************************************************************************************************************************************
*Author		    :Dharshan S.
*Date		    :27/2/25
*File		    :common.c
*Title		    :Helper Functions
*Description	:These functions help the process of project
****************************************************************************************************************************************************/

#include "inverted_search.h"

void initialize_hashtable(hash_table *htable)
{
    for (int i = 0; i < SIZE; i++)
    {
        htable[i].index = i;
        htable[i].link = NULL;
    }
}

int validate_file(int argc, char *argv[], Slist **head)
{
    for (int i = 1; i < argc; i++)
    {
        int flag = 0;
        if (strstr(argv[i], ".") == NULL)
        {
            fprintf(stderr, "Error: %s Invalid File name '.' should be there\n", argv[i]);
            flag = 1;
            continue;
        }

        if (strcmp(strstr(argv[i], "."), ".txt") != 0)
        {
            fprintf(stderr, "Error: %s Invalid File name '.txt extension needed\n", argv[i]);
            flag = 1;
            continue;
        }
        
        FILE *fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            fprintf(stderr, "Error: %s File doesn't exist\n", argv[i]);
            flag = 1;
            continue;
        }

        fseek(fptr, 0, SEEK_END);
        if (ftell(fptr) == 0)
        {
            fprintf(stderr, "Error: %s File empty\n", argv[i]);
            flag = 1;
            continue;
        }
        fclose(fptr);

        Slist *temp = *head;
        while (temp)
        {
            if (strcmp(temp->filename, argv[i]) == 0)
            {
                fprintf(stderr, "Error: %s File name already added\n", argv[i]);
                flag = 1;
                break;
            }
            temp = temp->link;
        }

        // Check if file is already in the database
        if (is_file_in_database(argv[i]))
        {
            fprintf(stderr, "%s is already stored in the database. Skipping...\n", argv[i]);
            continue;
        }
        
        if (!flag)
        {
            insert_at_last(head, argv[i]);
        }
    }
	print_list(*head);
    return (*head == NULL) ? 1 : 0;
}

int insert_at_last(Slist **head, char *data)
{
	/* create new node */
	Slist *new = malloc(sizeof(Slist));
	if (!new)
	{
		return FAILURE;
	}
	/* if new node created, update data + link */
	strcpy(new->filename,data);
	new->link = NULL;

	/* If list is empty */
	if (*head == NULL)
	{
		/* add new node to first position */
		*head = new;
		return SUCCESS;
	}

	/* else */
	/* temp points to first node */
	Slist *temp = *head;

	/* traverse to next node check next node is present or not */
	while (temp->link != NULL)
	{
		temp = temp->link;
	}

	/* establish the link between last and new node*/
	temp->link = new;

	return SUCCESS;
}

void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head)		
	    {
		    printf("%s -> ", head -> filename);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}

// Check if a file is already in the database
int is_file_in_database(const char *filename)
{
    FILE *db = fopen(FILE_DB, "r");
    if (!db)
    {
        printf("Database file not found, assuming no files stored yet.\n");
        return 0; // If file doesn't exist, assume filename is not stored
    }

    char stored_filename[256];
    while (fgets(stored_filename, sizeof(stored_filename), db))
    {
        stored_filename[strcspn(stored_filename, "\n")] = 0; // Remove newline
        if (strcmp(stored_filename, filename) == 0)
        {
            fclose(db);
            return 1; // File found
        }
    }

    fclose(db);
    return 0; // File not found
}

// Function to add filenames to the database file (only when "Save Database" is selected)
void save_filenames_to_database(Slist *head)
{
    FILE *db = fopen(FILE_DB, "a");
    if (!db)
    {
        perror("Error opening database file");
        return;
    }

    Slist *temp = head;
    while (temp)
    {
        if (!is_file_in_database(temp->filename)) // Avoid duplicate entries
        {
            fprintf(db, "%s\n", temp->filename);
        }
        temp = temp->link;
    }

    fclose(db);
    printf("Database filenames saved successfully!\n");
}

// Function to check if a file is empty
int is_file_empty(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 1; // If file does not exist, consider it empty

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    
    return size == 0;
}
