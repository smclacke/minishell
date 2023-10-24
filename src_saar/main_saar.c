/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 22:11:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

t_parser	*print_the_full_thing(t_parser *tokens)
{
	t_parser	*list;
	int			i = 0;

	list = tokens;
	while (list)
	{
		printf("[%i]\t ", i);
		printf("cmd = %s\t", list->cmd);
		printf("file = %s\t", list->file);
		printf("meta = %s\t", list->meta);
		printf("str = %s\n", list->str);
		// printf("n_cmd = %i\n", list->n_cmd);
		i++;
		list = list->next;
	}
	return (tokens);
		// printf("sign = %i\n", sign);
		// printf("tmp->cmd = %s\n", tmp->cmd);
		// printf("tmp->meta = %s\n", tmp->meta);
		// printf("tmp->flag = %i\n", tmp->flag);
		// printf("tmp->file = %s\n", tmp->file);
		// printf("tmp->str = %s\n", tmp->str);
}

/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
 * old function:
*/
int	another_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

t_parser	*sort_list(t_parser *tokens)
{
	t_parser	*head;
	t_parser	*tmp;
	t_parser	*new;
	t_parser	*new_node;
	t_parser	*tmp2;
	int			sign = 0;

	head = tokens;
	tmp = tokens;
	new = NULL;
	while (tmp && !sign)
	{
		if (tmp->cmd)
		{
			new_node = lexer_listnew(tmp->cmd);
			new_node->cmd = tmp->cmd;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
			sign = 42;
		}
		tmp = tmp->next;
	}
	tmp = tokens;
	sign = 0;
	while (tmp)
	{
		if (!tmp->flag && another_strcmp(tmp->meta, "|") == 0)
		{
			new_node = lexer_listnew(tmp->meta);
			new_node->meta = tmp->meta;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
			tmp2 = tmp;
			tmp2 = tmp2->next;
			while (tmp2 && !tmp2->flag)
			{
				if (tmp2->cmd)
				{
					new_node = lexer_listnew(tmp2->cmd);
					new_node->cmd = tmp2->cmd;
					lexer_listadd_back(&new, new_node);
					tmp2->flag = 1;
				}
				tmp2 = tmp2->next;
			}
		}
		if (!tmp->flag && tmp->file)
		{
			new_node = lexer_listnew(tmp->file);
			new_node->file = tmp->file;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->str)
		{
			new_node = lexer_listnew(tmp->str);
			new_node->str = tmp->str;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		if (!tmp->flag && tmp->meta)
		{
			new_node = lexer_listnew(tmp->meta);
			new_node->meta = tmp->meta;
			lexer_listadd_back(&new, new_node);
			tmp->flag = 1;
		}
		tmp = tmp->next;
		sign++;
	}
	shelly_print_list(new);
	return (new);
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
	tokens = NULL;

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
		// shelly_print_list(tokens);

		tokens = parser(tokens);
		if (!tokens)
			continue ;

		tokens = sort_list(tokens);
		if (!tokens)
			printf("wtf? NO NODES\n");
		print_the_full_thing(tokens);
		// ft_execute(&env, tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

		free_tokens(tokens);	
	}
	return (0);
}
