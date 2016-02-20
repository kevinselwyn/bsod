NAME    := bsod
FLAGS   := -Wall -Wextra
BIN_DIR := /usr/local/bin

all: build

build: $(NAME).c
	gcc -o $(NAME) $<

test: build
	./$(NAME)

install: $(NAME)
	install -m 0755 $(NAME) $(BIN_DIR)

uninstall:
	rm -f $(BIN_DIR)/$(NAME)

clean:
	rm -f $(NAME)