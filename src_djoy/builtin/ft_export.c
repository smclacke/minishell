/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 14:42:33 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/14 14:56:13 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node pointer to node in list given in the form of a string
 * @param env pointer to linked list
 * @brief export with no options
 * @todo first character cannot have a number but everything else can have
 * check export edge cases
 * remove line 33: when parsing parses cmd with string in one node
*/
void	ft_export(t_parser *node, t_env **env)
{
	char	*new_key;
	char	*new_value;
	t_env	*new_node;

	new_key = NULL;
	new_value = NULL;
	if (word_check(node) == 1)
		return ;
	node = node->next;
	if (ft_strchr(node->data_type->strs, '=') == 0)
		mini_error("strchr", errno);
	if (reassign_env(env, node, new_key, new_value) == 1)
		return ;
	get_key_value(node->data_type->strs, &new_key, &new_value);
	new_node = env_lstnew(new_key, new_value, node->data_type->strs);
	env_lstadd_back(env, new_node);
}

bool	reassign_env(t_env **env, t_parser *node, char *n_k, char *n_v)
{
	t_env	*head;

	head = *env;
	while (head)
	{
		if (mini_strcmp(node->data_type->strs, head->full) == 0)
		{
			head->full = node->data_type->strs;
			get_key_value(node->data_type->strs, &n_k, &n_v);
			head->value = n_v;
			head->key = n_k;
			return (true);
		}
		head = head->next;
	}
	return (false);
}

//unset everything and make sure the first nod is freed as well
//content needs to be freed
/*
➜  ~ bash
bash-3.2$ export
declare -x Apple_PubSub_Socket_Render="/private/tmp/com.apple.launchd.QRGzUMyyO3/Render"
declare -x COLORFGBG="7;0"
declare -x COLORTERM="truecolor"
declare -x COMMAND_MODE="unix2003"
declare -x DISPLAY="/private/tmp/com.apple.launchd.y0UhuGkD1c/org.xquartz:0"
declare -x HOME="/Users/dreijans"
declare -x HOMEBREW_CACHE="/tmp/dreijans/Homebrew/Caches"
declare -x HOMEBREW_TEMP="/tmp/dreijans/Homebrew/Temp"
declare -x ITERM_PROFILE="Default"
declare -x ITERM_SESSION_ID="w1t0p0:747A7864-04B8-4BD4-9393-CCF0D3CC0027"
declare -x LANG="en_US.UTF-8"
declare -x LC_TERMINAL="iTerm2"
declare -x LC_TERMINAL_VERSION="3.4.16"
declare -x LESS="-R"
declare -x LOGNAME="dreijans"
declare -x LSCOLORS="Gxfxcxdxbxegedabagacad"
declare -x LS_COLORS="di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43"
declare -x OLDPWD
declare -x PAGER="less"
declare -x PATH="/Users/dreijans/.brew/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin"
declare -x PWD="/Users/dreijans"
declare -x SECURITYSESSIONID="186a8"
declare -x SHELL="/bin/zsh"
declare -x SHLVL="2"
declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.GyohpGQNGj/Listeners"
declare -x TERM="xterm-256color"
declare -x TERM_PROGRAM="iTerm.app"
declare -x TERM_PROGRAM_VERSION="3.4.16"
declare -x TERM_SESSION_ID="w1t0p0:747A7864-04B8-4BD4-9393-CCF0D3CC0027"
declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n000dpyr003dqp/T/"
declare -x USER="dreijans"
declare -x XPC_FLAGS="0x0"
declare -x XPC_SERVICE_NAME="0"
declare -x ZSH="/Users/dreijans/.oh-my-zsh"
declare -x _="/bin/bash"
declare -x __CF_USER_TEXT_ENCODING="0x0:0:0"
bash-3.2$
-----------------------------------------------------------------------------------------------------------------------------------------------------------
bash-3.2$ export HOME
bash-3.2$ export
declare -x Apple_PubSub_Socket_Render="/private/tmp/com.apple.launchd.QRGzUMyyO3/Render"
declare -x COLORFGBG="7;0"
declare -x COLORTERM="truecolor"
declare -x COMMAND_MODE="unix2003"
declare -x DISPLAY="/private/tmp/com.apple.launchd.y0UhuGkD1c/org.xquartz:0"
declare -x HOME="/Users/dreijans"
declare -x HOMEBREW_CACHE="/tmp/dreijans/Homebrew/Caches"
declare -x HOMEBREW_TEMP="/tmp/dreijans/Homebrew/Temp"
declare -x ITERM_PROFILE="Default"
declare -x ITERM_SESSION_ID="w1t0p0:747A7864-04B8-4BD4-9393-CCF0D3CC0027"
declare -x LANG="en_US.UTF-8"
declare -x LC_TERMINAL="iTerm2"
declare -x LC_TERMINAL_VERSION="3.4.16"
declare -x LESS="-R"
declare -x LOGNAME="dreijans"
declare -x LSCOLORS="Gxfxcxdxbxegedabagacad"
declare -x LS_COLORS="di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43"
declare -x OLDPWD
declare -x PAGER="less"
declare -x PATH="/Users/dreijans/.brew/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin"
declare -x PWD="/Users/dreijans"
declare -x SECURITYSESSIONID="186a8"
declare -x SHELL="/bin/zsh"
declare -x SHLVL="2"
declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.GyohpGQNGj/Listeners"
declare -x TERM="xterm-256color"
declare -x TERM_PROGRAM="iTerm.app"
declare -x TERM_PROGRAM_VERSION="3.4.16"
declare -x TERM_SESSION_ID="w1t0p0:747A7864-04B8-4BD4-9393-CCF0D3CC0027"
declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n000dpyr003dqp/T/"
declare -x USER="dreijans"
declare -x XPC_FLAGS="0x0"
declare -x XPC_SERVICE_NAME="0"
declare -x ZSH="/Users/dreijans/.oh-my-zsh"
declare -x __CF_USER_TEXT_ENCODING="0x0:0:0"
bash-3.2$
*/