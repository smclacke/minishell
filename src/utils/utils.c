/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 18:33:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

bool	is_space(char *input)
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


// void	free_only_tokens(t_parser *tokens)
// {
// 	t_parser	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }

/**
 * hehe ugly
*/
// void	free_tokens(t_parser *tokens)
// {
// 	t_parser	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		if (tokens->cmd != tokens->input)
// 			free(tokens->cmd);
// 		if (tokens->meta != tokens->input)
// 			free(tokens->meta);
// 		if (tokens->file != tokens->input)
// 			free(tokens->file);
// 		if (tokens->str != tokens->input)
// 			free(tokens->str);
// 		if (tokens->hd_limit != tokens->input)
// 			free(tokens->hd_limit);
// 		free (tokens->input);
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }

// find out how many cmds there are total for pipe purposes
// int	get_n_cmds(t_parser *tokens)
// {
// 	t_parser	*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		if (tmp->cmd)
// 			i += 1;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }
