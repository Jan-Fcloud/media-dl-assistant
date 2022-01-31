# youtube-dl-Assistant
This is a user friendly middleman for the youtube-dl.exe downloader.

youtube-dl-assistant is a personal project with the **main focus for me to practice C++** and for anyone that might need it along the way.

I'm making it open source for the obvious reason of guaranteeing that it only does what it says.

Please do keep in mind that I am by no means and standards a "good programmer" so I will be improving it with time once I find more efficient methods and such.


# Requirements: [youtube-dl.exe](https://github.com/ytdl-org/youtube-dl/releases/) and [youtube-dl-assistant.exe](https://github.com/Jan-Fcloud/youtube-dl-Assistant/releases)
Note: Without youtube-dl, my program is useless. The download will only be necesary once since my program runs an update on startup.

# Setup
The setup is simple with only 1 or 2 steps necessary.

Place the youtube-dl-assistant.exe and it's dlls in a folder of your choosing and place the downloaded youtube-exe beside it.

Your directory should pretty much look like this:
```
- <folder name>
  └ youtube-dl-assistant.exe
  └ youtube-dl.exe
  └ ...
```

# Auto generated files
The program itself will only generate 2-3 files, being **version.txt** on startup, which only contains the version of **youtube-dl** and **youtube-dl-assistant**, and if you'll be telling the program to create a config, it'll create 2 additional files being **config.cfg** and **temp.txt**(only necessary for the time being), both being required to run configs.

# Program config
As of **v1.2.0**, youtube-dl-assistant now makes it's own config and uses it for future program uses. It is not required but if you wish to create and use a config, visit the **advanced settings** after you set all your settings that you want youtube-dl-assistant to keep and remember. So the **config.cfg** checker finally has a use!

## Note
This program is by no means a modification of the youtube-dl.exe

It has been made for less tech savy people which prefeer a user experience instead of searching command line arguments and executing them everytime they would like to make a download of a link or playlist.

But please do keep in mind that **not all** functions of youtube-dl are supported by the assitant. I will keep on updating it, adding features that are **already supported** by the original program itself. 

So if you see anything missing from my assistant, please do check out the actual program and execute the following command line argument in the directory with youtube-dl in it:
```
.\youtube-dl.exe -help
```
Or directly check out their doccumentation on the link above.

# Planned features
My goal is to have a wide range of functions while still holding somewhat of a great user experience. Some of the features being, an auto updater, custom configs, quick website detection (so downloading from more than just youtube) and of course adding on things that are already supported by youtube-dl itself but don't exist on the assitant as a toggle.

I am also planning that I will at some point be doing a C# .net rewritte of the original program to give a great visual experience to people so we could get rid of the cmd aspect of it (the app would still have logs and a cmd viewer implemented to keep track of it's activities).
