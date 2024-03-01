/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 19:44:21 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @param env environment linked list
 * @param input string containing prompt input
 * @param exit_c int containing exit code
 * @brief function that runs minishell
 */
static int	run_minishell(t_env *env, char *input, int exit_c)
{
	t_parser	*procs;

	procs = NULL;
	if (input[0] == '\0')
	{
		free(input);
		return (E_NO_INPUT);
	}
	procs = parse_input(procs, input);
	if (!procs)
		return (E_SYNTAX);
	else
		procs->exit_code = exit_c;
	execute(&env, procs);
	exit_c = procs->exit_code;
	free_parser(procs);
	return (exit_c);
}

/**
 * @param og_stdin int fd 
 * @param og_stdout int fd
 * @param exit_c int exit code
 * @brief open's fd's
*/
static void	open_fds(int og_stdin, int og_stdout, int exit_c)
{
	if (dup2(STDOUT_FILENO, og_stdout) == -1)
		exit_c = E_GENERAL;
	if (dup2(STDIN_FILENO, og_stdin) == -1)
		exit_c = E_GENERAL;
}

/**
 * @param og_stdin int fd 
 * @param og_stdout int fd
 * @param exit_c int exit code
 * @brief closes fd's
*/
static void	close_fds(int og_stdin, int og_stdout, int exit_c)
{
	if (dup2(og_stdout, STDOUT_FILENO) == -1)
		exit_c = E_GENERAL;
	if (dup2(og_stdin, STDIN_FILENO) == -1)
		exit_c = E_GENERAL;
	if (og_stdout != -1 && close(og_stdout) == -1)
		exit_c = E_CLOSE;
	if (og_stdin != -1 && close(og_stdin) == -1)
		exit_c = E_CLOSE;
}

/**
 * @param input prompt string
 * @brief checks if readline doesn't return NULL
 * if returns NULL exits accordingly
*/
static char	*readline_check(char *input, int exit_c)
{
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 6);
		exit(exit_c);
	}
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	t_env		*env;
	char		*input;
	int			exit_c;

	(void) argc;
	(void) argv;
	env = NULL;
	og_stdout = 3;
	og_stdin = 4;
	exit_c = 0;
	env = env_list(envp, env);
	while (1)
	{
		open_fds(og_stdin, og_stdout, exit_c);
		handle_signals(PARENT);
		input = readline(PROMPT);
		readline_check(input, exit_c);
		exit_c = run_minishell(env, input, exit_c);
		if (exit_c == E_NO_INPUT)
			continue ;
		close_fds(og_stdin, og_stdout, exit_c);
	}
	return (exit_c);
}
