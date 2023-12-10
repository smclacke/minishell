------------------------------TO DO----------------------------

1) 

    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 

    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 

    handle exit codes

4) WAIT?

    minibleh:cat Makefile | grep pr | head -n 5 | cd file_not_exit
    minishell: cd: file_not_exit: No such file or directory
    cat: pr: No such file or directory
    cat: 5: No such file or directory
    cat: file_not_exit: No such file or directory
    head: cannot open 'file_not_exit' for reading: No such file or directory
    grep: 5: No such file or directory
    grep: file_not_exit: No such file or directory

    it should do just:

    bash: cd: file_not_exit: No such file or directory

5) WAIT?

    minibleh:cat Makefile | grep pr | head -n 5 | hello
    cat: pr: No such file or directory
    cat: 5: No such file or directory
    hello: command not found
    grep: 5: No such file or directory

    it should do:

    bash: hello: command not found

6) EXPORT OR EXPANDER

    export var=a
    export $var=test
    echo $var $a
    a test

7) EXPORT OR EXPANDER

    export var
    export var=test
    export
    var="test"

8) EXECUTE 

    bash does:

    dreijans@f0r1s11:~$ cat Makefile | cd file_not_exit
    bash: cd: file_not_exit: No such file or directory
    cat: Makefile: No such file or directory

    mine does:

    minibleh:cat Makefile | cd file_not_exit
    minishell: cd: file_not_exit: No such file or directory
    cat: file_not_exit: No such file or directory

9) NORM here-doc

10) PARSER is this me?
    ..
    bash: ..: command not found

    minibleh:..


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