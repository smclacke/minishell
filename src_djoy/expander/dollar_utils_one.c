/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_utils_one.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:05:34 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/11 16:21:23 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node node from parser linked list
 * @param env environment linked list 
 * @param exp expander struct
 * @param len lenght of node->str
 * @brief checks if $ present and needs expanding
*/
char	*dollar(char *str, t_env **env, t_expand *exp, int len)
{
	if (ft_strnstr(str, "$", len))
	{
		exp = ft_calloc(1, sizeof (t_expand));
		str = exp_dollar(str, env, exp, len);
	}
	return (str);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param len lenght of node->str
 * @brief checks if $ is at the end of the string
 * @return 1 if the $ is at the end of the string
 * 0 if not.
*/
int	check_at_len(char *str, t_expand *exp, int i, int len)
{
	if (str[i] == '$' && (i + 1) == len)
	{
		free_remain_struct(exp);
		return (1);
	}
	return (0);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @brief replaces the before_dollar string if it's NULL with 
 * node->str content of i lenght.
*/
void	get_before_dollar(char *str, t_expand *exp, int i)
{
	if (exp->before_dollar == NULL)
		exp->before_dollar = ft_substr(str, 0, i);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param j index at next $ sign
 * @brief gets the string to compare the environment key to
*/
void	get_compare_str(char *str, t_expand *exp, int i, int j)
{
	while (str[j] != '$' && !ft_isquote(str[j]) && str[j] != '\0')
		j++;
	exp->comp_str = ft_substr(str, i, j - i);
}

/**
 * @param node node from parser linked list
 * @param exp expander struct
 * @param i index
 * @param j index at next $ sign
 * @brief gets the string to compare the environment key to
*/
int	get_var_str(char *str, t_expand *exp, int i, int j)
{
	while (ft_isquote(str[i]) && str[i] != '\0')
		i++;
	j = i;
	while (!ft_isquote(str[j]) && str[j] != '\0')
		j++;
	exp->var = ft_substr(str, i, j - i);
	printf("exp->var = [%s]\n", exp->var);
	return (j);
}

/**
 * @param exp expander struct
 * @brief reassigns exp->before_dollar with expanded value
 * free the string containing the value and temp string used
 * for swapping
*/
void	reassing_before_dollar_with_var(t_expand *exp)
{
	char	*temp;

	temp = NULL;
	temp = exp->before_dollar;
	exp->before_dollar = ft_strjoin(exp->before_dollar, exp->var);
	free(temp);
}

/**
 * @param node parser linked list
 * @param env environmet linked list
 * @brief checks for a $ sign in the node
 * expands the string to actual value
 * @todo when "" '' quotes are handled check and adjust again
*/
char	*exp_dollar(char *str, t_env **env, t_expand *exp, int len)
{
	int			i;
	int			j;

	i = 0;
	while (str[i] != '\0')
	{
		// if (!sarah_expand_dollar(str))
		// {
		// 	printf("don't expand hehe\n");
		// 	// fix up the str for return 
		// 	// str = fix_up(str);
		// 	return (str);
		// }
		// else if (sarah_expand_dollar(str))
		// {
		// 	// printf("str[i] = %i\n", str[i]);
		// 	printf("need expansion but also quote fix_up");
		// 	// remove double quotes etc..?
		// 	// these become separate if statements so we
		// 	// can still expand...
		// 	// str = fix_up(str);
		// }
		if (check_at_len(str, exp, i, len) != 0)
			return (str);
		else if (((str[i] == '$') || (ft_isquote(str[i]))) && (i + 1) != len)
		{
			get_before_dollar(str, exp, i);
			if (str[i] == '$' || ft_isquote(str[i]))
			{
				if (ft_isquote(str[i]))
				{
					i = get_var_str(str, exp, i, j);
					exp->var = remove_quotes(exp->var);
					printf("exp->var = [%s]\n", exp->var);
					reassing_before_dollar_with_var(exp);
					printf("exp->before_dollar = [%s]\n", exp->before_dollar);
				}
				printf("i = [%i]\n", i);
				i++;
			}
			printf("len = [%i]\n", len);
			j = i;
			if (i == len)
			{
				str = return_exp(str, exp);
				return (str);
			}
			get_compare_str(str, exp, i, j);
			get_check_value(exp, env);
			save_expanded(exp);
			i = j - 1;	
		}
		i++;
	}
	str = return_exp(str, exp);
	return (str);
}
