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


dreijans@f0r3s19:~/Documents/rank3/minishell/test$ ls
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ touch t1 t2 t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ chmod 000 t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile > t1 > t2
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile > t1 > t2 > t3
bash: t3: Permission denied
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile > t^C
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ rm t*
rm: remove write-protected regular empty file 't3'? y
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ ls
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile > t1 > t2 > t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ ls
t1  t2  t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ rm t*
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ chmod 000 t3
chmod: cannot access 't3': No such file or directory
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ touch t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ chmod 000 t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile > t3 > t2 > t1
bash: t3: Permission denied
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ ls
t3
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ cat ../Makefile >>t4 >>t5  > t3 > t2 > t
1
bash: t3: Permission denied
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ ls
t3  t4  t5
dreijans@f0r3s19:~/Documents/rank3/minishell/test$ 

linked list met de meta en filename in volgorde. 