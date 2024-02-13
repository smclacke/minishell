/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/13 17:42:18 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	add_to_expand(t_expand *str, char *copy_str)
{
	char	*tmp;

	if (!copy_str)
		return (-1);// error?
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, copy_str);
		if (!tmp)
			return (-1);// malloc error
	}
	else
	{
		tmp = ft_strdup(copy_str);
		if (!tmp)
			return (-1);// malloc error
	}
	free(str->expanded);
	str->expanded = tmp;
	free(copy_str);
	if (!str->expanded)
		return (-1);// error?
	return (0);
}

void	do_reds(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	str->input = NULL;
	if (tmp->proc->red_count != 0)
	{
		while (i < tmp->proc->red_count)
		{
			len = ft_strlen(tmp->proc->redir[i]);
			if (ft_strnstr(tmp->proc->redir[i], "$", len))
			{
				str->input = tmp->proc->redir[i];
				str->expanded = NULL;
				dollar(str, env);
				tmp->proc->redir[i] = str->expanded;
			}
			i++;
		}
	}
}

void	do_hds(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	str->input = NULL;
	if (tmp->proc->hd_count != 0)
	{
		while (i < tmp->proc->hd_count)
		{
			len = ft_strlen(tmp->proc->hd[i]);
			if (ft_strnstr(tmp->proc->hd[i], "$", len))
			{
				str->input = tmp->proc->hd[i];
				str->expanded = NULL;
				dollar(str, env);
				tmp->proc->hd[i] = str->expanded;
			}
			i++;
		}
	}
}

void	do_strs(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	str->input = NULL;
	if (tmp->proc->str_count != 0)
	{
		while (i < tmp->proc->str_count)
		{
			len = ft_strlen(tmp->proc->str[i]);
			if (ft_strnstr(tmp->proc->str[i], "$", len))
			{
				str->input = tmp->proc->str[i];
				str->expanded = NULL;
				dollar(str, env);
				tmp->proc->str[i] = str->expanded;
			}
			i++;
		}
	}
}

void	do_cmd(t_parser *tmp, t_expand *str, t_env **env)
{
	int		len;

	len = 0;
	str->input = NULL;
	if (tmp->proc->cmd)
	{
		len = ft_strlen(tmp->proc->cmd);
		if (ft_strnstr(tmp->proc->cmd, "$", len))
		{
			str->input = tmp->proc->cmd;
			str->expanded = NULL;
			dollar(str, env);
			tmp->proc->cmd = str->expanded;
		}
	}
}
