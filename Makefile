CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRCS = src/main.c src/user.c src/usage.c src/analysis.c src/suggestions.c src/file_handler.c
OBJ = $(SRCS:.c=.o)
TARGET = addictionAnalyzer

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)
