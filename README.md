# PreventTurnOffDisplay
Console-program that prevents the display from turning off for a specified time.

Run it from a cmd.exe with

```
MouseMover.exe 1800
```

The command-line-argument (in this example 1800) is the number of seconds, this
program will run.

At the beginning of the program a call to the Win32-API-function `SetThreadExecutionState`
is performed, informing "the system, that it is in use, thereby preventing the system 
from entering sleep or turning off the display while the application is running."

See [here](https://docs.microsoft.com/de-at/windows/win32/api/winbase/nf-winbase-setthreadexecutionstate)

Then the program just sleeps for the number of seconds given by the command-line-argument
( or for 3600 seconds = 1 hour, if no command-line-argument has been given). 

Before exiting the previus thread-execution-state is restored (which should be 
unnecessary, since the program and the thread are about to exit). So if the
program is "killed", for example by hitting CRTL+C, the display should blank and the
system should enter sleep mode in the normal way again.

