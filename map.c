#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Fonction pour déterminer la longueur de la plus longue ligne
int find_longest_line_length(char **map)
{
    int longest_length = 0;
    int length;
    int i = 0;

    while (map[i] != NULL)
    {
        length = strlen(map[i]);
        if (length > longest_length)
        {
            longest_length = length;
        }
        i++;
    }
    return longest_length;
}

// Fonction pour vérifier si une ligne contient uniquement des espaces blancs
int just_space(const char *str)
{
    while (*str)
    {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

// Fonction pour créer une nouvelle carte en complétant les lignes plus courtes avec des espaces
char **create_new_map(char **map, int longest_length, int rows)
{
    char **new_map = (char **)malloc((rows + 1) * sizeof(char *));
    if (!new_map)
        return NULL;

    int i = 0, j = 0;
    while (map[i] != NULL)
    {
        if (!just_space(map[i]))
        {
            new_map[j] = (char *)malloc((longest_length + 1) * sizeof(char));
            if (!new_map[j])
            {
                for (int k = 0; k < j; k++)
                {
                    free(new_map[k]);
                }
                free(new_map);
                return NULL;
            }
            strcpy(new_map[j], map[i]);
            int len = strlen(new_map[j]);
            for (int k = len; k < longest_length; k++)
            {
                new_map[j][k] = ' ';
            }
            new_map[j][longest_length] = '\0';
            j++;
        }
        i++;
    }
    new_map[j] = NULL;
    return new_map;
}

// Fonction principale
int main()
{
    char *map[] = {
        "        11111111111111111111111111                 ",
        "        100000000110000000000001",
        "        1011000001110000000000001",
        "        1001000000000000000000001",
        "                               111111111011000001110000000000001",
        "100000000011000001110111111111111",
        "11110111111111011100000010001",
        "11110111111111011101010010001",
        "11000000110101011100000010001",
        "10000000000000001100000010001",
        "100000000000W00011010100100001",
        "110000011101010111110111100011",
        "1111011111101011011110100011",
        "11111111111111111111111111",
        NULL};

    int rows = 0;
    while (map[rows] != NULL)
    {
        rows++;
    }

    int longest_length = find_longest_line_length(map);
    char **new_map = create_new_map(map, longest_length, rows);

    if (new_map)
    {
        printf("New map:\n");
        for (int i = 0; new_map[i] != NULL; i++)
        {
            printf("|%s|\n", new_map[i]);
            free(new_map[i]);
        }
        free(new_map);
    }
    else
    {
        printf("Memory allocation error.\n");
    }

    return 0;
}
