/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/06 18:05:37 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int		run_minishell(t_parser *procs, char *input, t_env **env)
{
	procs = parse_input(procs, input);
	if (!procs)
		return (0);
	execute(env, procs);
	prpr(procs);
	free_parser(procs);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;
	t_parser	*procs;
	t_env		*env;

	(void) argc;
	(void) argv;
	procs = NULL;
	env = NULL;
	env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (!run_minishell(procs, input, &env))
			continue ;
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
		
		printf("success\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}
