//MusicPlayList Project
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include "core_functions.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
using namespace std;
namespace fs = std::filesystem;
class MelodyEngine{
private: 
    vector<Song>main_library;
    play_history_stack currentPlaylist;
    play_up_next_queue nextQueue;
    playlist_linked_list currentLLPlaylist;
    Node_Song *currentTrack;

    ma_engine audioengine;
    ma_sound currentSound;
    bool isSoundLoaded;

    // MelodyEngine() : isSoundLoaded(false) {
    //     ma_result result = ma_engine_init(NULL, &audioengine);
    //     if (result != MA_SUCCESS) {
    //         cout << "Failed to initialize miniaudio engine!" << endl;
    //     }
    // }

    // ~MelodyEngine() {
    //     if (isSoundLoaded) {
    //         ma_sound_uninit(&currentSound);
    //     }
    //     ma_engine_uninit(&audioengine);
    // }

    void playAudio (string const &filePath){
        //This condition is built in order to check whether the sound is currently loaded or not.
        //If it is not, we gotta stop it first.
        
        if(isSoundLoaded){
            ma_sound_stop(&currentSound);
            ma_sound_uninit(&currentSound);
            isSoundLoaded = false;
        }
        //This condition is built in order to check whether there is a filepath that is passed into the function or not
        //Or it will check out the file system in the folder whether it exists or not
        if(filePath.empty() || !fs::exists(filePath)){
            cout << "File not found!!!" << endl;
            return;
        }

        ma_result result = ma_sound_init_from_file(&audioengine, filePath.c_str(), 0, NULL, NULL, &currentSound);
        if(result != MA_SUCCESS){
            cout << "Failed to play!!!" << endl;
            return;
        }
        isSoundLoaded= true;
        ma_sound_start(&currentSound);

    }
public:
    MelodyEngine() : currentTrack(nullptr), isSoundLoaded(false) {
        ma_result result = ma_engine_init(NULL, &audioengine);
        if (result != MA_SUCCESS) {
            cout << "Failed to initialize miniaudio engine!" << endl;
        }
    }
    void loadSongsFromFiles(const string &folderPath){
        int id = 101;
        main_library.clear();
        if(!fs::exists(folderPath)){
            cout << "The folder does not exist!!!" << endl;
            return;
        }
        for(const auto& file: fs:: directory_iterator(folderPath)){
            string filetype = file.path().extension().string();
            if(filetype == ".wav"){
                Song song;
                song.id = id++;
                song.name = file.path().stem().string();
                song.author = "Default";
                song.file_path = file.path().string();
                main_library.push_back(song);
            }
        }
        if(main_library.empty()){
            cout << "No files in the folder that are compatible!!!" << endl;
        }else{
            cout << "The songs are put in the main library || it is successful!!!" << main_library.size() << "song(s) are/is added" << endl;
        }
    }
    void buildPlaylist(){
        currentLLPlaylist.clear_playlist();
        if(currentLLPlaylist.empty()){
            for(const auto& onesong: main_library){
                currentLLPlaylist.add_song(onesong);
            }
        }
        currentTrack = currentLLPlaylist.current;
    }
    //nuth
};
void interface(){
    cout << "=============================" << endl;
    cout << "        MelodyEngine" << endl;
    cout << "=============================" << endl;
    cout << endl;
    cout << "Options (1-7): " << endl;
    cout << "1. Play Previous" << endl;
    cout << "2. Play Next" << endl;
    cout << "3. Add songs to your playlist" << endl;
    cout << "4.Pause" << endl;
    cout << "5. Resume" << endl;
    cout << "6. Stop" << endl;
    cout << "7. Exit" << endl;
}
int main(){
    //interface nuth
    interface();
    // MelodyEngine engine;
    // engine.playAudio("songs/bluestory_vannda.wav");



    cout << "Playing Audio - Press Enter to exit..." << endl;
    cin.get();


    return 0;
}