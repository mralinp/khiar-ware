# KhiarWare(Windows Version)
## WallHack + TriggerBot + RadarHack + AutoBhop
### Undetected
This project is an example of game hacking, and it's created to share the personal experiance with the other enthusiasts in this feild of software security.<br/>
This project is just for educational porpuses and i'm not responsible of any other subversive application of this.<br/>
As you know game hacking in online games is not allowed owing to annoying some other people. Normal players who want to just have fun with games and they don't want to face a demon hacker in their fun times, so game developers will response if you do somthing to annoy the other players. In other words cheating in online game will cause your account be **banned** (e.g VACation on steam platform).<br/>

![menu image](demo.png)


If you want to run the codes above, compile them with visual studio(i used 2019 edition), and be careful, i don't garranty that you get banned or not. To be safe while testing and running this code in game, just run the game in **insecure mode**. That turns off the Vlave anti-cheat when running the game, but you can't join any VAC secure servers while lunching the game on this mode. To do this just look at [Insecure Mode](#insecure-mode).

# How to user this code

First download the source code:
```console
foo@bar~:$ git clone https://github.com/mralinp/KhiarWare.git  
```

Then build an empty visual studio project and all of the source codes to the project. Now you are all set, press `run/debug` button to execute, enjoy!

> note: after any CS:GO update, the offset values will change, so you have to replace them with the new values to get this code running. Fresh offsets can be easily found on [hazedumper](https://github.com/frk1/hazedumper). download the `csgo.hpp` file from this [repo](https://github.com/frk1/hazedumper) and rename all `constexpr ::std::ptrdiff_t` with `const DWORD` then remove the parent namespace. Just Delete `namespace hazedumper {` and the last `}`. Finaly replace `#include <cstdint>` with `#include <windows.h>`, and rename the file into `Offsets.h`. Now you have a new `Offsets.h` file, replace it with the original one in the sorce code then run to project, ez.

## Insecure Mode
### For those who doesn't want to risk and it's recommened by me.
To run this code to see how it's working without any rish of getting VAC banned, you have to run the game on `insecure` mode. 

To do this, open steam, go to library, `right-click` on **CS:GO** icon and choose properties, in  `General` tab you can see `Lunch options` button, click on that and add `-insecure` at the end of the line, done, press `ok` and close the propeties tab.

just remember that for playing normally after testing this code, just remove `-insecure` from `lunch options`, this will anables anti-cheat and you are able to play at VAC secure servers.

If you saw that every thing is fine, and it's working good, you can use this code on `normal mode`, **competetive** or anywhere else, but at you own risk, be careful of being obvious and remember that overwatch is everywhere.

> note: I will fix the offsets problem with an auto updater and add more features to this code, as soon as i have some free times. If you've seen any issues just tell me to fix them or if you have got any errors, just share it on issues list, Thank you!
