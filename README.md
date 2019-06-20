# HideIt
A Win32 application that allows the user to change transparency of a window or hide it entirely from both the task bar and desktop.

## Downloading and Installing
Simply go to releases and download the .exe file from there.
Source code may also be downloaded through releases.

HideIt uses Windows and its protocols to function, no additional files are necessary.

## Using the program
Upon launch, you will be greeted by a screen telling you how to see the different keybinds.
HideIt mainly uses the "|" key to operate, and uses other modifier keys such as SHIFT, CTRL and ALT to provide functionality.

Pressing `CTRL + SHIFT + I` opens a list of keybinds.

HideIt is also hidden from both the desktop and task bar, and only uses message boxes to "communicate", making it very discreet.

To close the program, use `CTRL + SHIFT + |`.

**NOTE:** The | key is NOT usable while this software is running.

### How does it work?
The program waits for the user to bind a handle to the application that will be manipulated.
This is done with the `CTRL + |` keybind.

Once a process is bound, you may use the other keybinds to manipulate the transparency or to toggle the visibility of the applciation.

If you bind a new process while the other one is manipulated, the manipulated one will reset, and you may manipulate the newly bound application.

## Use areas
The software may be useful for cases where you need to for example read and type at the same time without access to an additional monitor.
You may then lower the transparency of your text editor to be able to read at the same time.
It was mainly created for me to get a better grasp at the Win32 API.

I do NOT recommend using this software to cheat on tests, exams, etc. as it's still possible to find out you're using the software, by using task manager.
