/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/08 15:37:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// INPUT: e'ch'o abc$abc 
// OUTPUT: abc
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
		tokens = lexer(input);
		if (!tokens)
			continue ;
		shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;





		//-- Djoyke --//
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		if (shelly_check_for_builtin(tokens))//will be a expand funct
			printf("there's a builtin whoop\n");
		// execution // make env_list, create child processes, execve
		micro_execute(envp, tokens);
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
