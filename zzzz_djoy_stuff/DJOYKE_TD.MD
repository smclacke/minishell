------------------------------TO DO----------------------------

1) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 
    handle exit codes

6) PARSER is this me?
    ..
    bash: ..: command not found

    minibleh:..
	leaks many bites
==107406==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x49a28d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a28d)
    #1 0x4ce5c3 in mini_malloc /home/dreijans/Documents/rank3/minishell/src/utils/cleanup.c:103:9
    #2 0x4dfa19 in get_argv /home/dreijans/Documents/rank3/minishell/src/executor/utils.c:91:21
    #3 0x4ddcc5 in mini_forks /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:132:9
    #4 0x4e10ae in init_fork /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:63:3
    #5 0x4e1483 in pipeline /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:107:3
    #6 0x4de23e in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:154:2
    #7 0x4de1bd in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:179:2
    #8 0x4cb420 in run_minishell /home/dreijans/Documents/rank3/minishell/src/main.c:24:2
    #9 0x4cb52f in main /home/dreijans/Documents/rank3/minishell/src/main.c:49:8
    #10 0x7f0f3c53bd8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

7) ECHO??

    minibleh:< testfile.txt echo hi

    minibleh:echo < testfile.txt hi

    minibleh:

8) ERRORS TO STANDARD ERROR!

9) exit > hoi.txt is writing exit in the file

10) met t_execute struct pointer maar t_export en t_env maken zodat ik clean functie kan.

11) dumb input like this gives a segfault

	minibleh:$var=test

[0] cmd = $var=test

[0] str_count = 0

[0] hd_count = 0

[0] red_count = 0
--------------------------------------------------
minishell: a: command not found
executable = [a]

=================================================================
==110641==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 10 byte(s) in 1 object(s) allocated from:
    #0 0x49a28d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a28d)
    #1 0x4e3ed3 in ft_strdup (/home/dreijans/Documents/rank3/minishell/minishell+0x4e3ed3)
    #2 0x4d254c in handle_cmd /home/dreijans/Documents/rank3/minishell/src/parser/get_procs.c:85:14
    #3 0x4d2375 in get_strs /home/dreijans/Documents/rank3/minishell/src/parser/get_procs.c:107:4
    #4 0x4d11c7 in sort_vars /home/dreijans/Documents/rank3/minishell/src/parser/sort_procs.c:26:3
    #5 0x4d1026 in sort_each_proc /home/dreijans/Documents/rank3/minishell/src/parser/sort_procs.c:50:2
    #6 0x4d061f in handle_procs /home/dreijans/Documents/rank3/minishell/src/parser/parser.c:33:4
    #7 0x4cfda8 in parse_tokens /home/dreijans/Documents/rank3/minishell/src/parser/parser.c:79:16
    #8 0x4cfc6d in parse_input /home/dreijans/Documents/rank3/minishell/src/parser/parser.c:98:11
    #9 0x4cb3e5 in run_minishell /home/dreijans/Documents/rank3/minishell/src/main.c:20:10
    #10 0x4cb52f in main /home/dreijans/Documents/rank3/minishell/src/main.c:49:8
    #11 0x7f68bb559d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

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

REMEMBER! exit from parser when:
	- nothing after meta
	- unclosed quotes
	- pipe after pipe
	- malloc
	- if string doesnt come back exit