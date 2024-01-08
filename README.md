# Media DL Assistant
This is a user friendly middleman for the youtube-dl.exe downloader.

# Requirements: [youtube-dl.exe](https://github.com/ytdl-org/youtube-dl/releases/) and [youtube-dl-assistant.exe](https://github.com/Jan-Fcloud/media-dl-assistant/releases)
Note: Without youtube-dl, the assistant software won't be of much use. The download will only be necesary once since my program runs an update on startup.

# Setup
Setting up is very easy. Please head on over to the [wiki for instructions](https://github.com/Jan-Fcloud/media-dl-assistant/wiki/Quickstart-Guide#installation).

# Auto generated files
The program itself will only generate 2-3 files, being **version.txt** on startup, which only contains the version of **youtube-dl** and **youtube-dl-assistant**, and if you'll be telling the program to create a config, it'll create 2 additional files being **config.cfg** and **temp.txt**(only necessary for the time being), both being required to run configs.

# Program config
As of **v1.2.0**, Media DL Assistant now makes it's own config and uses it for future program uses. It is not required but if you wish to create and use a config, visit the **advanced settings** after you set all your settings that you want Media DL Assistant to keep and remember. So the **config.cfg** checker finally has a use!

## Note
This program is by no means a modification of the youtube-dl.exe

It has been made for less tech savy people which prefeer a user experience instead of searching command line arguments and executing them everytime they would like to make a download of a link or playlist.

But please do keep in mind that **not all** functions of youtube-dl are supported by the assitant. I will keep on updating it, adding features that are **already supported** by the original program itself. 

So if you see anything missing from my assistant, please do check out the actual program and execute the following command line argument in the directory with youtube-dl in it:
```
.\youtube-dl.exe -help
```
Or directly check out their documentation on the link above.

# Planned features
The course of Media DL Assistant has changed! It is highly recommended to visit the [Development Plans](https://github.com/users/Jan-Fcloud/projects/3) for more information.
