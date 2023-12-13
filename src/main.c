/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/13 17:14:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * after firguring this out properly
 * could write func to take input, tokenize, parser... return 
 * just the shizz the executor needs and make this main shorter
*/

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**tokens;
	// int			og_stdout;
	// int			og_stdin;

	
	// t_process	data;
	// t_lexer		*tokens;
	t_parser	*procs;
	// t_env		*env;

	(void) argc;
	(void) argv;
	(void) envp;
	procs = NULL;
	// env = NULL;
	// env = env_list(envp, env);
	// og_stdout = dup(STDOUT_FILENO);
	// og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);

		tokens = lexer(input);
		free(input);
		print_token_arr(tokens);
		if (!tokens)
			continue ;

		procs = parse_tokens(tokens);

		ft_free_arr(tokens);
		free_only_tokens(procs);
		exit(EXIT_SUCCESS);


		// parser(&data); // add wrapper
		// print_parser(&data);
		// if (!procs)
		// 	continue ;
		// print_new_parser(&data);
		// exit(EXIT_SUCCESS);
		// print_the_full_thing(tokens);


		// execute(&env, tokens);
		// free_tokens(tokens);
		// dup2(og_stdout, STDOUT_FILENO);
		// dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
