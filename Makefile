CC = gcc
CFLAGS = -Wall -Wextra -Iunity/src -Iunity/include  -Isrc
LDFLAGS = -static-libgcc -static-libstdc++  # Ensure static linking with MinGW libraries

SRC = src/hello.c  src/main.c
TEST_SRC = tests/hello_test.c
UNITY_SRC = unity/src/unity.c

TARGET = hello_world
TEST_TARGET = test_hello

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_TARGET): $(UNITY_SRC) $(TEST_SRC) src/hello.c
	$(CC) $(CFLAGS) $(UNITY_SRC) $(TEST_SRC) src/hello.c -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all clean
