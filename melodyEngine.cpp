//MusicPlayList Project
#include <iostream>
#include <string>
#include <cstdlib>
#include "core_functions.h"
class MelodyEngine{
    //nuth
};
int main(){
    //interface nuth
    playlist_linked_list playlist;

    playlist.add_song("Blinding Lights");
    playlist.add_song("Levitating");
    playlist.add_song("Good 4 U");

    playlist.display_playlist();

    playlist.play_next();
    playlist.play_previous();
    return 0;
}