# KhiarWare(Windows Version) Wallhack Bhop TriggerBot
This project is an example of game hacking, and it's created to share the personal experiance with the other enthusiasts in this feild of software security.<br/>
This project is just for educational porpuses and i'm not responsible of any other subversive application of this.<br/>
As you know game hacking in online games is not allowed owing to annoying some other people. Normal players who want to just have fun with games and they don't want to face a demon hacker in their fun times, so game developers will response if you do somthing to annoy the other players or in other words Cheating in game by closeing your account(e.g VACation on steam platform).<br/>

If you want to run the codes above, compile them with visual studio(i used 2019 edition), and be careful, i don't garranty that you get banned or not. To be safe and run the game in insecure mode that turns off the anti-cheat when running the game, but you can't join to VAC secure servers on this mode.(search about "CS:GO insecure mode" to know how to run on this mode)<br/>

# How to user this code

First download the source code:
```console
foo@bar~:$ git clone https://github.com/mralinp/KhiarWare.git  
```

Then build an empty visual studio project and all of the source codes to the project. Now you are all set and press run/debug button to execute, enjoy!

> note: after any CS:GO update, the offset values will change, so you have to replace them with the new values to get this code running. Fresh offsets can be easily found on [hazedumper](https://github.com/frk1/hazedumper). download the `csgo.hpp` file from the [repo](https://github.com/frk1/hazedumper) and rename all `constexpr ::std::ptrdiff_t` with `const DWORD` then remove the parent namespace. Just Delete `namespace hazedumper {` and the last `}`. Finaly replace `#include <cstdint>` with `#include <windows.h>`, and rename the file into `Offsets.h`. Now you have a new `Offsets.h` file, replace it with the original one in the sorce code then run to project, ez. 

And an other thing you have to do before running the code is, replace all values in Offset.h file with the updated values (otherwise it would not work, becuase the addresses will be wrong).<br/>
You can find the updated values here: https://github.com/frk1/hazedumper
