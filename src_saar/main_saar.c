/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 15:19:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	// t_env		*env;

	(void) argc;
	(void) argv;
	(void) envp;

	tokens = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		//-- Sarah --//
		tokens = lexer(input);
		if (!tokens)
			continue ;
		shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;




		//-- Djoyke --//
		// micro_echo(parser_struct);
		// env = micro_env_list(envp);
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		// micro_execute(envp, par_tokens);
		// execution // make env_list, create child processes, execve
		// free input (readline needs to be fred at end)	
	}
	return (0);
}


/**
 * Old main
*/
// int	main(int argc, char **argv, char **envp)
// {
// 	(void) argc;
// 	(void) argv;
// 	(void) envp;
// 	char	*input;
// 	t_lexer	*tokens = NULL;

// 	while (1)
// 	{
// 		input = readline(PROMPT);
// 		add_history(input);
// 		tokens = lexer(input);
// 		if (!tokens)
// 			return (0);
// 		ft_print_tokens(tokens);

// 		// parse(tokens)
// 		// send list to expander
// 	}
// 	return (0);
	
// }
