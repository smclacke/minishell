/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:59:29 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/04 20:53:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @todo	strjoin protection
 * @todo	strdup protection
 * @todo	error handling?
*/
int	add_to_expand(t_expand *str, char *copy_str)
{
	char	*tmp;

	if (!copy_str)
		return (-1);
	if (str->expanded)
		tmp = ft_strjoin(str->expanded, copy_str);
	else
		tmp = ft_strdup(copy_str);
	free(str->expanded);
	str->expanded = tmp;
	free(copy_str);
	if (!str->expanded)
		return (-1);
	return (0);
}

/**
 * @param	env expander struct
 * @param	exp environmet linked list
 * @brief	checks environment value of string to be expanded
 * 			if there is no value it free's the comp_str and env_value.
 * @return	1 if there is no value, 0 if value is found and assigned
 * @todo	triple check protection, norm and sooo when less tired
*/
int	get_check_value(t_expand *str, t_env **env)
{
	t_env	*head;
	int		len;

	head = *env;
	str->env_val = NULL;
	while (head)
	{
		if (shelly_strcmp(str->dollar, head->key) == 0)
		{
			if (!head->value)
				return (1);
			len = ft_strlen(head->value);
			str->env_val = ft_substr(head->value, 0, len);
			if (!str->env_val)
			{
				free(str->env_val);
				return (1);
			}
			return (0);
		}
		head = head->next;
	}
	return (1);
}

// static void	set_input_and_sign(t_expand *str, char *input_type, int type, int i)
// {
// 	str->sign = type;
// 	str->input = input_type;
// 	str->pos = i;
// }


/**
 * if cmd = $, put into input, type = CMD 
 * expand and return to proc var
 * 
 * else
 * 	while arrays.. then get the right str from there
 */
// int	set_expand_string(t_parser *lst, t_expand *str, int i)
// {
// 	t_parser	*tmp;

// 	str->sign = 0;
// 	str->input = NULL;
// 	tmp = lst;
// 	if (!tmp)
// 		return (0);
// 	if (tmp->proc->cmd && ft_strnstr(tmp->proc->cmd, "$", ft_strlen(tmp->proc->cmd)))
// 		set_input_and_sign(str, tmp->proc->cmd, CMD_X, 0);
// 	i = find_strs(tmp, str, i);
// 	i = find_hds(tmp, str, i);
// 	i = find_reds(tmp, str, i);
// 	// str, hd and reds are arrays...
// 	// return i position!!
// 	else if (tmp->proc->str && ft_strnstr(tmp->proc->str, "$", ft_strlen(tmp->proc->str)))
// 	{
// 		set_input_and_sign(str, tmp->proc->str, STR_X);
// 		return (1);
// 	}
// 	else if (tmp->proc->file && ft_strnstr(tmp->proc->file, "$", ft_strlen(tmp->proc->file)))
// 	{
// 		set_input_and_sign(str, tmp->proc->file, HD_X);
// 		return (1);
// 	}
// 		// set_input_and_sign(str, tmp->proc->file, RED_X);
// 	return (0);
// }

void		do_reds(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
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
				if (!str->expanded)
					return ;
				tmp->proc->redir[i] = str->expanded;
				if (!tmp->proc->redir[i])
					return ; // errorR?????
			}
			i++;
		}
	}
}

void		do_hds(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
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
				if (!str->expanded)
					return ;
				tmp->proc->hd[i] = str->expanded;
				if (!tmp->proc->hd[i])
					return ; // errorR?????
			}
			i++;
		}
	}
}

void		do_strs(t_parser *tmp, t_expand *str, t_env **env)
{
	int		i;
	int		len;

	i = 0;
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
				if (!str->expanded)
					return ;
				tmp->proc->str[i] = str->expanded;
				if (!tmp->proc->str[i])
					return ; // error?????
			}
			i++;
		}
	}
}

void		do_cmd(t_parser *tmp, t_expand *str, t_env **env)
{
	int		len;

	len = ft_strlen(tmp->proc->cmd);
	if (tmp->proc->cmd && ft_strnstr(tmp->proc->cmd, "$", len))
	{
		str->input = tmp->proc->cmd;
		str->expanded = NULL;
		dollar(str, env);
		if (!str->expanded)
			return ;
		tmp->proc->cmd = str->expanded;
		if (!tmp->proc->cmd)
			return ; //error || ??
	}
}
