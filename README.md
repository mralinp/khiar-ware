# KhiarWare(Windows Version) <under developement>
## Preface 
This is project is an example of game hacking, and it's created to share the personal experiance with the other enthusiasts in this feild of software security.<br/>
This project is just for educational porpuses and i'm not responsible of any other subversive application of this.<br/>
As you know game hacking in online games is not allowed owing to annoying some other people. Normal players who want to just have fun with games and they don't want to face a demon hacker in their fun times, so game developers will response if you do somthing to annoy the other players or in other words Cheating in game by closeing your account(e.g VACation on steam platform).<br/>

# Tutorial begins
## intro
In this project we are trying ro read and write a running process memory to accesss the willing outputs of the process. In this project we choose c++ programming language to do the magic so if you want to use this tutorial a brief background of c ++ is required. I'll explain my main approach (the main algorithm) in any part of the project. I used some methods from various c++ librarys that may some of you don't know what is that and how it works, so to make it clear to every one i brought a bunch a refrences to any kind of uncommon method that is used in each part, so read them to know much better. <br/>

Project contains some main parts and some plug-ins that could be added to have more fun.(e.g auto Auto-Bhop and TriggerBot scripts)
you can write your plug-ins and make your own custom cheat.

## The engine, Memory Manager class
This part is the base of the project, with this class we can read and write the process memory, so its
a kind of handle for the current process running on the target computer.<br/>
On windows we have Windows Application Program Interface (WinAPI), that allows us to have fun with
the running processes on the OS. This is a library implimented for Windows operating system to
allow us communicate with the operating system trough the c++ source code.<br/>
for more Information about WinAPI refer to: https://en.wikipedia.org/wiki/Windows_API
