#include <stdio.h>
#include <string.h>
#include "contact.h"

void search_contact(const Contact *head)
{
    char name[MAX_NAME];
    const Contact *current = head;

    printf("Enter contact name to search: ");
    if (scanf(" %49[^\n]", name) != 1)
    {
        printf("Invalid name.\n");
        return;
    }

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("\nContact found.\n");
            printf("Name            : %s\n", current->name);

            printf("Phone numbers   :\n");
            if (current->phone_count == 0)
                printf("  (none)\n");
            for (int i = 0; i < current->phone_count; ++i)
                printf("  %d. %s\n", i + 1, current->phone[i]);

            printf("Email addresses :\n");
            if (current->email_count == 0)
                printf("  (none)\n");
            for (int i = 0; i < current->email_count; ++i)
                printf("  %d. %s\n", i + 1, current->email[i]);

            printf("Address         : %s\n", current->address);
            return;
        }

        current = current->next;
    }

    printf("Contact not found.\n");
}
