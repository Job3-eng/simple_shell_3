#include "shell.h"

/**
 * **strtow - spliting string to words
 * @str: input str
 * @d: delim str
 * Return:  ptr to arrays
 */

char **strtow(char *str, char *d)
{
	int a, b, l, m, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			n_words++;

	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n_words; b++)
	{
		while (is_delim(str[a], d))
			a++;
		l = 0;
		while (!is_delim(str[a + l], d) && str[a + l])
			l++;
		s[b] = malloc((l + 1) * sizeof(char));
		if (!s[b])
		{
			for (l = 0; l < b; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splitting strings to words
 * @str: input str
 * @d: delimter
 * Return: ptr to an array
 */
char **strtow2(char *str, char d)
{
	int a, b, l, m, n_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			n_words++;
	if (n_words == 0)
		return (NULL);
	s = malloc((1 + n_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < n_words; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		l = 0;
		while (str[a + l] != d && str[a + l] && str[a + l] != d)
			l++;
		s[b] = malloc((l + 1) * sizeof(char));
		if (!s[b])
		{
			for (l = 0; l < b; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			s[b][m] = str[a++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
