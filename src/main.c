/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/06 15:39:00 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../include/shelly.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*procs;
	char		**tokens;

	int			og_stdout;
	int			og_stdin;
	t_env		*env;

	(void) argc;
	(void) argv;
	// (void) envp;
	procs = NULL;

	env = NULL;
	env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
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
		free(tokens);

		execute(&env, procs);

		prpr(procs);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

		// free_parser(procs);

		printf("success\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}
