#ifndef CONTACT_H
#define CONTACT_H

#define MAX_NAME       50
#define MAX_PHONE      16
#define MAX_EMAIL      60
#define MAX_ADDRESS    120
#define MAX_NUMBERS    5
#define MAX_EMAILS     5

typedef struct Contact
{
    char name[MAX_NAME];

    char phone[MAX_NUMBERS][MAX_PHONE];
    int phone_count;

    char email[MAX_EMAILS][MAX_EMAIL];
    int email_count;

    char address[MAX_ADDRESS];

    struct Contact *next;
} Contact;

/* Contact operations */
void create_contact(Contact **head);
void display_contacts(const Contact *head);
void search_contact(const Contact *head);
void delete_contact(Contact **head);
void edit_contact(Contact *head);

/* File operations */
void save_contacts(const Contact *head);
void load_contacts(Contact **head);

/* Memory cleanup */
void free_contacts(Contact **head);

#endif
