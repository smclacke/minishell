/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 16:39:23 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/18 18:05:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// do quote check and splitting before this ??
// figuring it out without quotes down here
//getting a bit of the logical without quotes, but not sure about orser plus need 
//to find expandable things, expand them, add them to assed str, 
//then empty expand_this to keep searching through unassed

	
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
// need to call separately and iterate, if expand_this has $USER, dont want to try 
// adding another $USER before its expanded and added to assed var		
	// while (str->unassed[i])
	// {
	// 	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 		i++;
	// 	if (ft_dollar(str->unassed[i]))
	// 	{
	// 		str->unassed = expand_this(str, i);
	// 		if (!str->unassed)
	// 			return (str->assed);
	// 		printf("expand = %s\n", str->expand_this);
	// 		printf("unassed = %s\n", str->unassed);
	// 	}
	// 	i++;
	// }
	// str->unassed = expand_this(str, i);
	// if (!str->unassed)
	// 	return (str->assed);
	
	// printf("unassed[i] = %c\n", str->unassed[i]);
	// while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 	i++;
	// 	// while (str->unassed[i] && !ft_dollar(str->unassed[i]))
	// 	// 	i++;
	// if (ft_dollar(str->unassed[i])) // or quote, get the stuff between the two dollars
	// {
	// 	str->unassed = expand_this(str, i);
	// 	if (!str->unassed)
	// 		return (str->assed);
	// 	i = 0;
	// }
	// str->unassed = expand_this(str, i); // or there are no quotes/dollars after first
	// // encounter and we can iust expand the stuff we have after last dollar is found
	// if (!str->unassed)
	// 	return (str->assed);

static char	*save_this(t_exp_dol *str, int i)
{
	str->str_before_dol = ft_substr(str->unassed, 0, i);
	if (!str->str_before_dol) // if it fails or there wasnt anything before dollar
		return (str->unassed);
	str->unassed = ft_strtrim(str->unassed, str->str_before_dol);
	// add str->before_dollar to assed as first bit of str
	return (str->unassed);
}

static char	*expand_this(t_exp_dol *str, int i)
{
	str->expand_this = ft_substr(str->unassed, 0, i);
	// if (!str->expand_this) // if it fails
	// 	return (str->unassed);
	str->unassed = ft_strtrim(str->unassed, str->expand_this);
	// now expand, add to assed, then empty expand_this
	// printf("unassed in func = %s\n", str->unassed);
	return (str->unassed);
}

static char	*check_first(t_exp_dol *str)
{
	int		i = 0;
	
	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i]))
		str->unassed = save_this(str, i);
	return (str->unassed);
}

static char	*check_rest(t_exp_dol *str)
{
	int		i = 0;

	while (str->unassed[i] && !ft_dollar(str->unassed[i]))
		i++;
	if (ft_dollar(str->unassed[i]))
	{
		str->unassed = expand_this(str, i);
		if (!str->unassed)
			return (NULL);
	}
	return (str->unassed);
}

static char	*dollar(t_exp_dol *str, t_env **env)
{
	(void)env;
	// int		i = 0;
	// quotes....

	str->unassed = check_first(str);
	// while (str->unassed)
	// {
		printf("unassed = %s\n", str->unassed);
		if (str->unassed)
		{
			str->unassed = check_rest(str);
			if (!str->unassed)
				return (str->assed);
		}
	// }

	print_exp_dol_vals(str);

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
