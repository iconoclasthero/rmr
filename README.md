This is just a scrpt to bring together `rm`, `rm -r <dir>`, and `rmdir` under one roof so that if you want to remove something, you don't have to worry about whether it is a file or a directory or an occupied directory.  

Obviously **this should be used with caution**.  

The rm command will prompt if more than 3 files will be removed or if removal will be done recursively, i.e., the -I flag is set for rm.  `$ rm --help` states that -I is intended to be "less intrusive than -i, while still giving protection against most mistakes."  Should you wish for the additional protection, modify all instances of `rm -I` for `rm -i` (or use the commands the regular way.)

Put this utility somewhere in your path, e.g., locally you can use ~/bin or if you want to use a system-wide location, /usr/local/sbin is a reasonable place that should automatically be in the path.
  
  
