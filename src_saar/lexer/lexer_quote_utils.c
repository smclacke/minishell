/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_quote_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/08 23:30:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/09 16:41:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sarah.h"

int	lq_what_to_split(char c)
{
	if (c == 0 || c == 32 || c == 9 || c == 10)
		return (1);
	return (0);
}

int	lq_count_words(char *input)
{
	int	i = 0;
	int	count = 0;
	
	while (input[i])
	{
		while (input[i] && lq_what_to_split(input[i]))
			i++;
		if (input[i])
			count++;
		while (input[i] && !lq_what_to_split(input[i]))
			i++;
	}
	return (count);
}

int	lq_word_length(char *input)
{
	int	i = 0;

	while (input[i] && !lq_what_to_split(input[i]))
		i++;
	return (i);
}

int	quote_length(char *input)
{
	int	i = 0;
	int	len = ft_strlen(input);

	while (*input && i < len) // *input maybe enough?
		input++;
	while (*input && !ft_isquote(input))
	{
		len--;
		input--;
	}
	return (len);
}

///////////////bullshit


// static int	find_last_quote(char *input)
// {
// 	int		i = 0;
// 	int		start = 0;
// 	int		end = 0;
// 	int		total_size = ft_strlen(input);

// 	printf("total_size: [%i]\n", total_size);
// 	printf("input: [%s]\n", input);
// 	while (input[i])
// 	{
// 		while (input[i] && !ft_isquote(input[i]))
// 			i++;
// 		if (ft_isquote(input[i]))
// 		{
// 			start = i;
// 			printf("start: [%i]\n", start);
// 			while (input[i])
// 				i++;
// 			while (start < total_size && !ft_isquote(input[total_size]))
// 				total_size--;
// 			if (ft_isquote(input[total_size] && start != total_size))
// 				end = start - total_size;
// 			printf("end: [%i]\n", end);
// 		}
// 		i++;
// 	}
// 	return (end);
// }

// static char	*handle_quotes(char *input)
// {
// 	// int			i = 0;
// 	// int			j = 0;
// 	int			len = find_last_quote(input); // size from first to last quote
// 	char		*without;

// 	printf("len size: [%i]\n", len);
// 	without = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!without)
// 		return (NULL);
// 	// while (input[i])
// 	// {
// 	// 	while (input[i] && lq_what_to_split(input[i]))
// 	// 		i++;
// 	// 	if (ft_isquote(input[i]) && lq_what_to_split(input[i - 1]))
// 	// 	{
// 	// 		while (input[i])
// 	// 		{
// 	// 			without[j] = input[i];
// 	// 			i++;
// 	// 		}
// 		// }
// 		// 	if (ft_isquote(input[i]) && what_to_split(input[i + 1]))
// 		// 		without[j] = input[i];
// 		// }
// 		// if (ft_isquote(input[i] && !what_to_split(input[i - 1])))
// 		// {
// 		// 	while (input[i] && !what_to_split(input[i]))
// 		// 		i--;
// 		// 	if (input[i] &&  what_to_split(input[i]))
// 		// 	{
// 		// 		i++;
// 		// 		while (input[i])
// 		// 		{
// 		// 			without[j] = input[i];
// 		// 			i++;
// 		// 		}
// 		// 		if (ft_isquote(input[i]) && what_to_split(input[i + 1]))
// 		// 			without[j] = input[i];
// 		// 	}
// 		// }
// 		// i++;
// 	// }
// 	return (without);
// }

