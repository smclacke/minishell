/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/31 14:40:06 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// INPUT: e'ch'o abc$abc 
// OUTPUT: abc

// Djoyke, when checking vadility of the rest of the input, after first peice of input, i can send
// to you what is what and then you expand it, if its not good in expanding process, then error thrown
// sarah: try explain this so it makes sense....

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*par_tokens;
	// t_env		*env;

	(void) argc;
	(void) argv;
	(void) envp;
	// int		i = 0;


	tokens = NULL;
	par_tokens = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		//-- Sarah --//
		tokens = micro_lexer(input);
		if (!tokens)
			continue ;
		printf("tokens after lexer -> \n");
		micro_print_tokens(tokens);
	
		par_tokens = micro_parser(tokens);
		printf("list after parser -> \n");
		micro_print_par_list(par_tokens);




		//-- Djoyke --//
		// env = micro_env_list(envp);
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		// micro_execute(envp, par_tokens);
		// execution // make env_list, create child processes, execve
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
