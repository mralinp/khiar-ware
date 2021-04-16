# KhiarWare(Windows Version)
## WallHack + TriggerBot + RadarHack + AutoBhop
### Undetected
This project is an example of game hacking, and it's created to share the personal experience with other enthusiasts in this branch of software security.<br/>
This project is just for educational porpuses and i'm not responsible for any other subversive applications.<br/>
As you know game hacking in online games is not allowed owing to annoying some other people. Normal players who just want to have fun with games, don't want to face a demon hacker in their fun times, so game developers will respond if you do somthing to annoy other players. In other words cheating in online games will cause your account be **banned** (e.g VACation on steam platform).<br/>

![menu image](demo.png)


If you want to run the codes above, compile them with visual studio(i used 2019 edition), and be careful, i don't guarantee if you are getting banned or not. To be safe while testing and running this code in game, just run the game in **insecure mode**. That turns off the Valve anti-cheat when running the game, but you can't join any VAC secure servers while launching the game on this mode. To do this just look at [Insecure Mode](#insecure-mode).

# How to use this code

First of all download the source codes:

```console
foo@bar~:$ git clone https://github.com/mralinp/KhiarWare.git  
```

Then run `updater.py`, this will automatically update offset values into `Source/Offsets.h` file and you have to have `requests` library installed to run this as well:

```console
foo@bar~:$ pip install requests
foo@bar~:$ python updater.py
```

Finally create an empty visual studio project and add all of the source codes into the project (files with `.h` to `Headers` and the `.cpp` files into the `Sources`). Now you are all set, press `run/debug` button to execute, enjoy!


## Insecure Mode
### For those who doesn't want to risk and it's recommened by me.
To run this code to see how it's working without any rish of getting VAC banned, you have to run the game on `insecure` mode. 

To do this, open steam, go to library, `right-click` on **CS:GO** icon and choose properties, in  `General` tab you can see `Launch options` button, click on that and add `-insecure` at the end of the line, done, press `ok` and close the propeties tab.

just remember that for playing normally after testing this code, just remove `-insecure` from `launch options`, this will enables anti-cheat and you are able to play at VAC secure servers.

If you saw that every thing is fine, and it's working good, you can use this code on `normal mode`, **competetive** or anywhere else, but at you own risk, be careful of being obvious and remember that overwatch is everywhere.

> Attention!: Due to CS:GO updates, this source code needs to be updated and adapted with the newest changes, but you can stiil use some parts as a sample of CS:GO cheat.
