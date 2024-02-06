------------------------------TO DO----------------------------

1) 

    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 

    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 

    handle exit codes

4) EXPORT OR EXPANDER

    export var=a
    export $var=test
    echo $var $a
    a test

5) NORM here-doc

6) PARSER is this me?
    ..
    bash: ..: command not found

    minibleh:..

7) ECHO??

    minibleh:< testfile.txt echo hi

    minibleh:echo < testfile.txt hi

    minibleh:


**------------------ hello from sarah -------------------------**

nice lookin' globals 00 :P

*first thing*
when we only run " << eof " and dont run it with cat command
if we CTRL C or give the limiter, we exit the whole shell


*second thing*
when we CTRL C, we give two prompts and still print the here_doc input
bash gives:
> ^C
[prompt]

// Example:
minibleh:cat << eof
heredoc> sdf
heredoc> sdf
heredoc> sdf
heredoc> 
minibleh:
sdf
sdf
sdf
minibleh:^C
minibleh:


*third thing*
".." not erroring
		same with "''" (single quotes) and """" (double quotes)
need to give no command error


*fourth thing*
heredoc still weird, two prompts with signal (ctrl c sws, not sure about the quite signal)


*fifth thing*
 expanding $?


!!*we are not:*!!
- SHLVL
- export ls="ls -l"

char	**null_check(char *str, t_parser *temp)
{
	// char		**words;
	char		words[2];
	int			i;

	i = 0;

	words = NULL;
	// words = ft_split(str, '=');
	words[0] = ft_substr(0, lencount(str, '='));
	words[1] = ft_substr(lencount(str, '=', ft_strlen(str + 1)));
	// words[2] = NULL;
	// while(words[i] != NULL)
	// {
	// 	printf("word = %s\n", words[i]);
	// 	i++;
	// }
	if (words == NULL)
		mini_error(E_GENERAL, temp);
	if (words[0] == NULL)
	{
		ft_free_arr(words);
		return (NULL);
	}
	return (words);
}


/**
 * @param lst linked list
 * @brief checks if the words are export and unset norm
 * proof.
 * key (word) first letter has:
 * capital (H), lowercase (h), underscore (_) as first letter 
 * else give error if given 99=djoyke as key
 * minishell: export: `99=djoyke': not a valid identifier
 * rest of word can only have numbers, letters and underscore.
 * else give error export d@@=haha
 * minishell: export: `d@@=haha': not a valid identifier
 * same for unset
 * @return true if wrong found with the words
 * @todo the !word error part is for this edge case :
 * export "" test=a
 * 
 * but comprimises this edge case which didnt work before
 * but now doesnt work in a different way:
 * export var=a
 * export $var=test
 * echo $var $a
*/
bool	word_check(char *str, t_parser *lst)
{
	t_parser	*temp;
	char		**words;
	char		*cmd;

	cmd = lst->proc->cmd;
	temp = lst;
	words = null_check(str, lst);
	if (!words)
	{
		put_custom_error(lst, "export");
		mini_error(E_GENERAL, lst);
		return (true);
	}
	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
	{
		put_custom_error(temp, cmd);
		return (true);
	}
	if (key_value_check(lst, words, "export") == 1)
	{
		ft_free_arr(words);
		return (true);
	}
	ft_free_arr(words);
	return (false);
}



ERRORS TO STANDARD ERROR!