/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 12:11:57 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/07/26 15:31:21 by dreijans      ########   odam.nl         */
=======
/*   Updated: 2023/07/26 15:36:43 by smclacke      ########   odam.nl         */
>>>>>>> 75d24479e1e20c5f862e95b74c574e8b1b6559d7
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
<<<<<<< HEAD
	char	*input;
	t_lexer	*tokens;

	(void) argc;
	(void) argv;
	(void) envp;
	tokens = NULL;
=======
	(void) 		argc;
	(void) 		argv;
	(void) 		envp;
	char		*input;
	t_lexer		*tokens = NULL;
	t_parser	*par_tokens = NULL;
	
>>>>>>> 75d24479e1e20c5f862e95b74c574e8b1b6559d7
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = micro_lexer(input);
		if (!tokens)
			return (0);
		micro_ft_print_tokens(tokens);
<<<<<<< HEAD
=======

		par_tokens = micro_parser(tokens);
>>>>>>> 75d24479e1e20c5f862e95b74c574e8b1b6559d7
		// parser(tokens)
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		// execution // make env_list, create child processes, execve
		// free input (readline needs to be fred at end)	
	}
	return (0);
}
