# Phone Book Application in C

A menu-driven console Phone Book application developed in C using a **Singly Linked List**, dynamic memory allocation, modular programming, and text-file handling.

## Features

- Create a contact with a name, multiple phone numbers, multiple email addresses, and an address.
- Display all contacts.
- Search for a contact by name.
- Edit a contact's name, phone numbers, email addresses, or address.
- Delete a contact by name.
- Save all contacts to `contacts.txt`.
- Automatically load previously saved contacts when the application starts.
- Reject duplicate contact names.

## Technologies

- Language: C (C99)
- Data structure: Singly Linked List
- Memory management: `calloc()` and `free()`
- File handling: `fopen()`, `fprintf()`, `fgets()`, and `fclose()`
- Build tool: GNU Make
- Compiler: GCC

## Project structure

```text
PHONE_BOOK/
├── main.c
├── contact.h
├── create_contact.c
├── display_contact.c
├── search_contact.c
├── delete_contact.c
├── edit_contact.c
├── save_contact.c
├── sync_file.c
├── Makefile
├── README.md
└── .gitignore
```

## Requirements

Install GCC and Make. On Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential
```

## Compile

Run these commands from the project directory:

```bash
make
```

## Execute

```bash
./phonebook
```

Or compile and run in one step:

```bash
make run
```

## Menu options

| Option | Operation |
|---|---|
| C | Create a contact |
| P | Print all contacts |
| D | Delete a contact |
| F | Find a contact |
| E | Edit a contact |
| S | Save contacts |
| Q | Save and quit |

## Data storage

Contacts are stored in the human-readable text file `contacts.txt` in the directory from which the application is run.

- Select `S` to save the current linked list.
- Select `Q` to save and exit.
- On the next launch, the application loads the saved contacts automatically.

The file uses labelled records with a `PHONEBOOK_V1` header. The program saves contact fields, not in-memory linked-list pointers.

Example record:

```text
PHONEBOOK_V1
BEGIN_CONTACT
NAME:Raja
PHONE_COUNT:2
PHONE:9876543210
PHONE:9123456780
EMAIL_COUNT:1
EMAIL:raja@example.com
ADDRESS:Vijayawada
END_CONTACT
END_PHONEBOOK
```

## Limits

- Maximum name length: 49 characters
- Maximum phone numbers per contact: 5
- Maximum email addresses per contact: 5
- Maximum address length: 119 characters

Names, phone numbers, email addresses, and addresses should be entered on one line each.

## Clean build files

```bash
make clean
```

This removes object files and the executable. It does **not** delete `contacts.txt`.

## Notes

This is an educational console project. The text file is not encrypted, so do not store sensitive personal information in it.
