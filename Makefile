CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

BINARY ?= $(notdir $(CURDIR))

build: $(BINARY)

all: build

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(BINARY)
	@mkdir -p $(HOME)/.bin
	@cp -f $(BINARY) $(HOME)/.bin/
	@echo "Installed $(BINARY) to $(HOME)/.bin"

clean:
	rm -f $(OBJS) $(BINARY)

.PHONY: all build clean install

