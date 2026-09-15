
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
*/
 
// ---------------------------------------------------------------
// play_history_stack   //ravin
// NOTE: this class is only DECLARED in core_functions.h now.
// Defining it again as `class play_history_stack{ ... }` here (like the
// original file did) is a redefinition error, because the header already
// gives the compiler a full class definition. Member functions belong out
// here using the ClassName::method(...) syntax instead.
// ---------------------------------------------------------------
play_history_stack::play_history_stack(){
    top_node = nullptr;
    count = 0;
}
 
play_history_stack::~play_history_stack(){
    while(!isEmpty()){
        pop();
    }
}
 
// Call this whenever a song finishes playing
void play_history_stack::push(Song s){
    StackNode *new_node = new StackNode(s);
    new_node->next = top_node;
    top_node = new_node;
    count++;
}
 
// Call this for the "Previous Song" feature
Song play_history_stack::pop(){
    if(isEmpty()){
        cout << "The stack is empty!" << endl;
        return Song(); 
    }
    StackNode *temp = top_node;
    Song poppedsong = temp->song;
    top_node = top_node->next;
    delete temp;
    count--;
    return poppedsong;
}
 
// Peek at the most recently played song without removing it
Song play_history_stack::top(Song &result){
    if(isEmpty()){
        cout << "The stack is empty!" << endl;
        return Song(); 
    }
    result = top_node->song;
    return result;
}
 
bool play_history_stack::isEmpty(){
    return top_node == nullptr;
}
 
int play_history_stack::size(){
    return count;
}
 
void play_history_stack::printHistory(){
    std::cout << "Play History (most recent first):" << std::endl;
    StackNode *cur = top_node;
    while(cur != nullptr){
        std::cout << " - " << cur->song.name << " by " << cur->song.author << std::endl;
        cur = cur->next;
    }
}
 
// play_up_next_queue   //chikheang

play_up_next_queue::play_up_next_queue(): front(nullptr), rear(nullptr), count(0) {}
 
play_up_next_queue::~play_up_next_queue() {
    while (!isEmpty()) dequeue();
}
 
void play_up_next_queue::enqueue(Song s) {
    QueueNode* temp = new QueueNode(s);
    if (rear == nullptr) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
    count++;
}
 
Song play_up_next_queue::dequeue() {
    if (isEmpty()) return Song(); 
    QueueNode* temp = front;
    Song dequeuedSong = temp->song;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
    count--;
    return dequeuedSong;
}
 
bool play_up_next_queue::isEmpty() { return front == nullptr; }
 
// sokheang

playlist_linked_list::playlist_linked_list()
{
    current = nullptr;
}
void playlist_linked_list::add_song(Song song)
{
    Node_Song *new_song = new Node_Song(song);
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
    cout << "Added: " << song.name << endl;
}
 
void playlist_linked_list::play_next()
{
    if (current == nullptr)
    {
        cout << "This playlist is empty." << endl;
        return;
    }
    current = current->next;
    cout << "The next song is: " << current->song.name << endl;
}
 
void playlist_linked_list::play_previous()
{
    if (current == nullptr)
    {
        cout << "This playlist is empty." << endl;
        return;
    }
    current = current->prev;
    cout << "The previous song is: " << current->song.name << endl;
}
 
void playlist_linked_list::display_playlist()
{
    if (current == nullptr)
    {
        cout << "This playlist is empty." << endl;
        return;
    }
    cout << "-----Playlist-----" << endl;
    Node_Song *temp = current;
    do
    {
        cout << temp->song.name << endl;
        if (temp == current)
            cout << "Now playing" << endl;
        temp = temp->next;
    } while (temp != current);
}
 
void playlist_linked_list::clear_playlist()
{
    if (current == nullptr) return;
 
    Node_Song *head = current;
    Node_Song *temp = current;
 
    do {
        Node_Song *nextNode = temp->next;
        delete temp;
        temp = nextNode;
    } while (temp != head);
 
    current = nullptr;
}
 
bool playlist_linked_list::empty(){
    if(current == nullptr){
        return true;
    }
    return false;
}