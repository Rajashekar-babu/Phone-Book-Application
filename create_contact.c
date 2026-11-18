#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

static void read_line(const char *prompt, char *buffer, size_t size)
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
        /* Discard remaining input if the line exceeded the buffer. */
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
}

static int read_count(const char *prompt, int maximum)
{
    char line[32];
    char *end;
    long value;

    for (;;)
    {
        read_line(prompt, line, sizeof(line));
        value = strtol(line, &end, 10);

        if (line[0] != '\0' && *end == '\0' &&
            value >= 0 && value <= maximum)
            return (int)value;

        printf("Enter a number between 0 and %d.\n", maximum);
    }
}

void create_contact(Contact **head)
{
    Contact *node;
    Contact *current;
    char prompt[80];

    node = calloc(1, sizeof(*node));
    if (node == NULL)
    {
        perror("calloc");
        return;
    }

    read_line("Enter contact name: ", node->name, sizeof(node->name));
    if (node->name[0] == '\0')
    {
        printf("Name cannot be empty. Contact was not created.\n");
        free(node);
        return;
    }

    for (current = *head; current != NULL; current = current->next)
    {
        if (strcmp(current->name, node->name) == 0)
        {
            printf("A contact with that name already exists.\n");
            free(node);
            return;
        }
    }

    node->phone_count = read_count("How many phone numbers (0-5)? ",
                                   MAX_NUMBERS);
    for (int i = 0; i < node->phone_count; ++i)
    {
        snprintf(prompt, sizeof(prompt), "Enter phone number %d: ", i + 1);
        read_line(prompt, node->phone[i], sizeof(node->phone[i]));
    }

    node->email_count = read_count("How many email addresses (0-5)? ",
                                   MAX_EMAILS);
    for (int i = 0; i < node->email_count; ++i)
    {
        snprintf(prompt, sizeof(prompt), "Enter email address %d: ", i + 1);
        read_line(prompt, node->email[i], sizeof(node->email[i]));
    }

    read_line("Enter address: ", node->address, sizeof(node->address));

    node->next = NULL;

    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = node;
    }

    printf("Contact created successfully.\n");
}
