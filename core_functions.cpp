#include <iostream>
#include <vector>
#include "core_functions.h"
#include <cstdlib>
using namespace std;
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
    private:
    QueueNode* front;   
    QueueNode* rear;    
    int count;          

public:
    
    play_up_next_queue(){
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    
    bool isEmpty(){
        return front == nullptr;
    }

    
    void enqueue(Song s){
        QueueNode* newNode = new QueueNode(s); 
        if (isEmpty()){
            
            front = newNode;
            rear = newNode;
        } else {
            // Otherwise, link it after the current last node, then move "rear" to it
            rear->next = newNode;
            rear = newNode;
        }
        count++; 
    }

   
    Song dequeue(){
        if (isEmpty()){
            cout << "Up Next queue is empty!" << endl;
            return Song{"", "", ""}; 
        }

        QueueNode* temp = front;   
        Song playedSong = temp->song; 

        front = front->next; 
        if (front == nullptr){
            

            rear = nullptr;
        }

        delete temp; // Prevent memory leaks
        count--;     
        return playedSong;
    }

    
    Song peek(){
        if (isEmpty()){
            cout << "Up Next queue is empty!" << endl;
            return Song{"", "", ""};
        }
        return front->song;
    }

    int size(){
        return count;
    }


    void display(){
        if (isEmpty()){
            cout << "No songs in Up Next." << endl;
            return;
        }
        QueueNode* current = front; 
        int position = 1;
        cout << "----- Up Next -----" << endl;
        while (current != nullptr){
            cout << position << ". " << current->song.name
                 << " - " << current->song.author << endl;
            current = current->next; 
            position++;
        }
    }

    
    ~play_up_next_queue(){
        while (!isEmpty()){
            dequeue();
        }
    }
    //I didn't follow data stucture due to it's complicated to explain so I created another variable to navigate.
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
