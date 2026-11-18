CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic
TARGET = phonebook

SRC = main.c \
      create_contact.c \
      display_contact.c \
      search_contact.c \
      delete_contact.c \
      edit_contact.c \
      save_contact.c \
      sync_file.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c contact.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
