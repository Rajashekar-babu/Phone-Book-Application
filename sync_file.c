#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"

static int read_line(FILE *fp, char *buffer, size_t size)
{
    size_t length;

    if (fgets(buffer, (int)size, fp) == NULL)
        return 0;

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[--length] = '\0';
    }
    else if (!feof(fp))
    {
        /* The line is longer than the buffer; reject it. */
        int ch;
        while ((ch = fgetc(fp)) != '\n' && ch != EOF)
            ;
        return 0;
    }

    if (length > 0 && buffer[length - 1] == '\r')
        buffer[--length] = '\0';

    return 1;
}

static int read_field(FILE *fp, const char *label,
                      char *value, size_t value_size)
{
    char line[256];
    size_t label_length = strlen(label);
    size_t value_length;

    if (!read_line(fp, line, sizeof(line)))
        return 0;

    if (strncmp(line, label, label_length) != 0)
        return 0;

    value_length = strlen(line + label_length);
    if (value_length >= value_size)
        return 0;

    strcpy(value, line + label_length);
    return 1;
}

static int read_count(FILE *fp, const char *label,
                      int *count, int maximum)
{
    char line[64];
    char *end;
    long value;
    size_t label_length = strlen(label);

    if (!read_line(fp, line, sizeof(line)))
        return 0;

    if (strncmp(line, label, label_length) != 0)
        return 0;

    value = strtol(line + label_length, &end, 10);

    if (end == line + label_length || *end != '\0' ||
        value < 0 || value > maximum)
        return 0;

    *count = (int)value;
    return 1;
}

void load_contacts(Contact **head)
{
    FILE *fp;
    Contact *node;
    Contact *tail = NULL;
    char line[256];

    if (*head != NULL)
    {
        printf("Cannot load contacts into a non-empty list.\n");
        return;
    }

    fp = fopen("contacts.txt", "r");
    if (fp == NULL)
    {
        /* This is normal the first time the application is run. */
        printf("No previous contacts.txt file found. Starting a new phone book.\n");
        return;
    }

    if (!read_line(fp, line, sizeof(line)) ||
        strcmp(line, "PHONEBOOK_V1") != 0)
    {
        printf("Invalid contacts.txt format. No contacts loaded.\n");
        fclose(fp);
        return;
    }

    while (read_line(fp, line, sizeof(line)))
    {
        if (line[0] == '\0')
            continue;

        if (strcmp(line, "END_PHONEBOOK") == 0)
            break;

        if (strcmp(line, "BEGIN_CONTACT") != 0)
        {
            printf("Invalid contact record. Loading stopped.\n");
            break;
        }

        node = calloc(1, sizeof(*node));
        if (node == NULL)
        {
            perror("calloc");
            break;
        }

        if (!read_field(fp, "NAME:", node->name, sizeof(node->name)) ||
            node->name[0] == '\0' ||
            !read_count(fp, "PHONE_COUNT:",
                        &node->phone_count, MAX_NUMBERS))
            goto invalid_record;

        for (int i = 0; i < node->phone_count; ++i)
        {
            if (!read_field(fp, "PHONE:", node->phone[i],
                            sizeof(node->phone[i])))
                goto invalid_record;
        }

        if (!read_count(fp, "EMAIL_COUNT:",
                        &node->email_count, MAX_EMAILS))
            goto invalid_record;

        for (int i = 0; i < node->email_count; ++i)
        {
            if (!read_field(fp, "EMAIL:", node->email[i],
                            sizeof(node->email[i])))
                goto invalid_record;
        }

        if (!read_field(fp, "ADDRESS:", node->address,
                        sizeof(node->address)))
            goto invalid_record;

        if (!read_line(fp, line, sizeof(line)) ||
            strcmp(line, "END_CONTACT") != 0)
            goto invalid_record;

        node->next = NULL;

        if (*head == NULL)
            *head = node;
        else
            tail->next = node;

        tail = node;
        continue;

invalid_record:
        printf("Invalid or incomplete contact. Loading stopped.\n");
        free(node);
        break;
    }

    fclose(fp);
    printf("Contact loading completed.\n");
}

void free_contacts(Contact **head)
{
    Contact *current = *head;

    while (current != NULL)
    {
        Contact *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
