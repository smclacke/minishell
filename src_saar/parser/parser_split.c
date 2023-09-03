/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_split.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 19:43:29 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/03 19:50:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

int	what_to_split(char c)
{
	return (c == '>' || c == '<' || c == )
}

int	word_count(char *str)
{
	
}

int	word_len(char *str)
{
	
}

char	*make_words(char *str)
{
	char	*words;
	int		i = 0;
	int		len = word_len(str);
	
	words = (char *)malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		words[i] = str[i];
		i++;
	}
	words[i] = '\0';
	return (words);
}

char	**ft_split(char *str)
{
	char	**array;
	int		i = 0;
	
	array = (char **)malloc(sizeof(char *) * word_count(str) + 1);
	while (*str)
	{
		while (*str && !what_to_split(*str))
			str++;
		if (*str)
		{
			array[i] = make_words(str);
			i++;
		}
		while (*str && !what_to_split(*str))
			str++;
	}
	array[i] = 0;
	return (array);
}

int	main()
{
	char	**array;
	char	*str = "some<file<<meta>split>>up";
	int		i = 0;

	array = ft_split(str);
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
}
