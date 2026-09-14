#include <iostream>
#include <string>
using namespace std;
#ifndef CORE_FUNCTIONS_H
#define CORE_FUNCTIONS_H
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
    string name;
    string author;
    string file_path;
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
class playlist_linked_list
{
private:
    Node_Song *current;

public:
    playlist_linked_list();
    void add_song(string title, string author, string filePath);
    void play_next();
    void play_previous();
    void display_playlist();
};

#endif