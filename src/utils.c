/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/02 19:25:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int	shelly_strcmp(char *s1, char *s2)
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

void	free_only_tokens(t_parser *tokens)
{
	t_parser	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free (tokens);
		tokens = tmp;
	}
}

void	free_tokens(t_parser *tokens)
{
	t_parser	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free (tokens->input);
		free (tokens);
		tokens = tmp;
	}
}

// find out how many cmds there are total for pipe purposes
int	get_n_cmds(t_parser *tokens)
{
	t_parser	*tmp;
	int			i = 0;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->cmd)
			i += 1;
		tmp = tmp->next;
	}
	return (i);
}
