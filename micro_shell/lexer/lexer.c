/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:44:51 by smclacke      #+#    #+#                 */
/*   Updated: 2023/09/01 15:33:29 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief	if a single quotation is found, the string to searched to find the corresponding single qutation
 * 			same for double quotations
 * 			if the number of the type of quotations that are found is not even, the quotes can't be closed 
 * 			and therefore must error. 
 * @param	input from the command line
 * @return	will error if matching quotations are not closed, will return the index of closed quotations
*/
bool	closed_quotes(char *input)
{
	int	i;
	int	count_double;
	int	count_single;

	i = 0;
	count_double = 0;
	count_single = 0;
	while (input[i])
	{
		if (ft_isdouble_q(input[i]))
			count_double++;
		i++;
	}
	i = 0;
	while (input[i])
	{
		if (ft_issingle_q(input[i]))
			count_single++;
		i++;
	}
	if ((count_double % 2) != 0 || (count_single % 2) != 0)
		return (false);
	return (true);
}

/**
 * @brief	Check if there are any quotes and if they are closed
 * @param	tokens take the token->input (char *) to check through the string
 * @return	bool: true/false 1/0
*/
bool	shelly_check_quotes(char *tokens)
{
	char	*tmp;
	int		i = 0;
	
	tmp = tokens;
	while (tmp[i])
	{
		if (ft_isquote(tmp[i]))
		{	
			if (closed_quotes(tmp))
				return (true);
			else
				exit(EXIT_FAILURE); // need to error correctly for open quotes
		}
		i++;
	}
	return (false);
}

/**
 * @brief	takes the input string from the command line, iterates through it. While there
 * 			are no quotations, the string is split on spaces. If a quotation is encountered, 
 * 			the last quotation in the string is found and that segment is made into a separate
 * 			part of the array. 
 * @param	input input from the command line
 * @return	2D array of separated strings made from the input, ready to be tokenized
*/
static char	**parse_input(char *input)
{
	char	**array = NULL;

	// if (shelly_check_quotes(input))
	// {
	// 	array = ft_split_shelly(input); // this needs to work at some point in the future
	// 	if (!array)
	// 		return (NULL);
	// }
	// else
	// {
		array = ft_split(input, ' ');
		if (!array)
			return (NULL);
	// }
	return (array);
}

/**
 * @brief	once input has been parsed, quoted segments separated and spaces removed from the rest
 * 			of the input, iterate through the array creating substrings to put into token_str variable.
 * 			Node in a t_lexer list are created and added to the token_list which is returned to the parser
 * 			function to be passed to the parser.  
 * @param	parsed_input an array created but separating the input string into tokenizable bites
 * @return	newly made t_lexer token_list
*/
static t_parser	*make_token_list(char **parsed_input)
{
	t_parser		*tokens = NULL;
	t_parser		*token;
	char		*token_str;
	int			len;
	int			i = 0;

	while (parsed_input[i])
	{
		len = ft_strlen(parsed_input[i]);
		token_str = ft_substr(parsed_input[i], 0, len + 1);
		if (!token_str)
			return (0);
		token = lexer_listnew(token_str);
		if (!token)
			return (0);
		lexer_listadd_back(&tokens, token);
		i++;
	}
	return (tokens);
}

/**
 * @brief	takes the command line input, parses through the spaces outside quotations and creates
 * 			t_lexer tokens to pass to the parser. In the case of quotations, spaces must be kept and checked
 * 			for their validity, so if a quotation is encountered, take the end of the string and iterate
 * 			through to find the last quotation, all of this input is tokenized and then separated and validated
 * 			in the parser. 
 * @param	input from the commandline
 * @return	t_lexer token_list to pass to the parser
*/
t_parser	*lexer(char *input)
{
	t_parser		*tokens;
	char			**parsed_input = NULL;
	int				i;

	i  = 0;
	tokens = (t_parser *)malloc(sizeof(t_parser));
	if (!tokens)
		return (0);
	init_lexer(tokens);
	while (input[i])
	{
		parsed_input = parse_input(input);
		i++;
	}
	i = 0;
	if (!parsed_input)
		return (0);
	tokens = make_token_list(parsed_input);
	if (!tokens)
		return (0);
	return (tokens);
}

