#include <stdio.h>
#include "contact.h"

void save_contacts(const Contact *head)
{
    FILE *fp;
    const Contact *current = head;

    fp = fopen("contacts.txt", "w");
    if (fp == NULL)
    {
        perror("Unable to open contacts.txt");
        return;
    }

    fprintf(fp, "PHONEBOOK_V1\n");

    while (current != NULL)
    {
        fprintf(fp, "BEGIN_CONTACT\n");
        fprintf(fp, "NAME:%s\n", current->name);
        fprintf(fp, "PHONE_COUNT:%d\n", current->phone_count);

        for (int i = 0; i < current->phone_count; ++i)
            fprintf(fp, "PHONE:%s\n", current->phone[i]);

        fprintf(fp, "EMAIL_COUNT:%d\n", current->email_count);

        for (int i = 0; i < current->email_count; ++i)
            fprintf(fp, "EMAIL:%s\n", current->email[i]);

        fprintf(fp, "ADDRESS:%s\n", current->address);
        fprintf(fp, "END_CONTACT\n");

        current = current->next;
    }

    fprintf(fp, "END_PHONEBOOK\n");

    if (fclose(fp) == EOF)
    {
        perror("Error closing contacts.txt");
        return;
    }

    printf("Contacts saved successfully to contacts.txt.\n");
}
