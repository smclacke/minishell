-----------------------SARAH UPDATE------------------------------

1) 
    Avoid using more than one global variable to indicate a received signal. Consider
    the implications: this approach ensures that your signal handler will not access your
    main data structures.
    Be carefull. This global variable cannot provide any other
    information or data access than the number of a received signal.
    Therefore it is forbidden to use "norm" type structures in global.

    we need to have a part in our linked list that keeps our exit codes. because we cant use the global for these.

    typedef struct s_parser
    {
        void				*input;
        char				*cmd;
        char				*meta;
        char				*file;
        char				*str;
        int					n_cmd;
        --->// int					exit_code 
        --->// this will be updated after each process will happen automatically
        struct s_parser		*next;
    }				t_parser;

------------------------------TO DO----------------------------

1) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 
    handle exit codes

4) 

 ---> Made!
minibleh:export | export
||
index = [0], cmd = [export]
index = [0], str = [(null)]
index = [0], meta = [(null)]
next node
||
index = [1], cmd = [(null)]
index = [1], str = [(null)]
index = [1], meta = [|]
next node
||
index = [2], cmd = [export]
index = [2], str = [(null)]
index = [2], meta = [(null)]
next node
NULL
AddressSanitizer:DEADLYSIGNAL
=================================================================
==1021476==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0000004dd019 bp 0x7ffce0422900 sp 0x7ffce0422900 T0)
==1021476==The signal is caused by a READ memory access.
==1021476==Hint: address points to the zero page.
declare -x GDK_BACKEND="x11"
declare -x SSH_AGENT_LAUNCHER="gnome-keyring"
declare -x GJS_DEBUG_OUTPUT="stderr"
declare -x MANDATORY_PATH="/usr/share/gconf/ubuntu.mandatory.path"
declare -x LIBVIRT_DEFAULT_URI="qemu:///system"
declare -x GDM_LANG="en"
declare -x VSCODE_INJECTION="1"
declare -x QT_ACCESSIBILITY="1"
declare -x VSCODE_GIT_ASKPASS_EXTRA_ARGS="--ms-enable-electron-run-as-node"
declare -x PWD="/home/dreijans/Documents/rank3/minishell"
declare -x LSCOLORS="Gxfxcxdxbxegedabagacad"
declare -x XDG_DATA_DIRS="/usr/share/ubuntu:/usr/share/gnome:/home/dreijans/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop"
declare -x OLDPWD="/home/dreijans/Documents/rank3/minishell"
declare -x XDG_SESSION_PATH="/org/freedesktop/DisplayManager/Session60"
declare -x LANG="en_US.UTF-8"
declare -x XAUTHORITY="/home/dreijans/.Xauthority"
declare -x MAKEFLAGS=" --no-print-directory"
declare -x MFLAGS="--no-print-directory"
declare -x SSH_AUTH_SOCK="/run/user/112374/keyring/ssh"
declare -x XDG_CONFIG_DIRS="/etc/xdg/xdg-ubuntu:/etc/xdg"
declare -x GIT_ASKPASS="/usr/share/code/resources/app/extensions/git/dist/askpass.sh"
declare -x ZDOTDIR="/home/dreijans"
declare -x XDG_SESSION_DESKTOP="ubuntu"
declare -x ZSH="/home/dreijans/.oh-my-zsh"
declare -x KRB5CCNAME="FILE:/tmp/krb5cc_112374_50wzUE"
declare -x XDG_SESSION_TYPE="x11"
declare -x SESSION_MANAGER="local/f0r1s4.codam.nl:@/tmp/.ICE-unix/1016163,unix/f0r1s4.codam.nl:/tmp/.ICE-unix/1016163"
declare -x CHROME_DESKTOP="code-url-handler.desktop"
declare -x DBUS_SESSION_BUS_ADDRESS="unix:path=/run/user/112374/bus"
declare -x GNOME_DESKTOP_SESSION_ID="this-is-deprecated"
declare -x SHELL="/bin/zsh"
declare -x XMODIFIERS="@im=ibus"
declare -x DOTNET_BUNDLE_EXTRACT_BASE_DIR="/home/dreijans/.cache/dotnet_bundle_extract"
declare -x GJS_DEBUG_TOPICS="JS ERROR;JS LOG"
declare -x SHLVL="1"
declare -x PATH="/home/dreijans/bin:/home/dreijans/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/dreijans/.dotnet/tools"
declare -x VSCODE_GIT_IPC_HANDLE="/run/user/112374/vscode-git-499b890c1f.sock"
declare -x LANGUAGE="en"
declare -x VSCODE_GIT_ASKPASS_NODE="/usr/share/code/code"
declare -x VSCODE_GIT_ASKPASS_MAIN="/usr/share/code/resources/app/extensions/git/dist/askpass-main.js"
declare -x INVOCATION_ID="39162cfe16df4e9597d6dbb3c452acd6"
declare -x TERM_PROGRAM="vscode"
declare -x DOCKER_HOST="unix:///run/user/112374/docker.sock"
declare -x GTK_IM_MODULE="ibus"
declare -x XDG_CURRENT_DESKTOP="Unity"
declare -x LS_COLORS="rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:"
declare -x XDG_SEAT_PATH="/org/freedesktop/DisplayManager/Seat0"
declare -x DESKTOP_SESSION="ubuntu"
declare -x LESS="-R"
declare -x ORIGINAL_XDG_CURRENT_DESKTOP="ubuntu:GNOME"
declare -x LOGNAME="dreijans"
declare -x USER_ZDOTDIR="/home/dreijans"
declare -x GIO_LAUNCHED_DESKTOP_FILE="/usr/share/applications/code.desktop"
declare -x SYSTEMD_EXEC_PID="1016182"
declare -x DISPLAY=":0"
declare -x USER="dreijans"
declare -x GTK_MODULES="gail:atk-bridge"
declare -x DEFAULTS_PATH="/usr/share/gconf/ubuntu.default.path"
declare -x MANAGERPID="1015639"
declare -x GIO_LAUNCHED_DESKTOP_FILE_PID="1016726"
declare -x PAGER="less"
declare -x _="/usr/bin/make"
declare -x MAKE_TERMOUT="/dev/pts/0"
declare -x XDG_RUNTIME_DIR="/run/user/112374"
declare -x GPG_AGENT_INFO="/run/user/112374/gnupg/S.gpg-agent:0:1"
declare -x COLORTERM="truecolor"
declare -x JOURNAL_STREAM="8:10713087"
declare -x MAKE_TERMERR="/dev/pts/0"
declare -x XDG_SESSION_CLASS="user"
declare -x HOME="/home/dreijans"
declare -x QT_IM_MODULE="ibus"
declare -x TERM="xterm-256color"
declare -x XDG_GREETER_DATA_DIR="/var/lib/lightdm-data/dreijans"
declare -x XDG_MENU_PREFIX="gnome-"
declare -x TERM_PROGRAM_VERSION="1.84.2"
declare -x GDMSESSION="ubuntu"
declare -x MAKELEVEL="1"
    #0 0x4dd019 in ft_strlen (/home/dreijans/Documents/rank3/minishell/minishell+0x4dd019)
    #1 0x4ddc84 in ft_putstr_fd (/home/dreijans/Documents/rank3/minishell/minishell+0x4ddc84)
    #2 0x4d5506 in put_custom_error /home/dreijans/Documents/rank3/minishell/src/builtin/errors.c:27:3
    #3 0x4d4bc4 in space_check /home/dreijans/Documents/rank3/minishell/src/builtin/export.c:27:3
    #4 0x4d48f6 in ft_export /home/dreijans/Documents/rank3/minishell/src/builtin/export.c:121:6
    #5 0x4d5aa6 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:44:3
    #6 0x4d6e3c in mini_forks /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:99:3
    #7 0x4d8dc3 in init_fork /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:56:3
    #8 0x4d90ad in pipeline /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:100:4
    #9 0x4d751f in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:130:2
    #10 0x4d7452 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #11 0x4cb680 in main /home/dreijans/Documents/rank3/minishell/src/main.c:86:3
    #12 0x7f499978ed8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #13 0x7f499978ee3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #14 0x41f3e4 in _start (/home/dreijans/Documents/rank3/minishell/minishell+0x41f3e4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/home/dreijans/Documents/rank3/minishell/minishell+0x4dd019) in ft_strlen
==1021476==ABORTING
minibleh:^C