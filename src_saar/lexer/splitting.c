/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:39:28 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/12 18:02:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// everything starts and finishes here.... let's goooooooo
		 // WE MUST SEPARATE METAS
	// split on spaces, split on metas but add metas to token array
	// if quotes, split those apart keep them totally intact

// int		quotes_yes(char *input) // which quote
// {
// 	int		i = 0;
// 	while (input[i])
// 	{
// 		if (which_quote(input[i]) == 2)
// 			return (DOUBLE_Q);
// 		else if ()
// 	}

// 	return (NULL);
// }

static char	*find_tokens(char *input)
{
	char	*tmp;
	tmp = (char *)malloc(sizeof(char) * total_len + 1);
	while (input[i])
	{
		while (input[i] && !which_quote(input[i]) && !is_redirect(input[i]))
		{
			if (lq_what_to_split(input[i]))
			{
				tmp = ft_substr(input, 0, i - 1);
				
			}
			
		}
		i++;
	}
	
}

static char	**make_array(char *input)
{
	char	**array;
	int		token_count = count_tokens(input);
	int		total_len = ft_strlen(input);
	int		i = 0;

	array = (char **)malloc(sizeof(char *) * token_count + 1);
	array = find_tokens(input);
	// while (input)
	// {
	// 	while (input && good_stuff(input))
	// 		input++;
	// 	if (input && !good_stuff(input))
	// 		array = split_input(input);
	// 	while (input && !good_stuff(input))
	// 		input++;
	// }
	array = 0;
	return (array);
}

/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces with metas (exc. dollar) also being 
 * 			split into separate str. If a quotation is encountered, the matching quote is found and
 * 			all of that input is put into token
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
char	**parse_input(char *input)
{
	char	**array = NULL;

	array = make_array(input);
	// array = ft_split(input, ' ');
	if (!array)
		return (NULL);
	return (array);
}
