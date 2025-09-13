/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include <iostream>
#include <vector>
#include <cstddef>
#include "split.h"

// Helpers
Node* makeList(const std::vector<int>& vals) {
  Node* head = nullptr;
  Node*tail = nullptr;
  for(int v : vals) {
    Node* n = new Node(v, nullptr);
    if(!head) head = tail = n;
    else { tail->next = n; tail = n;}
  }
  return head;
}

void printList(const char* name, Node* head) {
  std::cout << name << ": []";
  for (Node* cur = head; cur; cur = cur->next) {
    std::cout << cur->value;
    if(cur->next) std::cout << " -> ";
  }
  std::cout << "]\n";
}

void deleteList(Node* head) {
  while(head) {
    Node* nxt = head->next;
    delete head;
    head = nxt;
  }
}

void runCase(const std::vector<int>& input) {
  Node* in = makeList(input);
  Node* odds = nullptr;
  Node* evens = nullptr;

  std::cout << "\nInput ";
  printList("in", in);

  split(in, odds, evens);

  std::cout << "After split:\n";
  printList("odds ", odds);
  printList("evens", evens);
  std::cout << "in is " << (in == nullptr ? "NULL" : "NOT NULL") << "\n";

  deleteList(odds);
  deleteList(evens);
}

int main(int argc, char* argv[])
{
  std::cout << "Basic tests for split() \n";

  runCase({});
  runCase({2});
  runCase({1});
  runCase({7, 8});
  runCase({0, 11, 20});
  runCase({1, 3, 5, 7, 9, 11, 12});
  runCase({0, 5, 6, 7, 8, 10, 72, 256, 300, 9009, 1111});
  runCase({70, 128, 500, 722, 65536});
  runCase({3, 7, 13, 17, 19, 23, 29, 37});
  runCase({2, 2, 2});
  runCase({5, 6, 7, 8, 9, 10, 72, 256, 256, 1111, 1111, 1111, 9009});

  return 0;

}
