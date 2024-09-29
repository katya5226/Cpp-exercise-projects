/*#include <vector>
#include <string>
#include <iostream>

using namespace std;


 struct node {
      int data;
      node* next;
 };

 class list
 {
 private:
     node* head, * tail;
 public:
     list()
     {
         head = NULL;
         tail = NULL;
     }
     node* getHead() {
         return head;
     }
     void display();
     void createnode(int);
 };

 void displayReverse(node*);

node* reverse(node* head) {
    node* prev = NULL;
    node* curr = head;
    node* next = NULL;


    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void list::display()
{
    node* temp = new node;
    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << "\t";// << temp->next << "\n";
        temp = temp->next;
    }
}

void list::createnode(int value)
{
    node* temp = new node;
    temp->data = value;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }

}

void displayR(node* head) {
    node* temp = new node;
    temp = head;
    while (temp != NULL) {
        cout << temp->data << "\t";
        temp = temp->next;
    }
    delete temp;
}


int main() {

    list* myList = new list();
    myList->createnode(1);
    myList->createnode(2);
    myList->createnode(3);

    node* head = myList->getHead();


    node* newHead = reverse(head);
    displayR(newHead);

    delete myList;

	return 0;
}*/