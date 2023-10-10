/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:31:47 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/10 20:11:02 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

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
