/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/12 19:48:19 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	char	*input;
	char	*no_quote;
	t_list	*token;
	int		i;

	while(1)
	{
		i = 0;
		input = readline(PROMPT);
		add_history(input);
		no_quote = check_quotes(input);
		argv = ft_split(no_quote, ' ');
		if (!argv)
			return (EXIT_FAILURE);
		while (argv[i])
		{
			token = lexer(argv[i]);
			ft_print_tokens(token);
			i++;
		}
	}
}


// WHAT MUST BE WRITTEN!!!!!!!!!!!
/**
 * argv = func()
 * func = check for quotes, if found, remove
 * then split via spaces and make tokens
 * if quotes found, make tokens out of them
*/


