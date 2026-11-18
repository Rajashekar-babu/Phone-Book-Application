#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

static void read_edit_line(const char *prompt, char *buffer, size_t size)
{
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    size_t length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

static int read_edit_count(const char *prompt, int maximum, int *result)
{
    char line[32];
    char *end;
    long value;

    read_edit_line(prompt, line, sizeof(line));
    value = strtol(line, &end, 10);

    if (line[0] == '\0' || *end != '\0' || value < 0 || value > maximum)
        return 0;

    *result = (int)value;
    return 1;
}

void edit_contact(Contact *head)
{
    Contact *current = head;
    char name[MAX_NAME];
    char new_name[MAX_NAME];
    char choice;
    int count;

    printf("Enter contact name to edit: ");
    if (scanf(" %49[^\n]", name) != 1)
    {
        printf("Invalid name.\n");
        return;
    }

    /* Consume newline left by scanf before using fgets(). */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    while (current != NULL && strcmp(current->name, name) != 0)
        current = current->next;

    if (current == NULL)
    {
        printf("Contact not found.\n");
        return;
    }

    printf("\n1. Edit name\n");
    printf("2. Replace phone numbers\n");
    printf("3. Replace email addresses\n");
    printf("4. Edit address\n");
    printf("Enter your choice: ");

    if (scanf(" %c", &choice) != 1)
        return;

    switch (choice)
    {
        case '1':
        {
            Contact *other;

            read_edit_line("Enter new name: ", new_name, sizeof(new_name));
            if (new_name[0] == '\0')
            {
                printf("Name cannot be empty.\n");
                return;
            }

            for (other = head; other != NULL; other = other->next)
            {
                if (other != current &&
                    strcmp(other->name, new_name) == 0)
                {
                    printf("Another contact already uses that name.\n");
                    return;
                }
            }

            strcpy(current->name, new_name);
            break;
        }

        case '2':
            if (!read_edit_count("Number of phone numbers (0-5): ",
                                 MAX_NUMBERS, &count))
            {
                printf("Invalid count. No changes made.\n");
                return;
            }

            current->phone_count = count;
            for (int i = 0; i < count; ++i)
            {
                char prompt[64];
                snprintf(prompt, sizeof(prompt), "Enter phone number %d: ", i + 1);
                read_edit_line(prompt, current->phone[i],
                               sizeof(current->phone[i]));
            }
            break;

        case '3':
            if (!read_edit_count("Number of email addresses (0-5): ",
                                 MAX_EMAILS, &count))
            {
                printf("Invalid count. No changes made.\n");
                return;
            }

            current->email_count = count;
            for (int i = 0; i < count; ++i)
            {
                char prompt[64];
                snprintf(prompt, sizeof(prompt), "Enter email address %d: ", i + 1);
                read_edit_line(prompt, current->email[i],
                               sizeof(current->email[i]));
            }
            break;

        case '4':
            read_edit_line("Enter new address: ", current->address,
                           sizeof(current->address));
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Contact updated successfully. Select S or Q to save it.\n");
}
