# include "cube.h"

void    ft_free_2d(char **arr)
{
    int     i;

    i = -1;
    if (arr)
    {
        while (arr && arr[++i])
            free(arr[i]);
        free(arr);
    }
}

static size_t   ft_strlen_sp(char const *s, char c)
{
    size_t      l;

    l = 0;
    while (s && s[l] && (s[l] != c))
        l++;
    return (l);
}

static int  ft_count_words(char const *s, char c)
{
    int         nbr;

    nbr = 0;
    while (s && *s)
    {
        if (*s && (*s != c))
        {
            while (*s && (*s != c))
                s++;
            nbr++;
        }
        else if (*s)
            s++;
    }
    return (nbr);
}

static char *ft_take_word(char const *s, char c)
{
    size_t      i;
    size_t      len;
    char        *word;

    i = -1;
    word = NULL;
    len = ft_strlen_sp(s, c);
    if (len)
    {
        word = malloc(sizeof(char) * (len + 1));
        if (!word)
            return (NULL);
        while (len--)
            word[++i] = *s++;
        word[++i] = '\0';
    }
    return (word);
}

char    **ft_split(char const *s, char c)
{
    int         i;
    int         wrds;
    char        **arr;

    i = -1;
    arr = NULL;
    wrds = ft_count_words(s, c);
    if (wrds)
    {
        arr = (char **)malloc(sizeof(char*) * (wrds + 1));
        if (!arr)
            return (NULL);
        while (*s)
        {
            while (*s && (*s == c))
                s++;
            if (*s)
                arr[++i] = ft_take_word(s, c);
            if (!arr[i])
                return (ft_free_2d(arr), NULL);
            s += ft_strlen_sp(arr[i], c);
        }
        arr[++i] = NULL;
    }
    return (arr);
}