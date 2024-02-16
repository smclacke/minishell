/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/16 15:12:43 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * // = remove for final version
 * 	everything else is normed
 */
int	run_minishell(char **envp, char *input)
{
	t_parser	*procs;
	t_env		*env;

	(void) envp;
	procs = NULL;
	env = NULL;
	// env = env_list(envp, env);
	procs = parse_input(procs, input);
	if (!procs)
		return (0);
	// prpr(procs); //
	// execute(&env, procs);
	// prpr(procs); //
	free_parser(procs);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;

	(void) argc;
	(void) argv;
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (!run_minishell(envp, input))
			continue ;
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
		// printf("success\n"); //
		exit(EXIT_SUCCESS); //
	}
	return (0);
}
