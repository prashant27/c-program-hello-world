#include "../unity/include/unity.h"
#include <stdio.h>
#include <string.h>
#include "../src/hello.h"
#include <stdlib.h>

#define OUTPUT_BUFFER_SIZE 100

char output_buffer[OUTPUT_BUFFER_SIZE];
FILE* original_stdout;

void setUp(void) {
    // Redirect stdout to a temporary file
    original_stdout = freopen("test_output.txt", "w", stdout);
    if (!original_stdout) {
        perror("freopen");
        exit(EXIT_FAILURE);
    }
}

void tearDown(void) {
    // Restore stdout and close the temporary file
    freopen("CONOUT$", "w", stdout);
}

void test_print_hello(void) {
    // Redirect stdout to buffer
    freopen("test_output.txt", "w", stdout);

    print_hello();

    // Restore stdout
    freopen("CONOUT$", "w", stdout);

    // Open the temporary file to read its content
    FILE* file = fopen("test_output.txt", "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Read the output into the buffer
    fgets(output_buffer, OUTPUT_BUFFER_SIZE, file);
    fclose(file);

    // Test if the output is as expected
    TEST_ASSERT_EQUAL_STRING("Hello, World!\n", output_buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_print_hello);
    return UNITY_END();
}

