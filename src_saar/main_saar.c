/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/01 16:56:38 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

// t_parser	*print_the_full_thing(t_parser *tokens)
// {
// 	t_parser	*list;
// 	int			i = 0;

// 	list = tokens;
// 	while (list)
// 	{
// 		printf("[%i]\t ", i);
// 		printf("cmd = %s\t", list->cmd);
// 		printf("file = %s\t", list->file);
// 		printf("meta = %s\t", list->meta);
// 		printf("str = %s\n", list->str);
//		 printf("n_cmd = %i\t", list->n_cmd);
// 		printf("hd_fd = %i\n", list->hd_fd);
// 		i++;
// 		list = list->next;
// 	}
// 	return (tokens);
// }

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_parser	*parsed;
	t_env		*env;


	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	tokens = NULL;
	parsed = NULL;

	int	og_stdout = dup(STDOUT_FILENO);
	int	og_stdin = dup(STDIN_FILENO);

	while (1)
	{
		input = readline(PROMPT);
		add_history(input);

		tokens = lexer(input);
		free (input);
		if (!tokens)
			continue ;

		parsed = parser(tokens);
		free(tokens);
		if (!parsed)
			continue ;

		execute(&env, parsed);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

		free_tokens(parsed);
	}
	return (0);
}
