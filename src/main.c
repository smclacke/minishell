/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/04 15:50:57 by smclacke      ########   odam.nl         */
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
		// ft_free_arr(tokens);
		
		// int		i = 0;
		// while (procs)
		// {
		// 	printf("in main\n");
		// 	printf("[%i] cmd = %s\n", i, procs->proc->cmd);
		// 	printf("[%i] hd_count = %i\n", i, procs->proc->hd_count);
		// 	procs = procs->next;
		// 	i++;
		// }
	

		// printf("success\n");
		// exit(EXIT_SUCCESS);

		execute(&env, procs);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
		// free_parser(procs);
	}
	return (0);
}
