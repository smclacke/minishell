/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/01 17:50:54 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

static bool	is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_parser_list(t_parser *lst)
{
	int i;

	i = 0;
	while (lst != NULL)
	{
		printf("||\n");
		printf("index = [%d], cmd = [%s]\n", i, lst->cmd);
		printf("index = [%d], str = [%s]\n", i, lst->str);
		printf("index = [%d], meta = [%s]\n", i, lst->meta);
		printf("next node\n");
		if (lst->next == NULL)
			printf("NULL\n");
		lst = lst->next;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_env		*env;


	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);

	int	og_stdout = dup(STDOUT_FILENO);
	int	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (!input)
			exit(0);
		if (!is_space(input))
			add_history(input);


		tokens = lexer(input);
		free(input);
		if (!tokens)
			continue ;

		tokens = parser(tokens);
		if (!tokens)
			continue ;
		print_parser_list(tokens);
		execute(&env, tokens);
		free_tokens(tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

	}
	return (0);
}
