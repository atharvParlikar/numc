CC = clang
TARGET = numc

all: $(TARGET)
		./$(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) -march=armv8-a+simd -O3

clean:
	rm -f $(TARGET)
