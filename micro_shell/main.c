/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/26 20:54:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// INPUT: e'ch'o abc$abc 
// OUTPUT: abc

/**
 * need to do extensive error handling in the future
*/

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*par_tokens;

	(void) argc;
	(void) argv;
	(void) envp;
	tokens = NULL;
	par_tokens = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = micro_lexer(input);
		if (!tokens)
			return (0);
		printf("tokens after lexer -> \n");
		micro_print_tokens(tokens);
	
	
		par_tokens = micro_parser(tokens);
		printf("list after parser -> \n");
		micro_print_par_list(par_tokens);
		


		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		// micro_execute(envp, par_tokens);
		// execution // make env_list, create child processes, execve
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
