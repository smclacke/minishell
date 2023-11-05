// static char	*expand_this(t_expand *str, t_env **env, int i)
// {
// 	printf("something needs to be expanded\n");
// 	i++;
// 	while (str->input[i] && !ft_dollar(str->input[i]))
// 		i++;
// 	str->do_expand = ft_substr(str->input, 0, i);
// 	if (!str->do_expand)
// 		return (str->input);
// 	str->do_expand = ft_strtrim(str->input, "$");
// 	printf("str->do_expand HERE = %s\n", str->do_expand);
// 	str->input = ft_strtrim(str->input, "$");
// 	str->input = ft_strtrim(str->input, str->do_expand);
// 	printf("str->input HERE = %s\n", str->input);
// 	if (get_check_value(str, env))
// 		mini_error("bit fucked in expand_this()", errno); // this fails with two dollars
// 	free (str->do_expand);
// 	printf("epxanded = %s\n", str->expanded);
// 	printf("done = %s\n", str->done);
// 	str->done = ft_strjoin(str->done, str->expanded);
// 	printf("str->done = %s\n", str->done);
// 	printf("str->input = %s\n", str->input);
// 	return (str->input);
// }

// /**
//  * @todo all of this shitt...
// */
// char	*check_rest(t_expand *str, t_env **env, int i)
// {
// 	while (str->input[i] && !ft_dollar(str->input[i])) // OR QUOTES ('''')
// 		i++;
// 	if (ft_dollar(str->input[i])) // OR QUOTES (dllar could still be in quotes)
// 	{
// 		str->input = expand_this(str, env, i);
// 		if (!str->input)
// 			return (NULL);
// 	}
// 	if (!str->input)
// 		return (NULL);
// 	return (str->input);
// }