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
    StackNode *top_node;
    int count;

public:
    play_history_stack(){
        top_node = nullptr;
        count = 0;
    }

    ~play_history_stack(){
        while(!isEmpty()){
            pop();
        }
    }

    // Call this whenever a song finishes playing
    void push(Song s){
        StackNode *new_node = new StackNode(s);
        new_node->next = top_node;
        top_node = new_node;
        count++;
    }

    // Call this for the "Previous Song" feature
    bool pop(){
        if(isEmpty()){
            return false;
        }
        StackNode *temp = top_node;
        top_node = top_node->next;
        delete temp;
        count--;
        return true;
    }

    // Peek at the most recently played song without removing it
    bool top(Song &result){
        if(isEmpty()){
            return false;
        }
        result = top_node->song;
        return true;
    }

    bool isEmpty(){
        return top_node == nullptr;
    }

    int size(){
        return count;
    }

    void printHistory(){
        std::cout << "Play History (most recent first):" << std::endl;
        StackNode *cur = top_node;
        while(cur != nullptr){
            std::cout << " - " << cur->song.name << " by " << cur->song.author << std::endl;
            cur = cur->next;
        }
    }
};
class play_up_next_queue{
    //chikheang
};
class playlist_linked_list{
    //sokheang
public:
    void printHello()
    {
        std::cout << "Hello" << std::endl;
        std::cout << "This is NGEP Project" << std::endl;
        
    }
};
