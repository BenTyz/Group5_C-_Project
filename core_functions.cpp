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

// sokheang
// NOTE: Do NOT redefine struct Song here — it already exists in core_functions.h
// Use the Node_Song struct your teammate built in the header instead.

playlist_linked_list::playlist_linked_list()
{
    current = nullptr;
}

void playlist_linked_list::add_song(std::string title)
{
    Node_Song *new_song = new Node_Song(Song{title, "", ""});
    if (current == nullptr)
    {
        new_song->next = new_song;
        new_song->prev = new_song;
        current = new_song;
    }
    else
    {
        Node_Song *last = current->prev;
        last->next = new_song;
        new_song->prev = last;
        new_song->next = current;
        current->prev = new_song;
    }
    std::cout << "Added: " << title << std::endl;
}

void playlist_linked_list::play_next()
{
    if (current == nullptr)
    {
        std::cout << "This playlist is empty." << std::endl;
        return;
    }
    current = current->next;
    std::cout << "The next song is: " << current->song.name << std::endl;
}

void playlist_linked_list::play_previous()
{
    if (current == nullptr)
    {
        std::cout << "This playlist is empty." << std::endl;
        return;
    }
    current = current->prev;
    std::cout << "The previous song is: " << current->song.name << std::endl;
}

void playlist_linked_list::display_playlist()
{
    if (current == nullptr)
    {
        std::cout << "This playlist is empty." << std::endl;
        return;
    }
    std::cout << "-----Playlist-----" << std::endl;
    Node_Song *temp = current;
    do
    {
        std::cout << temp->song.name << std::endl;
        if (temp == current)
            std::cout << "Now playing" << std::endl;
        temp = temp->next;
    } while (temp != current);
}
