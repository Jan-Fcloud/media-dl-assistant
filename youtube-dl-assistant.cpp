/// youtube-dl-assistant v1.2

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

/////////////////////////////////
/// DON'T FORGET VERSION PLS! ///
    string yddlav = "v1.2.0";
/// THANKS ME!                ///
/////////////////////////////////

bool loadedConfig = false;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void color(string tcolor);
bool cfgValues[] = {false,false,false,false,false,false,false,false,false,false,false};

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
    bool debug = false;
    bool rememberUse = false;
    bool debugMode = false;
    // List formats
    // login

}advSettings;

void mainSettings(int start);
void outputSettings();
void outputSettings(string setting, bool enabled);
void outputadvSettings();
void outputadvSettings(string setting, bool enabled);
void mainSettings();
void beginDownload();
void listSupported();
void startOtherDownload();
void loadConfig();
void writeConfig();

void setupEXE(){
    cout<<"Checking for update...";
    system("youtube-dl.exe --update > nul");
    cout<<"Done\n";
    system("youtube-dl.exe --version > .\\version.txt");

    cout<<"Checking for config...";
    try{

        bool yup = false;
        string temp;

        ifstream useConfig("temp.txt");
        if(useConfig.is_open() && useConfig.good()){
            getline(useConfig, temp);

            if(temp == "true"){
                yup = true;
            }

        }
        else{
            ofstream createTemp("temp.txt");
            createTemp<<"false";

            createTemp.close();
        }

        useConfig.close();

        ifstream downloadConfig("config.cfg");

        if(downloadConfig.is_open()){
            if(downloadConfig.good()){
                char agree;
                cout<<"Done\n"; color("green");
                cout<<"\nConfig found! Would you like to use it? Y or N\n"; color("white"); cout<<"Option: ";

                if(yup){
                    color("green"); cout<<"y (set by user config)\n";
                    color("white");

                    loadedConfig = true;
                    cout<<"Config will be used\n\n";
                    loadConfig();
                }
                else{
                    cin>>agree;
                    cin.ignore();

                    cout<<endl;

                    if(agree == 'y' || agree == 'Y'){
                        loadedConfig = true;
                        cout<<"Config will be used\n\n";
                        loadConfig();
                    }
                    else{
                        cout<<"Config will not be used\nApplying program defaults...\n\n";
                    }
                }

            }
        }
        else{
            cout<<"Done\n";
            color("red");
            cout<<"Config not found.\n\n";
            color("white");
        }
    }
    catch(...){
        cout<<"Done\n";
        cout<<"There was an error trying to open the config file.\nFile either can't be accessed or it doesn't exist.\n\n"<<endl;
    }

    /*
    color("yellow");
    cout<<"Note: Config not yet functional.\nChecker has been implemented for the future!"<<endl<<endl;
    */
    color("white");
}

void initializeEXE(){
    // Startup setup:
    setupEXE();

    bool yep = true;

    string versiontx;
    ifstream version("version.txt");
    getline(version, versiontx);
    version.close();

    string cmdTitle = "youtube-dl Assistant - v" + versiontx;
    SetConsoleTitleA(cmdTitle.c_str());
    cout<<"Input Supported URL: (type \"support\" to list all compatible links or \"help\" for all commands)"<<endl;
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
            cout<<"Downloading Twitch Clip/Stream..."<<endl;
            startOtherDownload();
            yep = false;
            }
         else if(settings.url.find("twitter") != string::npos){
            cout<<"Downloading Twitter Video..."<<endl;
            startOtherDownload();
            yep = false;
            }
        else if(settings.url.find("instagram") != string::npos){
            cout<<"Downloading Instagram Post..."<<endl;
            startOtherDownload();
            yep = false;
            }
        else if(settings.url.find("reddit") != string::npos){
            cout<<"Downloading Reddit Video..."<<endl;
            startOtherDownload();
            yep = false;
            }
         else if(settings.url.find("soundcloud") != string::npos){
            cout<<"Downloading SoundCloud song..."<<endl;
            startOtherDownload();
            yep = false;
            }
        else{
            system("cls");
            if(settings.url.find("version") != string::npos){
                cout<<"Current program versions:\n";
                color("green");
                cout<<"youtube-dl-assistant "<<yddlav<<endl;
                cout<<"youtube-dl v"<<versiontx<<endl;
                color("white");
            }
            else if(settings.url.find("support") != string::npos){
                listSupported();
                settings.url = "";
            }
            else if(settings.url.find("debug") != string::npos){
                advSettings.debugMode = true;
                outputSettings();
                yep = false;
            }
            else if(settings.url.find("help") != string::npos){
                cout<<"Current available commands:\n";
                cout<<"help - lists all available commands\n";
                cout<<"support - lists all yt-dl-assistant compatible links\n";
                cout<<"debug - activates debug mode for feature testing (not usable to normal users / doesn't download)\n";
                cout<<"version - shows current youtube-dl and youtube-dl-assistant versions\n";
            }
            else{
                cout<<"Given URL is not a valid or supported URL. Please try again."<<endl;
            }
            if(advSettings.debugMode == false){
               cout<<endl<<"Input Supported URL: "<<endl;
               getline(cin, settings.url);
            }

        }
    }while(yep);

    color("green");
    cout<<endl<<"The program has completed it's job."<<endl<<"Press ENTER to download another file!"<<endl;
    if(advSettings.debugMode == true){color("red"); cout<<"Debug mode disabled\n"; color("white"); advSettings.debugMode = false;}
    cin.get();
    cin.ignore();

    color("white");

    initializeEXE();

}

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

    //Start Program
    initializeEXE();

}

void outputSettings(){
    system("cls");
    if(advSettings.debugMode){
        color("red"); cout<<"!!!Debug mode!!!\n"; color("white");
    }
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
    if(advSettings.debugMode){
        color("red"); cout<<"!!!Debug mode!!!\n"; color("white");
    }
    cout<<"Advanced Settings:"<<endl;
    outputadvSettings("a) Overwrite Files", advSettings.overwrites);
    outputadvSettings("b) Output Description", advSettings.description);
    outputadvSettings("c) Output Metadata", advSettings.metadata);
    outputadvSettings("d) Use CMD tittle as Status", advSettings.tittleStatus);
    outputadvSettings("e) Use Config on startup", advSettings.rememberUse);
    cout<<endl;
    outputadvSettings("f) Enable DEBUG mode", advSettings.debug);
    cout<<"g) Write Config file"<<endl;

    // List unimplemented
    //cout<<"e) List all available formats = "; color("yellow"); cout<<"unimplemented"<<endl; color("white");
    cout<<"h) Login to Account = "; color("yellow"); cout<<"unimplemented"<<endl; color("white");

    cout<<endl<<"x) Back to Main Menu"<<endl;
    mainSettings();
}

void outputSettings(string setting, bool enabled){
    cout<<setting<<" = ";
    switch(enabled){
    case true:
        color("green");
        cout<<"true"<<endl;
        break;
    case false:
        color("red");
        cout<<"false"<<endl;
        break;
    }
    color("white");
}

void outputadvSettings(string setting, bool enabled){
    cout<<setting<<" = ";
    switch(enabled){
    case true:
        color("green");
        cout<<"true"<<endl;
        break;
    case false:
        color("red");
        cout<<"false"<<endl;
        break;
    }
    color("white");
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
        case 'e':{
            advSettings.rememberUse = !advSettings.rememberUse;
            outputadvSettings();
            break;
        }
        case 'f':{
            advSettings.debug = !advSettings.debug;
            outputadvSettings();
            break;
        }
        case 'g':{
            writeConfig();
            outputadvSettings();
            break;
        }
        case 'x':{
            outputSettings();
            break;
        }
        default:{
            color("red");
            cout<<endl<<"Command doesn't exist..."<<endl<<" Press ENTER to continue."<<endl;
            cin.ignore();
            cin.get();
            color("white");
            outputSettings();
        }
    }

}

void startOtherDownload(){
    string command = "youtube-dl.exe ";

    command += settings.url;

    /*////////////////////
    /// DEBUG SETTING  ///
    ////////////////////*/
    if(advSettings.debug){color("red");cout<<endl<<"Final Command: "<<command<<endl<<endl;color("white");cout<<endl; }
    /*/////////////////////
    // END DEBUG SETTING //
    /////////////////////*/

    system(command.c_str());
}

void beginDownload(){
    string command = "youtube-dl.exe ";
    if(settings.mp3){
        command += "--audio-format mp3 -x -f worstvideo+bestaudio/best ";
    }
    if(settings.mp4){
        command += "--format mp4 ";
    }
    if(settings.webm){
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


    /*////////////////////
    /// DEBUG SETTING  ///
    ////////////////////*/
    if(advSettings.debug){color("red");cout<<endl<<"Final Command: "<<command<<endl<<endl;color("white");cout<<endl; }
    /*/////////////////////
    // END DEBUG SETTING //
    /////////////////////*/

    if(advSettings.debugMode == false){
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

    /*
    debug=false
    mp3=true
    mp4=false
    thumbnail=true
    webm=false
    playlist=false
    overwrites=false
    description=false
    metadata=false
    tittleStatus=false
    */

    string cfgSettings[] = {
            "debug=","mp3=","mp4=",
            "thumbnail=","webm=",
            "playlist=","overwrites=",
            "description=","metadata=",
            "tittleStatus=",
            "alwaysUseConfig="
        };

    void loadConfig(){
        int itemp;
        string temp, temp2;

        ifstream downloadConfig("config.cfg");

        for(int i = 0; i<11; i++){
            if(downloadConfig.is_open()){
                if(downloadConfig.good()){
                    getline(downloadConfig, temp);
                    itemp = temp.find(cfgSettings[i]);
                    temp2 = temp.substr(itemp+(cfgSettings[i].size()));

                    if((temp.find("debug") != string::npos) && (temp.find("true") != string::npos)){
                        advSettings.debug = true;
                    }

                    if(temp2 == "true"){
                        cfgValues[i] = true;
                        color("red");
                    }
                    else{
                        cfgValues[i] = false;
                    }

                    /*////////////////////
                    /// DEBUG SETTING  ///
                    ////////////////////*/
                    if (advSettings.debug){
                        cout<<"Loop "<<i<<". "<<endl;
                        cout<<"Pulled: "<<temp<<" from -> config.cfg\n";
                        cout<<"Found bool value on position: "<<itemp+(cfgSettings[i].size())<<endl;
                        cout<<"Set cfgValues["<<i<<"] boolean to: ";

                        if(cfgValues[i] == true){
                            cout<<"true";
                        }
                        else{
                            cout<<"false";
                        }

                        cout<<endl<<endl;
                    }
                    /*/////////////////////
                    // END DEBUG SETTING //
                    /////////////////////*/




                }
            }
            else{
                color("red");
                cout<<"File not found/not open... (No permissions to read/write?) Aborting...\n";
                color("white");
                for(int j = 0; j<11; j++){
                    cfgValues[j] = false;
                }
                break;
            }
        }

        downloadConfig.close();


        advSettings.debug = cfgValues[0];
        settings.mp3 = cfgValues[1];
        settings.mp4 = cfgValues[2];
        settings.thumbnail = cfgValues[3];
        settings.webm = cfgValues[4];
        settings.playlist = cfgValues[5];
        advSettings.overwrites = cfgValues[6];
        advSettings.description = cfgValues[7];
        advSettings.metadata = cfgValues[8];
        advSettings.tittleStatus = cfgValues[9];
        advSettings.rememberUse = cfgValues[10];

        color("white");

    }

    void writeConfig(){

        cfgValues[0] = advSettings.debug;
        cfgValues[1] = settings.mp3; cfgValues[2] = settings.mp4;
        cfgValues[3] = settings.thumbnail; cfgValues[4] = settings.webm;
        cfgValues[5] = settings.playlist; cfgValues[6] = advSettings.overwrites;
        cfgValues[7] = advSettings.description; cfgValues[8] = advSettings.metadata;
        cfgValues[9] = advSettings.tittleStatus;
        cfgValues[10] = advSettings.rememberUse;


        ofstream writeTemp("temp.txt");

        if(advSettings.rememberUse == true){
            writeTemp<<"true";
            writeTemp.close();
            if(advSettings.debug){ // Debug start
                color("red");
                cout<<"rememberUse = true...\n";
                cout<<"Wrote \"true\" to -> temp.txt\n";
            } // Debug stop
        }
        else{
            writeTemp<<"false";
            writeTemp.close();

            if(advSettings.debug){ // Debug start
                color("red");
                cout<<"rememberUse = false...\n";
                cout<<"Wrote \"false\" to -> temp.txt\n";
            } // Debug stop

        }

        color("white");

        ofstream makeConfig("config.cfg");

        for(int i = 0; i<11; i++){
            string temp = "";
            temp += cfgSettings[i];

            if(cfgValues[i] == true){
                temp += "true";
            }
            else{
                temp += "false";
            }

            makeConfig<<temp;

            /*////////////////////
            /// DEBUG SETTING  ///
            ////////////////////*/
            if (advSettings.debug){
                color("red");
                cout<<"Wrote: "<<temp<<" to file -> config.cfg"<<endl;
                color("white");
            }
            /*/////////////////////
            // END DEBUG SETTING //
            /////////////////////*/

            makeConfig<<"\n";

        }

        color("green");
        cout<<"\nProgram finished writting config file! ENTER to continue...\n"<<endl;
        color("white");
        makeConfig.close();

        cin.get();
        cin.ignore();


    }
