#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to trim spaces and tabs from the beginning and end of a string
char *trim_whitespace(const char *str)
{
    char *end;
    size_t len;

    // Check for NULL input
    if (!str)
        return NULL;

    // Find the first non-whitespace character
    while (isspace((unsigned char)*str))
        str++;

    // If the string is all spaces, return an empty string
    if (*str == '\0')
        return strdup("");

    // Find the last non-whitespace character
    end = (char *)str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Calculate the trimmed length and allocate memory for the new string
    len = end - str + 1;
    char *trimmed = (char *)malloc(len + 1);
    if (!trimmed)
        return NULL;

    // Copy the trimmed part into the new string and add the null terminator
    strncpy(trimmed, str, len);
    trimmed[len] = '\0';

    return trimmed;
}

int main()
{
    const char *test_strings[] = {
        "\t  Hello, World!  \t",
        "  No leading or trailing spaces  ",
        "\t\tAll\tspaces\tand\ttabs\t\t",
        "      ",
        "\t\t",
        NULL // Sentinel value to mark the end of the array
    };

    for (int i = 0; test_strings[i] != NULL; i++)
    {
        char *trimmed = trim_whitespace(test_strings[i]);
        if (trimmed)
        {
            printf("Original: |%s|\n", test_strings[i]);
            printf("Trimmed: |%s|\n", trimmed);
            free(trimmed);
        }
        else
        {
            printf("Memory allocation failed\n");
        }
    }

    return 0;
}
