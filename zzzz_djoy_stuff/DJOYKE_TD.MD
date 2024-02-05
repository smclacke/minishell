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