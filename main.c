/***************************************************************************************************************************************************
*Author		    :Dharshan S.
*Date		    :27/2/25
*File		    :main.c
*Title		    :Driver function
*Description	:This function acts like the driver function for the project inverted search
****************************************************************************************************************************************************/
#include "inverted_search.h"

int updatedone = 0;

int main(int argc, char *argv[])
{
	/* Define the main function here */
	if (argc < 2)
    {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    
    Slist *head = NULL;
    if (validate_file(argc, argv, &head))
    {
		printf("Error: None of the file succeeded in validation!!\n");
        return 1;
    }

	hash_table htable[SIZE];
    initialize_hashtable(htable);

    int operation;
	char option;
    int creatdone = 0;
	char word[20];
    char update_file_name[256];

    do
	{
		/* Display the menu */
		printf("\n1. Create DATABASE\n2. Display\n3. Update DATABASE\n4. Search_Word\n5. Search_File\n6. Save DATABASE\n\n");
		printf("Enter the option :  ");
		scanf("%d",&operation);
		/* Jump to the option entered by the user */
		switch (operation)
		{
			case 1:
                if (creatdone == 0){
                    if (create_database(head, htable) == SUCCESS)
                    {
                        creatdone = 1;
                        printf("\nDatebase successfully created!!\n");
                    }
                }else{
                    printf("Error: Only one create allowed per execution!!\n");
                }
                break;
			case 2:
                display(htable);
				break;
			case 3:
                // Load saved database before processing new files
                if (creatdone == 0 && updatedone == 0)
                {
                    while (getchar() != '\n')
                        ; // Consume leftover newline
                    // Get filename from user and validate
                    while (1)
                    {
                        printf("Enter the filename to Update the database (.txt only): ");
                        fgets(update_file_name, sizeof(update_file_name), stdin);
                        update_file_name[strcspn(update_file_name, "\n")] = 0; // Remove newline

                        if ((strstr(update_file_name, ".txt") && strcmp(strstr(update_file_name, ".txt"), ".txt") == 0))
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid filename! Please enter a valid .txt filename.\n");
                        }
                    }
                    if (update_database_from_file(htable, update_file_name))
                    {
                        printf("Database loaded successfully from file.\n");
                        updatedone = 1;
                    }
                }else{
                    if(creatdone == 1){
                        printf("Error: Update after create is not allowed!!\n");
                    }else if(updatedone == 1){
                        printf("Error: Already Updated!!\n");
                    }
                }
                break;
			case 4:
				printf("Enter the word you want to search: ");
				scanf("%s",word);
				if(search_word(htable,word) == FAILURE){
                    printf("Search Option Failed!!\n");
                }
				break;
            case 5:
                // Clear input buffer before using fgets
                while (getchar() != '\n');  // Consume leftover newline
                // Taking multiple words from user
                char input[256];
                printf("Enter words to search (space-separated): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove newline

                char *words[50];
                int count = 0;
                char *token = strtok(input, " ");
                while (token)
                {
                    words[count++] = token;
                    token = strtok(NULL, " ");
                }

                // Search for words
                search_file(htable, words, count);
                break;
            case 6:

                char file_name[256];
                while (getchar() != '\n');  // Consume leftover newline
                // Get filename from user and validate
                while (1)
                {
                    printf("Enter the filename to save the database (.txt only): ");
                    fgets(file_name, sizeof(file_name), stdin);
                    file_name[strcspn(file_name, "\n")] = 0; // Remove newline

                    if ((strstr(file_name, ".txt") && strcmp(strstr(file_name, ".txt"), ".txt") == 0))
                    {
                        break;
                    }
                    else
                    {
                        printf("Invalid filename! Please enter a valid .txt filename.\n");
                    }
                }

                if(updatedone){
                    if (strcmp(update_file_name, file_name) == 0)
                    {
                        printf("Cannot save to the same file used for updating! Choose a different filename.\n");
                        break;
                    }

                }
                // Save the database to a file
                if (save_database(htable, file_name))
                {
                    printf("Database saved successfully.\n");
                    save_filenames_to_database(head);
                }
                break;
			default:
			printf("Enter proper choice\n");
			break;		
		}
		
		printf("\nDo you Want to continue? Press [yY | nN]: ");
		scanf("\n%c", &option);
				
	}while (option == 'y' || option == 'Y');
}
