#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

void delete_contact(Contact **head)
{
    Contact *current = *head;
    Contact *previous = NULL;
    char name[MAX_NAME];

    if (*head == NULL)
    {
        printf("Phone book is empty.\n");
        return;
    }

    printf("Enter contact name to delete: ");
    if (scanf(" %49[^\n]", name) != 1)
    {
        printf("Invalid name.\n");
        return;
    }

    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
                *head = current->next;
            else
                previous->next = current->next;

            free(current);
            printf("Contact deleted successfully.\n");
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Contact not found.\n");
}
