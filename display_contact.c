#include <stdio.h>
#include "contact.h"

void display_contacts(const Contact *head)
{
    const Contact *current = head;
    int contact_number = 1;

    if (head == NULL)
    {
        printf("Phone book is empty.\n");
        return;
    }

    while (current != NULL)
    {
        printf("\n====================================\n");
        printf("Contact %d\n", contact_number++);
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
        current = current->next;
    }

    printf("====================================\n");
}
