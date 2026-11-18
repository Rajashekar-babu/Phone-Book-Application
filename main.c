#include <stdio.h>
#include <stdlib.h>
#include "contact.h"

static void display_menu(void)
{
    printf("\n====================================\n");
    printf("           PHONE BOOK\n");
    printf("====================================\n");
    printf("C : Create a new contact\n");
    printf("P : Print all contacts\n");
    printf("D : Delete a contact\n");
    printf("F : Find a contact\n");
    printf("E : Edit a contact\n");
    printf("S : Save contacts\n");
    printf("Q : Save and quit\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

int main(void)
{
    Contact *head = NULL;
    char choice;

    load_contacts(&head);

    for (;;)
    {
        display_menu();

        if (scanf(" %c", &choice) != 1)
        {
            printf("\nInput ended. Saving contacts...\n");
            save_contacts(head);
            break;
        }

        /* Consume the rest of the menu input line before using fgets(). */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        switch (choice)
        {
            case 'C':
            case 'c':
                create_contact(&head);
                break;

            case 'P':
            case 'p':
                display_contacts(head);
                break;

            case 'D':
            case 'd':
                delete_contact(&head);
                break;

            case 'F':
            case 'f':
                search_contact(head);
                break;

            case 'E':
            case 'e':
                edit_contact(head);
                break;

            case 'S':
            case 's':
                save_contacts(head);
                break;

            case 'Q':
            case 'q':
                save_contacts(head);
                free_contacts(&head);
                printf("Thank you for using Phone Book!\n");
                return 0;

            default:
                printf("Invalid choice. Please select C, P, D, F, E, S or Q.\n");
                break;
        }
    }

    free_contacts(&head);
    return 0;
}
