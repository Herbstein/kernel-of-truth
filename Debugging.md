Debugging
=========

Understandably, debugging a kernel is not exactly straightforwards at first.
How do you print to the terminal if you have no `printf`? 
How do you use a debugger on a kernel? I shall explain some useful debugging
techniques for my setup.


`printf` style debugging
----------------------
At present, printing values to the terminal isn`t very useful.
The addresses and structures you may want to examine may be difficult to
find during runtime. Also, presently the terminal driver is broken.
I welcome a pull request to fix this, and possibly a real implementation
of stdio. I swear I fixed this earlier, but I have more pressing concerns.
If you would like to print something to the terminal, include `kernel/kputs.h`
and use `kputs(char*)` just like `puts(char*)`.

Using QEMU and GDB
------------------------
We will start QEMU in debug mode so that it connects with GDB locally.
The easy way is just to run:  
`$ make start-debug`  
The kernel will not start until GDB tells it to.
Next open GDB in the repository root directory. You may see a message like this:  
	```warning: File "/home/ian/projects/truth/kernel-of-truth/.gdbinit" auto-loading has been declined by your 'auto-load safe-path' set to "$debugdir:$datadir/auto-load".
To enable execution of this file add
        add-auto-load-safe-path /home/<user>/<path>/<to>/kernel-of-truth/.gdbinit
line to your configuration file "/home/<user>/.gdbinit".
To completely disable this security protection add
        set auto-load safe-path /
line to your configuration file "/home/<user>/.gdbinit".
For more information about this security protection see the
"Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
        info "(gdb)Auto-loading safe path"
```
Do as the warning suggests and add that line line to `~/.gdbinit`, and restart GDB.
GDB will not accept connections to remote hosts (like qemu) without explicit 
authorization. After all, you wouldn`t want to download someone`s git repo and
immediately connect to some machine over the network?
Once GDB is configured you may use it as usual. Look at the man pages for QEMU and GDB for more information.

Getting register values and stack traces with QEMU
--------------------------------------------------
The simple way is just to run:  
`$ make start-log`  
This will log the state of the machine to the file `qemu.log`. 
Running this command multiple times will overwrite the log, so back it up if you want to compare different runs.
QEMU will terminate if the kernel crashes.
Again, consult your man pages for more info.

Inspect the assembly
-------------------
There comes a time when you have to roll up your sleeves and inspect
the assembly to tell what the hell is actually going on. You can do this with
GCC or `objdump`.
Invoking GCC with the `-S` option will generate AT&T syntax assembly for your reading pleasure.
Alternately, after compiling the executable, running:  
`$ objdump -d executableName`  
will spit out AT&T to stdout. I recommend piping it to less or redirecting it to a file.
