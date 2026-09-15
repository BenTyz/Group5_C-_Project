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
    play_history_stack historySongs;
    play_up_next_queue nextQueue;
    playlist_linked_list currentLLPlaylist;
    Node_Song *currentTrack;
 
    ma_engine audioengine;
    ma_sound currentSound;
    bool isSoundLoaded;
 
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
 
    ~MelodyEngine(){
        if(isSoundLoaded){
            ma_sound_stop(&currentSound);
            ma_sound_uninit(&currentSound);
        }
        ma_engine_uninit(&audioengine);
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
        for(const auto& onesong: main_library){
            currentLLPlaylist.add_song(onesong);
        }
        currentTrack = currentLLPlaylist.current;
    }
 
    void displayLibrary(){
        if(main_library.empty()){
            cout << "The library is empty!!!" << endl;
            return;
        }
        cout << "-----Library-----" << endl;
        for(const auto &s : main_library){
            cout << "  [" << s.id << "] " << s.name << " - " << s.author << endl;
        }
    }
    void addToQueue(int id){
        for(const auto &s : main_library){
            if(s.id == id){
                nextQueue.enqueue(s);
                cout << "Added to Up Next: " << s.name << endl;
                return;
            }
        }
        cout << "No song with id " << id << " found in the library!!!" << endl;
    }
 
    void play_next_song(){
        // Priority 1: anything explicitly queued jumps the line, ahead of
        // the regular playlist order.
        if(!nextQueue.isEmpty()){
            if(currentTrack != nullptr){
                historySongs.push(currentTrack->song);
            }
            Song queuedSong = nextQueue.dequeue();
            cout << "[Audio] : Playing from queue: " << queuedSong.name << ": " << queuedSong.author << endl;
            playAudio(queuedSong.file_path);
            return; 
        }
 
        // Priority 2: regular playlist order.
        if(currentLLPlaylist.empty()){
            cout << "The playlist is empty!! No songs available!!!" << endl;
            return;
        }
        if(currentTrack != nullptr){
            historySongs.push(currentTrack->song);
        }
        currentLLPlaylist.play_next();
        currentTrack = currentLLPlaylist.current;
        if(currentTrack != nullptr){
            cout << "[Audio] : The song is playing: " << currentTrack->song.name << endl;
            playAudio(currentTrack->song.file_path); 
        }
    }
    void play_previous_song(){
        if(historySongs.isEmpty()){
            if(!currentLLPlaylist.empty()){
                currentLLPlaylist.play_previous();
                currentTrack = currentLLPlaylist.current;
                cout << "[Audio] : The song is playing (previous): " << currentTrack->song.name << endl;
                playAudio(currentTrack->song.file_path);
            }else{
                cout << "[Audio] No previous song available!!!" << endl;
            }
            return;
        }
        Song previous_song = historySongs.pop();

        if(!currentLLPlaylist.empty()){
            Node_Song *start = currentLLPlaylist.current;
            Node_Song *node = start;
            do{
                if(node->song.id == previous_song.id){
                    currentLLPlaylist.current = node;
                    break;
                }
                node = node->next;
            }while(node != start);
        }
        currentTrack = currentLLPlaylist.current;
 
        cout << "[Audio] : The song is playing (previous): " << previous_song.name<< endl;
        playAudio(previous_song.file_path);
    }
    void pause_song(){
        if(isSoundLoaded && ma_sound_is_playing(&currentSound)){
            ma_sound_stop(&currentSound);
            cout << "[Audio] The song is paused!!!" << endl;
        }else{
            cout << "[Audio] Nothing is currently playing!!!" << endl;
        }
    }
    void resume_song(){
        // Was: `if(isSoundLoaded || !ma_sound_is_playing(...))` which could
        // call ma_sound_start on a sound that was already playing.
        if(!isSoundLoaded){
            cout << "[Audio] Nothing to resume!!!" << endl;
            return;
        }
        if(!ma_sound_is_playing(&currentSound)){
            ma_sound_start(&currentSound);
            cout << "[Audio] The current song is resuming!!!" << endl;
        }else{
            cout << "[Audio] There is a song that is currently playing!!!" << endl;
        }
    }
    void stop_song(){
        if(isSoundLoaded && ma_sound_is_playing(&currentSound)){
            ma_sound_stop(&currentSound);
            ma_sound_seek_to_pcm_frame(&currentSound, 0);
            cout << "[Audio] The current song is stop playing!!!" << endl;
        }else{
            cout << "[Audio] There is no song that is currently playing right now!!!" << endl;
        }
    }
    //nuth
};
void displayUI(){
    cout << "=============================" << endl;
    cout << "        MelodyEngine" << endl;
    cout << "=============================" << endl;
    cout << endl;
    cout << "Options (1-9): " << endl;
    cout << "1. Play Next" << endl;
    cout << "2. Play Previous" << endl;
    cout << "3. Reload songs into your playlist" << endl;
    cout << "4. Pause" << endl;
    cout << "5. Resume" << endl;
    cout << "6. Stop" << endl;
    cout << "7. Show library (see song ids)" << endl;
    cout << "8. Add a song to Up Next queue" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose your option: ";
}
int main(){
    int choice;
    MelodyEngine engine;
    engine.loadSongsFromFiles("./songs");
    engine.buildPlaylist(); 
 
    bool running = true;
    while(running){ 
        displayUI();
        cin >> choice;
        cout << endl;
        switch (choice){
            case 1: engine.play_next_song(); break;
            case 2: engine.play_previous_song(); break;
            case 3: engine.buildPlaylist(); break;
            case 4: engine.pause_song(); break;
            case 5: engine.resume_song(); break;
            case 6: engine.stop_song(); break;
            case 7: engine.displayLibrary(); break;
            case 8: {
                int songId;
                cout << "Enter the id of the song to queue (see option 7 for ids): ";
                cin >> songId;
                engine.addToQueue(songId);
                break;
            }
            case 9: running = false; break;
            default: cout << "Invalid Input" << endl;
        }
        cout << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}
 