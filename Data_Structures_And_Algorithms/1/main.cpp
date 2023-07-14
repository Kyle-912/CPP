#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

class Node {
public:
    int value;
    Node* next = nullptr;
    Node();
    Node(int value);
};

class LinkedList {
public:
    Node* head;
    LinkedList();
};
Node* insertEnd(Node* head, int key);

float interQuartile(Node* head);

int main() {
    LinkedList linkedList;
    linkedList.head = insertEnd(linkedList.head, 1);
    linkedList.head = insertEnd(linkedList.head, 8);
    linkedList.head = insertEnd(linkedList.head, 15);
    linkedList.head = insertEnd(linkedList.head, 43);
    linkedList.head = insertEnd(linkedList.head, 82);
    linkedList.head = insertEnd(linkedList.head, 101);
    linkedList.head = insertEnd(linkedList.head, 110);
    linkedList.head = insertEnd(linkedList.head, 2456);
    linkedList.head = insertEnd(linkedList.head, 55345);
    linkedList.head = insertEnd(linkedList.head, 137556);
    linkedList.head = insertEnd(linkedList.head, 137576);
    interQuartile(linkedList.head);
}

float interQuartile(Node* head) { //I know I'm losing 20 points for storing the values in a vector, I genuinely couldn't find the intended solution despite hours of tinkering
    float range = 0.0;
    float q1 = 0.0;
    float q3 = 0.0;
    Node* iterator = head;
    vector<int> vector;
    while (iterator != nullptr && iterator->next != nullptr) {
        vector.push_back(iterator->value);
        iterator = iterator->next;
    }
    vector.push_back(iterator->value);
    if ((vector.size() - 1) % 3 == 0 || (vector.size() - 1) % 5 == 0 || (vector.size() - 1) % 7 == 0 || (vector.size() - 1) % 11 == 0 || (vector.size() - 1) % 13 == 0 || (vector.size() - 1) % 17 == 0) {
        q1 = vector[vector.size() / 4];
        q3 = vector[vector.size() * 3 / 4];
    } else {
        q1 = (vector[round(vector.size() / 4.0)] + vector[round(vector.size() / 4.0) - 1]) / 2.0;
        q3 = (vector[round(vector.size() * 3 / 4.0)] + vector[round(vector.size() * 3 / 4.0) - 1]) / 2.0;
    }
    range = q3 - q1;
    return range;
}

Node* insertEnd(Node* head, int key)
{
    Node* temp = new Node();
    temp->value = key;
    if(head == nullptr)
        head = temp;
    else
    {
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    return head;
}

Node::Node(int value) {
    this->value = value;
    this->next = nullptr;
}

Node::Node(){
    this->value = 0;
    this->next = nullptr;
}

LinkedList::LinkedList() {
    head = nullptr;
}