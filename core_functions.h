#include <iostream>
#include <string>
using namespace std;
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