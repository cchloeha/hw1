/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
  if(in == nullptr) return;

  // Save current node and rest of list
  Node* curr = in;
  Node* rest = in->next;

  // Detach curr to prevent carrying old next pointers forward
  curr->next = nullptr;
  
  // Recurse on remainder first to preserve order on unwind
  split(rest, odds, evens);

  // Put curr in appropriate output list
  if((curr->value % 2) == 0) {
    curr->next = evens;
    evens = curr;
  } else {
    curr->next = odds;
    odds = curr;
  }

  // Original input list not preserved so set in to nullptr
  in = nullptr;
// WRITE YOUR CODE HERE
}

/* If you needed a helper function, write it here */
