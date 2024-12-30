#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <CUnit/Basic.h>

// Function prototypes
char *get_next_line(int fd);

// Setup and Teardown functions
int setup(void) {
    // Create test files with different contents
    FILE *file;

    file = fopen("empty.txt", "w");
    fclose(file);

    file = fopen("single_line.txt", "w");
    fprintf(file, "Hello, World!");
    fclose(file);

    file = fopen("multiple_lines.txt", "w");
    fprintf(file, "Line 1\nLine 2\nLine 3\n");
    fclose(file);

    file = fopen("no_newline.txt", "w");
    fprintf(file, "This is a single line without newline");
    fclose(file);

    file = fopen("multiple_newlines.txt", "w");
    fprintf(file, "\n\n\n");
    fclose(file);

    return 0;
}

int teardown(void) {
    // Remove test files
    remove("empty.txt");
    remove("single_line.txt");
    remove("multiple_lines.txt");
    remove("no_newline.txt");
    remove("multiple_newlines.txt");

    return 0;
}

// Test cases
void test_empty_file(void) {
    int fd = open("empty.txt", O_RDONLY);
    char *line = get_next_line(fd);
    CU_ASSERT_PTR_NULL(line);
    close(fd);
}

void test_single_line_file(void) {
    int fd = open("single_line.txt", O_RDONLY);
    char *line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "Hello, World!");
    free(line);
    close(fd);
}

void test_multiple_lines_file(void) {
    int fd = open("multiple_lines.txt", O_RDONLY);
    char *line;

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "Line 1\n");
    free(line);

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "Line 2\n");
    free(line);

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "Line 3\n");
    free(line);

    close(fd);
}

void test_no_newline_file(void) {
    int fd = open("no_newline.txt", O_RDONLY);
    char *line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "This is a single line without newline");
    free(line);
    close(fd);
}

void test_multiple_newlines_file(void) {
    int fd = open("multiple_newlines.txt", O_RDONLY);
    char *line;

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "\n");
    free(line);

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "\n");
    free(line);

    line = get_next_line(fd);
    CU_ASSERT_STRING_EQUAL(line, "\n");
    free(line);

    close(fd);
}

void test_invalid_fd(void) {
    char *line = get_next_line(-1);
    CU_ASSERT_PTR_NULL(line);
}

void test_zero_buffer_size(void) {
    // Assuming BUFFER_SIZE is a macro, we need to redefine it for this test
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 0
    int fd = open("single_line.txt", O_RDONLY);
    char *line = get_next_line(fd);
    CU_ASSERT_PTR_NULL(line);
    close(fd);
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 1024 // Restore original buffer size
}

// Main function to run the tests
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("get_next_line_test_suite", setup, teardown);

    CU_add_test(suite, "test_empty_file", test_empty_file);
    CU_add_test(suite, "test_single_line_file", test_single_line_file);
    CU_add_test(suite, "test_multiple_lines_file", test_multiple_lines_file);
    CU_add_test(suite, "test_no_newline_file", test_no_newline_file);
    CU_add_test(suite, "test_multiple_newlines_file", test_multiple_newlines_file);
    CU_add_test(suite, "test_invalid_fd", test_invalid_fd);
    CU_add_test(suite, "test_zero_buffer_size", test_zero_buffer_size);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}