

1) echo not updated exit code
shitey shelly:$LESS$VAR
minishell: -R: command not found
shitey shelly:$
minishell: $: command not found
shitey shelly:echo $
$
shitey shelly:echo $?
127
shitey shelly:exit
exit

shitey shelly:echo $
$
shitey shelly:echo $?
0

2) hanging
echo blahblah >test

cd .. > test.txt