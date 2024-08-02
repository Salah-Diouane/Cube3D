#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int is_texture_or_color_line(char *line)
{
    if (strncmp(line, "NO ", 2) == 0 || strncmp(line, "SO ", 2) == 0 ||
        strncmp(line, "WE ", 2) == 0 || strncmp(line, "EA ", 2) == 0 ||
        strncmp(line, "F ", 1) == 0 || strncmp(line, "C ", 1) == 0)
    {
        return 1;
    }
    return 0;
}

int is_map_line(char *line)
{
    while (*line)
    {
        if (*line != '1' && *line != '0' && *line != ' '
			&& *line != '\t' && *line != '\n')
        {
            return 0;
        }
        line++;
    }
    return 1;
}

int validate_map_position(char **map)
{
    int i = 0;
    int map_started = 0;

    while (map[i])
    {
        // Skip empty lines
        if (map[i][0] == '\0')
        {
            i++;
            continue;
        }
        // Skip texture and color lines
        if (is_texture_or_color_line(map[i]))
        {
            if (map_started)
                return -1; // Map lines must be contiguous and at the end
        }
        else if (is_map_line(map[i]))
        {
            map_started = 1;
        }
        else if (map_started && !is_map_line(map[i]))
        {
            return -1; // Non-map lines after map started
        }
        i++;
    }
    // Check if map has started
    if (!map_started)
        return -1;  // No map lines found
    return 0; // Map is at the end
}

int main(void)
{
    // Exemple de carte et de textures/couleurs
    char *map[] = {
        "NO ./path_to_the_north_texture",
        "SO ./path_to_the_south_texture",
        "WE ./path_to_the_west_texture",
        "EA ./path_to_the_east_texture",
        "F 220,100,0",
        "C 225,30,0",
        "",
        "11111111111111111111111111",
        "100000000110000000000001",
        "1011000001110000000000001",
        "1001000000000000000000001",
        "111111111011000001110000000000001",
        "100000000011000001110111111111111",
        "11111111111111011100000010001111111111111111111111111111111111",
        "11110111111111011101010010001",
        "1111111111111111110101011100000010001",
        "100000000000000011000000100011111111",
        "100000000000W00011010100100001",
        "110000011101010111110111100011",
        "1111011111101011011110100011",
        "11111111111111111111111111",
        NULL
    };

    int result = validate_map_position(map);

    if (result == 0)
        printf("The map is correctly positioned at the end of the file.\n");
    else
        printf("The map is not correctly positioned.\n");

    return 0;
}
