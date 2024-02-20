/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/20 21:06:20 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 *	is this the right logic?
 * 	if parser succeeds exit code is 0, update parser exit code with previous
 * 	otherwise error occurred, syntax exit given back to main
 */
int	run_minishell(t_env *env, char *input, int exit_c)
{
	t_parser	*procs;

	procs = NULL;
	procs = parse_input(procs, input);
	// prpr(procs);
	if (!procs)
		return (E_SYNTAX);
	else
		procs->exit_code = exit_c;
	execute(&env, procs);
	exit_c = procs->exit_code;
	free_parser(procs);
	return (exit_c);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;
	t_env		*env;
	int			exit_c;

	(void) argc;
	(void) argv;
	env = NULL;
	exit_c = 0;
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	env = env_list(envp, env);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_SUCCESS);
		exit_c = run_minishell(env, input, exit_c);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
