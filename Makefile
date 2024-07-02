CC = gcc
TARGET = numc

all: $(TARGET)
		./$(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET)

clean:
	rm -f $(TARGET)
