#include <iostream>
#include <vector>
#include "core_functions.h"
#include <cstdlib>
/*
This file only contains the class and core function of this playlist project which includes:
_Array (Dynamic Array / std::vector): Acts as the master library storing all available audio tracks in memory, allowing instant $O(1)$ lookup whenever a song ID is selected.
_Doubly Circular Linked List: Powers the core active playlist. Its forward (next) and backward (prev) pointers allow smooth navigation through songs without needing to re-index or shift elements.
_Queue: Manages the "Play Next" feature. When a user manually adds songs to a priority queue, they are played in strict First-In, First-Out order before resuming the regular playlist.
_Stack: Tracks play history for the "Previous Song" feature. Every time a song finishes, it gets pushed onto the stack; pressing "Previous" pops the top song, preserving correct back-navigation even during shuffle mode.

/*
 I will provide the class for you to modify and build the function and feel free to change something
 if you thing it is not correct.
*/
class play_history_stack{
    //ravin
};
class play_up_next_queue{
    //chikheang
};

// sokheang

struct Song{
    std :: string title;
    Song *next;
    Song *prev;
};
class playlist_linked_list{
   private:
       Song *current;
    public:
        playlist_linked_list(){
            current = nullptr;
        }
void add_song(std::string title){
    Song *new_song = new Song();
    new_song->title = title;
    if(current==nullptr){
        new_song->next = new_song;
        new_song->prev = new_song;
        current = new_song;
    }else{
        Song *last = current->prev;
        new_song->prev = last;
        new_song->next = current;
        current->prev = new_song;
    }
    std::cout << "Added: " << title << std::endl;
}
void play_next(){
    if(current==nullptr){
        std::cout << "This playlist is empty." << std::endl;
        return;
    }else{
        current = current->next;
        std::cout << "The next song is: " << current->title << std::endl;
    }
}
void play_previous()
{
    if (current == nullptr)
    {
        std::cout << "This playlist is empty." << std::endl;
        return;
    }
    else
    {
        current = current->prev;
        std::cout << "The previous song is: " << current->title << std::endl;
    }
}
void display_playlist(){
    if (current == nullptr)
    {
        std::cout << "This playlist is empty." << std::endl;
        return;
    }
    std::cout << "-----Playlist-----" << std::endl;
    Song *temp = current;
    do{
        std::cout << temp->title << std::endl;
        if(temp==current){
            std::cout << "Now playing" << std::endl;
        }
        temp = temp->next;
    } while (temp != current);
}
};
