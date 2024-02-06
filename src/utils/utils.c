/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 21:38:52 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/06 16:34:47 by smclacke      ########   odam.nl         */
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

static	void	sarah_free_procs(t_procs *proc)
{
	int			i;

	i = 0;
	if (proc->cmd)
		free(proc->cmd);
	if (proc->str_count != 0)
	{
		while (i < proc->str_count)
		{
			free(proc->str[i]);
			i++;
		}
	}
	i = 0;
	if (proc->hd_count != 0)
	{
		while (i < proc->hd_count)
		{
			free(proc->hd[i]);
			i++;
		}
	}
	i = 0;
	if (proc->red_count != 0)
	{
		while (i < proc->red_count)
		{
			free(proc->redir[i]);
			i++;
		}
	}
}

/**
 * @todo	check this is correct for new parser ...
*/
void	free_parser(t_parser *procs)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	while (procs)
	{
		tmp = procs->next;
		if (procs->proc_arrs)
		{
			while (procs->proc_arrs[i])
			{
				ft_free_arr(procs->proc_arrs[i]);
				i++;
			}
		}
		free(procs->process);
		sarah_free_procs(procs->proc);
		free(procs->proc);
		procs = tmp;
	}
	free(tmp);
	free(procs);
}

void	sarah_error(t_parser *proc, char *str)
{
	if (proc)
		free_parser(proc);
	printf("%s\n", str);
	exit (EXIT_FAILURE);
}
