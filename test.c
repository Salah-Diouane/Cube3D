#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclure la déclaration de la fonction
// Fonction pour vérifier si une ligne est vide ou ne contient que des espaces
int just_space(const char *str)
{
    while (*str)
    {
        if (*str != ' ')
            return 0;
        str++;
    }
    return 1;
}
// Fonction pour créer une nouvelle carte avec des lignes complétées par des espaces
char **create_new_map(char **map, int longest_length)
{
    // Compter le nombre de lignes dans la carte d'origine
    int rows = 0;
    while (map[rows])
    {
        rows++;
    }

    // Allouer de la mémoire pour la nouvelle carte
    char **new_map = (char **)malloc((rows + 1) * sizeof(char *));
    if (!new_map)
    {
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        // Allouer de la mémoire pour chaque ligne dans la nouvelle carte
        new_map[i] = (char *)malloc((longest_length + 1) * sizeof(char));
        if (!new_map[i])
        {
            for (int k = 0; k < i; k++)
            {
                free(new_map[k]);
            }
            free(new_map);
            return NULL;
        }

        // Copier la ligne actuelle de l'ancienne carte à la nouvelle carte
        strcpy(new_map[i], map[i]);

        // Obtenir la longueur de la ligne copiée
        int len = strlen(new_map[i]);

        // Compléter la ligne avec des espaces si elle est plus courte que la ligne la plus longue
        for (int k = len; k < longest_length; k++)
        {
            new_map[i][k] = ' ';
        }

        // Ajouter le caractère de fin de ligne
        new_map[i][longest_length] = '\0';
    }

    // Marquer la fin de la nouvelle carte
    new_map[rows] = NULL;

    return new_map;
}
char *strip_trailing_whitespace(const char *str)
{
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'))
    {
        len--;
    }
    char *result = (char *)malloc(len + 1);
    if (result)
    {
        strncpy(result, str, len);
        result[len] = '\0';
    }
    return result;
}

int main()
{
    // Exemple de carte avec des lignes de longueurs variées et nouvelles lignes
    char *map[] = {
        "123     \n",
        "    45\n",
        "6789   ",
        "12    ",
        "1234567890\n",
        NULL
    };

    // Allouer un tableau temporaire pour stocker les lignes sans nouvelles lignes
    char **clean_map = (char **)malloc(sizeof(map));
    int rows = 0;

    while (map[rows])
    {
        clean_map[rows] = strip_trailing_whitespace(map[rows]);
        rows++;
    }
    clean_map[rows] = NULL;

    // Trouver la longueur de la ligne la plus longue
    int longest_length = 0;
    for (int i = 0; clean_map[i]; i++)
    {
        int len = strlen(clean_map[i]);
        if (len > longest_length)
        {
            longest_length = len;
        }
    }

    // Créer une nouvelle carte avec des lignes complètes
    char **new_map = create_new_map(clean_map, longest_length);

    // Afficher la nouvelle carte
    if (new_map)
    {
        for (int i = 0; new_map[i]; i++)
        {
            printf("'%s'\n", new_map[i]);
            free(new_map[i]); // Libérer chaque ligne
        }
        free(new_map); // Libérer le tableau de lignes
    }

    // Libérer la mémoire allouée pour les lignes nettoyées
    for (int i = 0; clean_map[i]; i++)
    {
        free(clean_map[i]);
    }
    free(clean_map);

    return 0;
}