# KhiarWare(Windows Version)
## WallHack + TriggerBot + RadarHack + AutoBhop
This project is an example of game hacking, and it's created to share the personal experience with other enthusiasts in this branch of software security.<br/>
I made this only for educational porpuses and i'm not responsible for any other subversive applications.

As you might know, game hacking in online games is not allowed owing to annoying other players. Normal players who just want to have fun with games, don't want to face a demon hacker in their fun times, so game developers will respond if you do somthing to annoing to other players such as griffing as well as cheating (hacking) in game. In other words cheating in online games will cause your account be **banned** (e.g VACation on steam platform).

![menu image](demo.png)


To run and use the project, first, run the updater.py to update the offset addresses to the latest version of CS:GO using python3. After that use visual studio to build and run the source code.

> Note: To be safe while testing and running this code in game, just run the game in **insecure mode**. That turns off the Valve anti-cheat when running the game, but you can't join any VAC secure servers while launching the game on this mode. To do this just look at [Insecure Mode](#insecure-mode).

# How to use this code

First of all download the source codes:

```console
foo@bar~:$ git clone https://github.com/mralinp/KhiarWare.git  
```

Then run `updater.py`, this will automatically updates the offset values inside `Source/Offsets.h` file.
- You have to have python `requests` library installed in you python environment to be able to run `updater.py`.

```console
foo@bar~:$ pip install requests
foo@bar~:$ python updater.py
```

Finally, open the `khiar-ware/khiar-ware.sln` using visual sudio and press build/debug and enjoy.
> Before running the code make sure you are building for x86 instruction-set and not x64 because, csgo is a 32bit software and has 32bit addresses and offsets.


## Insecure Mode
### For those who doesn't want to risk and it's recommened by me.
To run this code to see how it's working without the rish of getting VAC banned, you have to run the game on `insecure` mode. To do this, open steam, go to library, `right-click` on **CS:GO** icon and choose properties, in `General` tab you can see `Launch options` button, click on that and add `-insecure` at the end of the line, done, press `ok` and close the propeties tab.

just remember that for playing normally after testing this code, just remove `-insecure` from `launch options`, this will enables anti-cheat and you are able to play at VAC secure servers.
If you saw that every thing is fine, and it's working good, you can use this code on `normal mode`, **competetive** or anywhere else, but at you own risk, be careful of being obvious and remember that overwatch is everywhere.

> Attention!: Due to CS:GO updates, this source code needs to be updated and adapted with the newest changes, but you can stiil use some parts as a sample of CS:GO cheat.
