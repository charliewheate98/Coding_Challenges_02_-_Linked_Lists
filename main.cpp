#include <iostream>
#include <map>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

// Node Structure and Print Function ///////////////
struct Node
{
    int key;
    Node* next;
};
Node* add(int data)
{
    Node* new_node = new Node;
    new_node->key = data;
    new_node->next = NULL;
    return new_node;
}
void PrintLinkedList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->key);
        head = head->next;
    }
}
////////////////////////////////////////////////////

//////////////////////////////////////////
// Remove Duplicates Challenge          // 
// ---------------------------------------
// Remove duplicates from a linked list //
//////////////////////////////////////////
void RemoveDups(Node* head)
{
    unordered_set<int> seen;

    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL)
    {
        if (seen.find(curr->key) != seen.end())
        {
            prev->next = curr->next;
            delete curr;
        }
        else
        {
            seen.insert(curr->key);
            prev = curr;
        }

        curr = prev->next;
    }
}

///////////////////////////////////////////////////
// Get Kth from Last Element in the linked list
//////////////////////////////////////////////////
void GetKthFromEnd(Node* head, int n)
{
    int len = 0;
    Node* temp = head;

    while (temp != NULL) {
        temp = temp->next;
        ++len;
    }

    temp = head;
    for (auto i = 1; i < len - n + 1; ++i)
        temp = temp->next;

    cout << temp->key << endl;
}

///////////////////////////////////
// Delete Middle Node Challenge
///////////////////////////////////
// Write an algorithm to delete a 
// node in the middle (i.e. any 
// node but the first and last
// not nessasarly the exact 
// middle)
///////////////////////////////////
// O(n)
void DeleteNode(Node* head, int key)
{
    Node* temp = head;
    Node* prev = NULL;

    if (key == head->key)
    {
        printf("Cannot Delete That Node!\n\n");
        return;
    }

    while (temp != NULL) {
        if (temp->next == NULL) {
            if (temp->key == key) {
                printf("Cannot Delete That Node!\n\n");
                break;
                return;
            }
        }

        if (temp->key == key) {
            prev->next = temp->next;
            delete(temp);
        }
        else {
            prev = temp;
        }
        temp = prev->next;
    }
}

//////////////////////////////////////////
// Partition linked list around value x
//////////////////////////////////////////
// partition a linked list so that all
// nodes less then x come before and all
// nodes greater or equal to come after
// (on the right partition)
//////////////////////////////////////////
// partition value = 3
// 1 2    [3]    7 
//////////////////////////////////////////
// T(n) : tight bound : average case
// O(n^2) : upper bound : worst case
void ParitionLinkedList(Node* head, int x)
{
    vector<int> v;

    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL) 
    {
        if (temp->key >= x) 
        {
            v.emplace_back(temp->key);
            prev->next = temp->next;
            delete temp;
        }
        else 
        {
            prev = temp;
        }

        temp = prev->next;
    }

    temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    for(auto i = 0; i < v.size(); ++i)
        temp->next = add(v[i]);
}

//////////////////////////////////////////////////////
// Sum Lists Challenge
//////////////////////////////////////////////////////
// Given 2 numbers represented by linked 
// lists, where each node contains a single
// digit. The digits are stored in reverse
// order.
// Write a function that adds the numbers
// and returns the sum as a linked list
//////////////////////////////////////////////////////
// example 
// --------
// (7 -> 2 -> 1) + (9 -> 5 -> 6) = 127 + 659 = 786
//////////////////////////////////////////////////////
Node* SumLists(Node* first, Node* second)
{
    Node* res = NULL;
    Node* temp = NULL, *prev = NULL;
    int carry = 0;
    int sum;

    while (first != NULL || second != NULL)
    {
        // calculate the sum adding the carry if there is one to add
        sum = carry + (first ? first->key : 0) + (second ? second->key : 0);
        // update carry for next calulation  
        carry = (sum >= 10) ? 1 : 0;
        // update sum if it is greater than 10  
        sum = sum % 10;

        temp = add(sum);

        if (res == NULL)
            res = temp;
        else
            prev->next = temp;

        prev = temp;

        if(first) 
            first = first->next;
        if(second) 
            second = second->next;
    }

    return res;
}

//////////////////////////////////////////////////////
// Check if Linked List is Palindrome
//////////////////////////////////////////////////////
bool isPalindrome(Node* head)
{
    Node* slow = head;
    stack<int> s;

    while (slow != nullptr) {
        s.push(slow->key);
        slow = slow->next;
    }

    while (head != nullptr) {
        int i = s.top();
        s.pop();

        if (head->key != i)
            return false;

        head = head->next;
    }

    return true;
}

// Left Rotation a List of Integers by K steps
void leftrotate(std::vector<int> nums, int k)
{
    std::reverse(nums.begin(), nums.end());
    std::reverse(nums.begin(), nums.begin() + k);
    std::reverse(nums.begin() + k, nums.end());

    for (auto i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
}

// O(n) | linear solution
Node* GetIntersectionNode(Node* headA, Node* headB)
{
    if (headA == nullptr || headB == nullptr)
        return nullptr;

    Node* p1 = headA;
    Node* p2 = headB;

    while (p1 != p2) 
    {
        if (p1->next == nullptr) {
            p1 = headB;
        }
        else {
            p1 = p1->next;
        }

        if (p2->next == nullptr) {
            p2 = headA;
        }
        else {
            p2 = p2->next;
        }
    }

    return p1;
}

// 4 5 6 2 8
// s f
// O(s + f) | linear
// Floyds Tourtoise and Hare Algorithm 
// (Also known as the runner technique)
bool IsCycle(Node* head) {
    if (head == nullptr)
        return false;

    Node* slow = head;
    Node* fast = head->next;

    while (slow != fast) {
        if (fast == nullptr || fast->next == nullptr) {
            return false;
        }

        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}

int main(int argc, char* argv[])
{
    Node* head = add(3);
    head->next = add(2); 
    head->next->next = add(0);
    head->next->next->next = add(4);

    Node* head2 = add(3);
    head2->next = add(4);
    head2->next->next = add(8);

    if (IsCycle(head)) {
        printf("TRUE");
    }
    else 
        printf("FALSE");


    //RemoveDups(head);
    //GetKthFromEnd(head, 2);
   // DeleteNode(head, 3);
    //ParitionLinkedList(head, 3);
    //Node* r = reverse(head);
    //PrintLinkedList(r);
    //if (isPalindrome(head))
    //    printf("True\n\n");
    //else 
    //    printf("False\n\n");

    system("pause");
    return EXIT_SUCCESS;
}
