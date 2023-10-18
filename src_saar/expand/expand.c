/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/18 16:32:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

static char	*dollar(t_exp_dol *str, t_env **env)
{
	(void)env;
	int		i = 0; // start till first dollar
	int		j = 0; // from first dollar

// do quote check and splitting before this ??
// figuring it out without quotes down here

	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i])) // first dollar...
	{
		str->str_before_dol = ft_substr(str->unassed, 0, i);
		str->unassed = ft_strtrim(str->unassed, str->str_before_dol);
	}
	j++;
	// while (str->unassed)
	// {
		while (str->unassed[j] && !ft_dollar(str->unassed[j]))
			j++;
		if (ft_dollar(str->unassed[j]))
		{
			printf("unassed = %s\n", str->unassed);
			printf("unassed[j] = %c\n", str->unassed[j]);
			str->expand_this = ft_substr(str->unassed, 0, j);
			str->unassed = ft_strtrim(str->unassed, str->expand_this);
			j++;
		}
	// }

// need to call separately and iterate, if expand_this has $USER, dont want to try 
// adding another $USER before its expanded and added to assed var

	print_exp_dol_vals(str); // print and cont 


	
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
}
