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



1) ERRORS TO STANDARD ERROR!
2) exit > hoi.txt is writing exit in the file

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

first! before start,

clone met ssh!!!!! wieeeeeeh


minishell git:(djoyke) ✗ valgrind --leak-check=full ./minishell
==1842334== Memcheck, a memory error detector
==1842334== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1842334== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==1842334== Command: ./minishell
==1842334== 
minibleh:cat Makefile | grep pr | head -n 5 | hello

[0] cmd = cat

[0] str_count = 1
[0] strs[0] = Makefile

[0] hd_count = 0

[0] red_count = 0
--------------------------------------------------

[1] cmd = grep

[1] str_count = 1
[1] strs[0] = pr

[1] hd_count = 0

[1] red_count = 0
--------------------------------------------------

[2] cmd = head

[2] str_count = 2
[2] strs[0] = -n
[2] strs[1] = 5

[2] hd_count = 0

[2] red_count = 0
--------------------------------------------------

[3] cmd = hello

[3] str_count = 0

[3] hd_count = 0

[3] red_count = 0
--------------------------------------------------
executable = [/usr/bin/cat]
executable = [/usr/bin/head]
executable = [/usr/bin/grep]
minishell: hello: command not found
executable = [hello]
==1842410== 
==1842410== HEAP SUMMARY:
==1842410==     in use at exit: 222,694 bytes in 639 blocks
==1842410==   total heap usage: 887 allocs, 248 frees, 245,435 bytes allocated
==1842410== 
==1842410== 293 (80 direct, 213 indirect) bytes in 1 blocks are definitely lost in loss record 35 of 82
==1842410==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1842410==    by 0x402E65: init_parser (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842410==    by 0x402DA3: parse_tokens (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842410==    by 0x402D1D: parse_input (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842410==    by 0x40131D: run_minishell (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842410==    by 0x4013CA: main (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842410== 
==1842410== LEAK SUMMARY:
==1842410==    definitely lost: 80 bytes in 1 blocks
==1842410==    indirectly lost: 213 bytes in 14 blocks
==1842410==      possibly lost: 0 bytes in 0 blocks
==1842410==    still reachable: 222,401 bytes in 624 blocks
==1842410==         suppressed: 0 bytes in 0 blocks
==1842410== Reachable blocks (those to which a pointer was found) are not shown.
==1842410== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1842410== 
==1842410== For lists of detected and suppressed errors, rerun with: -s
==1842410== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
minibleh:exit


==1842334== 
==1842334== HEAP SUMMARY:
==1842334==     in use at exit: 235,223 bytes in 986 blocks
==1842334==   total heap usage: 1,232 allocs, 246 frees, 257,303 bytes allocated
==1842334== 
==1842334== 56 bytes in 3 blocks are definitely lost in loss record 25 of 85
==1842334==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1842334==    by 0x403368: sort_vars (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x403316: sort_each_proc (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x402FDB: handle_procs (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x402E0B: parse_tokens (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x402D1D: parse_input (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x40131D: run_minishell (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x4013CA: main (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334== 
==1842334== 389 (160 direct, 229 indirect) bytes in 2 blocks are definitely lost in loss record 35 of 85
==1842334==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1842334==    by 0x402E65: init_parser (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x402DA3: parse_tokens (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x402D1D: parse_input (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x40131D: run_minishell (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x4013CA: main (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334== 
==1842334== 13,198 (40 direct, 13,158 indirect) bytes in 1 blocks are definitely lost in loss record 84 of 85
==1842334==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1842334==    by 0x4044E0: env_lstnew (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x40478B: env_list (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x40130C: run_minishell (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334==    by 0x4013CA: main (in /home/dreijans/Documents/rank3/minishell/minishell)
==1842334== 
==1842334== LEAK SUMMARY:
==1842334==    definitely lost: 256 bytes in 6 blocks
==1842334==    indirectly lost: 13,387 bytes in 382 blocks
==1842334==      possibly lost: 0 bytes in 0 blocks
==1842334==    still reachable: 221,580 bytes in 598 blocks
==1842334==         suppressed: 0 bytes in 0 blocks
==1842334== Reachable blocks (those to which a pointer was found) are not shown.
==1842334== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==1842334== 
==1842334== For lists of detected and suppressed errors, rerun with: -s
==1842334== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
➜  minishell git:(djoyke) ✗ 