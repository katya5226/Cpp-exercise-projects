/*#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};

class SinglyLinkedList {
private:
    SinglyLinkedListNode* head, * tail;
public:
    SinglyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    SinglyLinkedListNode* getHead() {
        return head;
    }
    SinglyLinkedListNode* getTail() {
        return tail;
    }
    void createnode(int, SinglyLinkedListNode*);
    void display();
};

void SinglyLinkedList::createnode(int a, SinglyLinkedListNode* aNode) {
    SinglyLinkedListNode* temp = new SinglyLinkedListNode;
    temp->data = a;
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
    if (aNode != NULL) {
        tail->next = aNode;
    }
    else {
        tail->next = NULL;
    }
}

void SinglyLinkedList::display()
{
    SinglyLinkedListNode* temp = new SinglyLinkedListNode;
    temp = head;
    while (temp != NULL)
    {
        cout << temp->data << "\t";// << temp->next << "\n";
        temp = temp->next;
    }
}

bool has_cycle(SinglyLinkedListNode* head) {
    bool cyc = false;
    vector<SinglyLinkedListNode*> nodes;
    SinglyLinkedListNode* curr = head;
    while (curr->next != NULL && cyc == false) {
        nodes.push_back(curr);
        for (SinglyLinkedListNode* node : nodes) {
            cout << node->data << "\t" << node->next->data << "\n";
            if (node == curr->next) cyc = true;
        }
        curr = curr->next;
    }
    return cyc;
}

int main() {

    SinglyLinkedList myList;
    myList.createnode(1, NULL);
    myList.createnode(2, NULL);
    myList.createnode(3, NULL);
    myList.createnode(4, myList.getHead());

    bool res = has_cycle(myList.getHead());
    cout << "YES/NO: " << res;

    return 0;
}
*/