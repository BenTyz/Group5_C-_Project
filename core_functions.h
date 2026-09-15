#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H

#include <iostream>
#include <string>
/*
In this header file, the thing that remain here are data type and class declaration as well,
like when ever you are establishing a class or a struct please put it here for example:
struct Node{
    Song s;
    Node* next;
    Node * prev;
};

and you don't have to give any definition in here but only declaration.
You can do more research on how this works
*/
struct Song{
    int id;
    std::string name;
    std::string author;
    std::string file_path;
};
struct Node_Song{
    Song song;
    Node_Song *prev;
    Node_Song *next;

    Node_Song(Song s):  song(s), prev(nullptr), next(nullptr) {}
};
struct StackNode{
    Song song;
    StackNode *next;
    
    StackNode(Song s): song(s), next(nullptr) {}
};
struct QueueNode{
    Song song;
    QueueNode *next;

    QueueNode(Song s): song(s), next(nullptr) {};
};

class play_history_stack{
    //ravin
private:
    StackNode *top_node;
    int count;

public:
    play_history_stack();
    ~play_history_stack();
    void push(Song s);
    Song pop(); 
    Song top(Song &result);
    bool isEmpty();
    int size();
    void printHistory();
};
class play_up_next_queue{
    //chikheang
private:
    QueueNode *front, *rear;
    int count;
public:
    play_up_next_queue();
    ~play_up_next_queue();
    void enqueue(Song s);
    Song dequeue();

    bool isEmpty();
};

class playlist_linked_list
{
public:
    Node_Song *current;
    playlist_linked_list();
    void add_song(Song song);
    void play_next();
    void play_previous();
    void display_playlist();
    void clear_playlist();
    bool empty();
};

#endif