/// youtube-dl-assistant v1.1

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

bool loadedConfig = false;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(string tcolor);

struct settings{
    char option = '999';
    string url = "";
    bool mp3 = true;
    bool mp4 = false;
    bool thumbnail = true;
    bool webm = false;
    bool playlist = false;
    bool processed = false;
}settings;

struct advSettings{
    bool overwrites = true;
    bool description = false;
    bool metadata = false;
    bool tittleStatus = false;
    // List formats
    // login

}advSettings;

void setupEXE(){
    cout<<"Checking for update...";
    system("youtube-dl.exe --update > nul");
    cout<<"Done\n";
    system("youtube-dl.exe --version > .\\version.txt");

    cout<<"Checking for config...";
    try{
        ifstream downloadConfig("config.json");

        if(downloadConfig.is_open()){
            if(downloadConfig.good()){
                char agree;
                cout<<"Done\n";
                cout<<"Config found! Would you like to use it? Y or N";
                cin>>agree;
                cin.ignore();

                if(agree == 'y' || agree == 'Y'){
                    loadedConfig = true;
                    cout<<"Config will be used\n";
                }
                else{
                    cout<<"Config will not be used\n";
                }
            }
        }
        else{
            cout<<"Done\n";
            SetConsoleTextAttribute(hConsole, 4);
            cout<<"Config not found.\n\n";
            SetConsoleTextAttribute(hConsole, 7);
        }
    }
    catch(...){
        cout<<"Done\n";
        cout<<"There was an error trying to open the config file.\nFile either can't be accessed or it doesn't exist.\n\n"<<endl;
    }

    SetConsoleTextAttribute(hConsole, 6);
    cout<<"Note: Config not yet functional.\nChecker has been implemented for the future!"<<endl<<endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void mainSettings(int start);
void outputSettings();
void outputSettings(string setting, bool enabled);
void outputadvSettings();
void outputadvSettings(string setting, bool enabled);
void mainSettings();
void beginDownload();

void listSupported(){
    cout<<"Currently supported links:\n";
    cout<<"- YouTube "; color("yellow"); cout<<"(Age restricted unsupported)\n"; color("white");
    cout<<"- Twitch "; color("yellow"); cout<<"(Livestreams not functional in this version)\n"; color("white");
    cout<<"- Twitter\n";
    cout<<"- Instagram\n";
    cout<<"- Reddit\n";
    cout<<"- Soundcloud (Song and Playlists)\n";
}


int main(){
    // Startup setup:
    setupEXE();

    bool yep = true;

    string versiontx;
    ifstream version("version.txt");
    getline(version, versiontx);
    version.close();

    string cmdTitle = "youtube-dl Assistant - v" + versiontx;
    SetConsoleTitleA(cmdTitle.c_str());
    cout<<"Input Supported URL: (type \"support\" to list all compatible links)"<<endl;
    getline(cin, settings.url);

    do{
       if(settings.url.find("youtube.com") != string::npos){
            if(settings.url.find("playlist") != string::npos){
                settings.playlist = true;
            }
            yep = false;
            mainSettings(1);
        }
        else if(settings.url.find("twitch") != string::npos){
            beginDownload();
            yep = false;
            }
         else if(settings.url.find("twitter") != string::npos){
            beginDownload();
            yep = false;
            }
        else if(settings.url.find("instagram") != string::npos){
            beginDownload();
            yep = false;
            }
        else if(settings.url.find("reddit") != string::npos){
            beginDownload();
            yep = false;
            }
         else if(settings.url.find("soundcloud") != string::npos){
            beginDownload();
            yep = false;
            }
        else{
            system("cls");
            if(settings.url.find("support") != string::npos){
                listSupported();
                settings.url = "";
            }
            else{
                cout<<"Given URL is not a valid or supported URL. Please try again."<<endl;
            }
            cout<<endl<<"Input Supported URL: "<<endl;
            getline(cin, settings.url);
        }
    }while(yep);

    SetConsoleTextAttribute(hConsole, 2); // 4-red, 2-green, 7-white
    cout<<endl<<"The program has completed it's job."<<endl<<"Press ENTER to close."<<endl;
    cin.ignore();
    cin.get();

}

void outputSettings(){
    system("cls");
    cout<<"Fast Setup Settings:"<<endl;
    outputSettings("1) mp3", settings.mp3);
    outputSettings("2) mp4", settings.mp4);
    outputSettings("3) embed thumbnail", settings.thumbnail);
    outputSettings("4) webm", settings.webm);
    cout<<endl<<"5) Advanced Settings"<<endl;
    if(settings.playlist){
        cout<<"p) Playlist Settings - "; SetConsoleTextAttribute(hConsole, 6); cout<<"unimplemented"<<endl; SetConsoleTextAttribute(hConsole, 7);
    }
    cout<<"\n6) Start Download \n7) Cancel"<<endl;
    mainSettings();
}

void outputadvSettings(){
    system("cls");
    cout<<"Advanced Settings:"<<endl;
    outputadvSettings("a) Overwrite Files", advSettings.overwrites);
    outputadvSettings("b) Output Description", advSettings.description);
    outputadvSettings("c) Output Metadata", advSettings.metadata);
    outputadvSettings("d) Use CMD tittle as Status", advSettings.tittleStatus);

    // List unimplemented
    //cout<<"e) List all available formats = "; SetConsoleTextAttribute(hConsole, 6); cout<<"unimplemented"<<endl; SetConsoleTextAttribute(hConsole, 7);
    cout<<"e) Login to Account = "; SetConsoleTextAttribute(hConsole, 6); cout<<"unimplemented"<<endl; SetConsoleTextAttribute(hConsole, 7);

    cout<<endl<<"x) Back to Main Menu"<<endl;
    mainSettings();
}

void outputSettings(string setting, bool enabled){
    cout<<setting<<" = ";
    switch(enabled){
    case true:
        SetConsoleTextAttribute(hConsole, 2); // 4-red, 2-green, 7-white
        cout<<"true"<<endl;
        break;
    case false:
        SetConsoleTextAttribute(hConsole, 4); // 4-red, 2-green, 7-white
        cout<<"false"<<endl;
        break;
    }
    SetConsoleTextAttribute(hConsole, 7); // 4-red, 2-green, 7-white
}

void outputadvSettings(string setting, bool enabled){
    cout<<setting<<" = ";
    switch(enabled){
    case true:
        SetConsoleTextAttribute(hConsole, 2); // 4-red, 2-green, 7-white
        cout<<"true"<<endl;
        break;
    case false:
        SetConsoleTextAttribute(hConsole, 4); // 4-red, 2-green, 7-white
        cout<<"false"<<endl;
        break;
    }
    SetConsoleTextAttribute(hConsole, 7); // 4-red, 2-green, 7-white
}

void mainSettings(int start){
    outputSettings();
}

void mainSettings(){
    cout<<endl;
    cout<<"Choose an option: ";
    cin>>settings.option;

    /*////////////////////
    /// BASIC SETTINGS ///
    ////////////////////*/
    switch(settings.option){
        case '0':{
            outputSettings();
            break;
        }
        case '1':{
            settings.mp3 = !settings.mp3;
            if(settings.mp3){
                settings.mp4 = false;
                settings.webm = false;
            }
            outputSettings();
            break;
        }
        case '2':{
            settings.mp4 = !settings.mp4;
            if(settings.mp4){
                settings.mp3 = false;
                settings.webm = false;
            }
            outputSettings();
            break;
        }
        case '3':{
            settings.thumbnail = !settings.thumbnail;
            outputSettings();
            break;
        }
        case '4':{
            settings.webm = !settings.webm;
            if(settings.webm){
                settings.mp3 = false;
                settings.mp4 = false;
            }
            outputSettings();
            break;
        }
        case '5':{
            outputadvSettings();
            break;
        }
        case '6':{
            beginDownload();
            break;
        }
        case '7':{
            break;
        }
        case 'a':{
            advSettings.overwrites = !advSettings.overwrites;
            outputadvSettings();
            break;
        }
        case 'b':{
            advSettings.description = !advSettings.description;
            outputadvSettings();
            break;
        }
        case 'c':{
            advSettings.metadata = !advSettings.metadata;
            outputadvSettings();
            break;
        }
        case 'd':{
            advSettings.tittleStatus = !advSettings.tittleStatus;
            outputadvSettings();
            break;
        }
        case 'x':{
            outputSettings();
            break;
        }
        default:{
            SetConsoleTextAttribute(hConsole, 4); // 4-red, 2-green, 7-white
            cout<<endl<<"Command doesn't exist..."<<endl<<" Press ENTER to continue."<<endl;
            cin.ignore();
            cin.get();
            SetConsoleTextAttribute(hConsole, 7);
            outputSettings();
        }
    }

}



void beginDownload(){
    string command = "youtube-dl.exe ";
    if(settings.url.find("twitch") != string::npos){
        cout<<"Downloading Twitch clip..."<<endl<<endl;
        command += settings.url;
        system(command.c_str());
    }
    else{
    if(settings.mp3){
        command += "--audio-format mp3 -x ";
    }
    else if(settings.mp4){
        command += "--format mp4 ";
    }
    else if(settings.webm){
        command += "--format webm ";
    }
    if(settings.thumbnail){
        command += "--embed-thumbnail ";
    }
    if(settings.playlist){
        command += "--yes-playlist ";
    }
    if(advSettings.overwrites != true){
        command += "--no-overwrites ";
    }
    if(advSettings.description){
        command += "--write-description ";
    }
    if(advSettings.metadata){
        command += "--write-info-json ";
    }
    if(advSettings.tittleStatus){
        command += "--console-title ";
    }
    if(settings.playlist){
        command += "--yes-playlist ";
    }
    else{
        command += "--no-playlist ";
    }

    command += settings.url;
    //cout<<endl<<"Final Command: "<<command<<endl<<endl;
    cout<<endl;
    system(command.c_str());
    }
}

void color(string tcolor = "reset"){
    if(tcolor == "red")
        SetConsoleTextAttribute(hConsole, 4); // 4-red, 2-green, 7-white
    else if(tcolor == "green")
        SetConsoleTextAttribute(hConsole, 2);
    else if(tcolor == "white")
        SetConsoleTextAttribute(hConsole, 7);
    else if(tcolor == "yellow")
        SetConsoleTextAttribute(hConsole, 6);
    else
        SetConsoleTextAttribute(hConsole, 7);
    }
