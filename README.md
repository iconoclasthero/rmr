This is just a scrpt to bring together `rm`, `rm -r <dir>`, and `rmdir` under one roof so that if you want to remove something, you don't have to worry about whether it is a file or a directory or an occupied directory.  

Obviously **this should be used with caution**.  

The rm command will prompt if more than 3 files will be removed or if removal will be done recursively, i.e., the -I flag is set for rm.  `$ rm --help` states that -I is intended to be "less intrusive than -i, while still giving protection against most mistakes."  Should you wish for the additional protection, modify all instances of `rm -I` for `rm -i` (or use the commands the regular way.)

Put this utility somewhere in your path, e.g., locally you can use ~/bin or if you want to use a system-wide location, /usr/local/sbin is a reasonable place that should automatically be in the path.

Sun May 19 01:59:56 PM EDT 2024

It now checks to see if at least some of the files are not writeable and escallates to sudo...the check for unwritaablity will probably need to be reviewed/refined, but there you go, at least there's something.

Mon May 20 06:19:09 AM EDT 2024

ChatGPT wrote it in c and, after a couple iterations, it compiled without error.  I assume it's broadly *nix compatable, not sure I trust something designed to delete stuff that was written by AI and not checked by anyone who knows any c.
