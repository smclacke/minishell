/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 14:09:11 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @todo	you need to be normed
 * @todo	check the frees
 * @todo	free proc struct
*/
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**tokens;
	t_parser	*procs;

	// int			og_stdout;
	// int			og_stdin;
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
		if (!tokens)
			continue ;

		procs = parse_tokens(tokens);
		if (!procs)
			printf("NOPE\n");
		ft_free_arr(tokens);
		free_parser(procs);

		printf("success\n");
		exit(EXIT_SUCCESS);

		// execute(&env, tokens);

		// dup2(og_stdout, STDOUT_FILENO);
		// dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
