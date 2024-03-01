/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/01 20:23:40 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

int	add_to_expand(t_expand *str, char *copy_str)
{
	char	*tmp;

	if (!copy_str)
		general_error("expansion failure");
	if (str->expanded)
	{
		tmp = ft_strjoin(str->expanded, copy_str);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	else
	{
		tmp = ft_strdup(copy_str);
		if (!tmp)
			malloc_error(NULL, NULL, NULL, 0);
	}
	free(str->expanded);
	str->expanded = tmp;
	free(copy_str);
	if (!str->expanded)
		general_error("expansion failure");
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
				tmp->proc->redir[i] = NULL;
				str->expanded = NULL;
				dollar(tmp, str, env);
				if (str->expanded)
					tmp->proc->redir[i] = str->expanded;
				free(str->input);
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
				tmp->proc->hd[i] = NULL;
				str->expanded = NULL;
				dollar(tmp, str, env);
				if (str->expanded)
					tmp->proc->hd[i] = str->expanded;
				free(str->input);
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
				str->input = strdup(tmp->proc->str[i]);
				if (!str->input)
					malloc_error(tmp, NULL, tmp->proc->str, 3);
				free(tmp->proc->str[i]);
				str->expanded = NULL;
				dollar(tmp, str, env);
				if (str->expanded)
					tmp->proc->str[i] = str->expanded;
				free(str->input);
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
			str->input = ft_strdup(tmp->proc->cmd);
			if (!str->input)
				malloc_error(tmp, NULL, &tmp->proc->cmd, 3);
			free(tmp->proc->cmd);
			str->expanded = NULL;
			dollar(tmp, str, env);
			if (str->expanded)
				tmp->proc->cmd = str->expanded;
			free(str->input);
		}
	}
}
