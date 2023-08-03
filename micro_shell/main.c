/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 17:30:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// INPUT: e'ch'o abc$abc 
// OUTPUT: abc
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*parser_struct;

	(void) argc;
	(void) argv;
	// (void) envp;

	tokens = NULL;
	parser_struct = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
			continue ;
		micro_print_lexer(tokens);
		print_lexer(tokens);
		parser_struct = parser(tokens);
		if (!parser_struct)
			continue ;
		if (shelly_check_for_builtin(parser_struct))
			printf("there's a builtin whoop\n");
		micro_execute(envp, parser_struct);
	}
	return (0);
}
