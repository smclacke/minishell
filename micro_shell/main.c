/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 14:36:24 by dreijans      ########   odam.nl         */
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
	t_parser	*parser_struct;
	// t_expand	*expand_list;

	(void) argc;
	(void) argv;
	tokens = NULL;
	parser_struct = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		//-- Sarah --//
		tokens = lexer(input);
		if (!tokens)
			continue ;
		print_lexer(tokens);
		

		parser_struct = parser(tokens);
		if (!parser_struct)
			continue ;
		




		//-- Djoyke --//
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		if (shelly_check_for_builtin(parser_struct))//will be a expand funct
			printf("there's a builtin whoop\n");
		// execution // make env_list, create child processes, execve
		micro_execute(envp, parser_struct);
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
