/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/18 15:07:22 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*dollar(t_exp_dol *str, t_env **env)
{
	(void)env;
	int		i = 0;
	int		j = 0;

	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i]))
	{
		j = i - 1;
		str->str_before_dol = &str->assed[j];
	}
	// str->
	// printf("before_dollar = %s\n", str->str_before_dol);
	// assed = full things returned after expansion 
	// concating and non expandable bits together

	// here all the expansion needs to happen
	


	// break it up, then check dollar parts for expansion
	// need to break up the string into
	// separate parts of the struct
	// check expansion if dollar part etc... (str->expand)

	// str->expand_this = check_if_expand(str->unassed);
	// if (!str->expand_this)
	// {
	// 	str->dont_expand_this = str->unassed;
	// }
	return (str->assed);
}

static void	expand_dollar(t_parser *lst, t_env **env, t_exp_dol *str)
{
	int			sign;

	sign = 0;
	str->unassed = set_expand_string(lst, str, &sign);
	if (sign == 1 || sign == 2)
	{
		str->assed = dollar(str, env);
		if (sign == 1)
		{
			lst->cmd = str->assed;
			sign = 0;
		}
		else if (sign == 2)
		{
			lst->str = str->assed;
			sign = 0;
		}
	}
}

void	ft_expand(t_parser *tokens, t_env **env)
{
	t_parser	*lst;
	t_exp_dol	*str;

	lst = tokens;
	str = (t_exp_dol *)malloc(sizeof(*str));
	if (!str)
		mini_error("malloc error exp_dol struct", errno);
	ft_bzero(str, sizeof(t_exp_dol));
	expand_quotes(lst);
	while (lst)
	{
		expand_dollar(lst, env, str);
		lst = lst->next;
	}
	// print_exp_dol_vals(str); // print and cont
}
