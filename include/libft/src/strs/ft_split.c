/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:31:47 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/10 19:52:25 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// static int	ft_words(char const *s, char c)
// {
// 	unsigned int	i;
// 	int				words;

// 	i = 0;
// 	words = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			words++;
// 		i++;
// 	}
// 	return (words);
// }

// static void	ft_free(char **arr, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

// static int	ft_letters(char const *s, char c, char **arr)
// {
// 	unsigned int	b;
// 	unsigned int	e;
// 	int				words;

// 	b = 0;
// 	words = 0;
// 	while (s[b] && words < ft_words(s, c))
// 	{
// 		e = 0;
// 		while (s[b] == c)
// 			b++;
// 		while (s[b + e] != c && s[b + e] != '\0')
// 			e++;
// 		arr[words] = ft_substr(s, b, e);
// 		if (!arr[words])
// 		{
// 			ft_free(arr, ft_words(s, c));
// 			return (0);
// 		}
// 		b += e;
// 		words++;
// 	}
// 	return (1);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**arr;

// 	if (!s)
// 		return (NULL);
// 	arr = (char **)ft_calloc((ft_words(s, c) + 1), sizeof(char *));
// 	if (!arr)
// 		return (0);
// 	if (!(ft_letters(s, c, arr)))
// 		return (NULL);
// 	return (arr);
// }

static int	lencount(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

static int	wordcount(char const *s, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (word);
}

static char	**freedom(char **md_array)
{
	int	i;

	i = 0;
	while (md_array[i] != NULL)
	{
		free(md_array[i]);
		i++;
	}
	free(md_array);
	return (NULL);
}

static char	*fill(char const *s, char c, int *i)
{
	char	*str;
	char	*d;
	int		len;

	d = (char *)s;
	len = lencount(d, c);
	str = ft_substr(d, 0, len);
	if (str == 0)
	{
		return (0);
	}
	*i += len;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	split_str = (char **)malloc((sizeof(char *) * (wordcount(s, c) + 1)));
	if (split_str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		split_str[j] = fill(&s[i], c, &i);
		if (split_str[j] == NULL)
			return (freedom(split_str));
		j++;
	}
	split_str[j] = NULL;
	return (split_str);
}

/*
Parameters:
s: The string to be split.
c: The delimiter character.

Return value: 
The array of new strings resulting from the split.
NULL if the allocation fails.

External functs: 
malloc, 
free

Description: 
Allocates (with malloc(3)) 
returns an array of strings obtained by splitting s
using the character ’c’ as a delimiter. 
The array must end with a NULL pointer.

extra function messes with value of i and j.
uses pointers to change value not the addres
break prevents from accessing unallocated memory
stops the loop
*/