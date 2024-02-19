------------------------------TO DO----------------------------

1) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) find solid evidence for allowing dprintf, if not just change it you lazy bum

3) handle exit codes

4) ERRORS TO STANDARD ERROR!

5) exit > hoi.txt is writing exit in the file

6) met t_execute struct pointer maar t_export en t_env maken zodat ik clean functie kan.

7) fix promt when ^C out of heredoc

bash:
➜  minishell git:(djoyke) ✗ bash
dreijans@f0r3s26:~/Documents/rank3/minishell$ cat << eof
> ^C
dreijans@f0r3s26:~/Documents/rank3/minishell$ << eof
> ^C
dreijans@f0r3s26:~/Documents/rank3/minishell$ ^C

minishell:
➜  minishell git:(djoyke) ✗ make run                    
minibleh:<< eof
heredoc> ^C

minibleh:<< eofminibleh:
minibleh:cat << eof
heredoc> ^C

minibleh:cat << eof
=================================================================
==83312==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 1 byte(s) in 1 object(s) allocated from:
    #0 0x49a28d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a28d)
    #1 0x7f8a59ffabac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

SUMMARY: AddressSanitizer: 1 byte(s) leaked in 1 allocation(s).

=================================================================
==83349==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 1 byte(s) in 1 object(s) allocated from:
    #0 0x49a28d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a28d)
    #1 0x7f8a59ffabac in xmalloc (/lib/x86_64-linux-gnu/libreadline.so.8+0x39bac)

SUMMARY: AddressSanitizer: 1 byte(s) leaked in 1 allocation(s).
minibleh:

**------------------ hello from sarah -------------------------**

heredoc still weird, two prompts with signal (ctrl c sws, not sure about the quite signal)

!!*we are not:*!!
- SHLVL
- export ls="ls -l"

REMEMBER! exit from parser when:
	- nothing after meta
	- unclosed quotes
	- pipe after pipe
	- malloc
	- if string doesnt come back exit