#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val)
{
  // Allocate first node if list is empty
  if (tail_ == NULL) {
    tail_ = new Item();
    head_ = tail_;
  }

  // If there is no room at tail, allocate new tail node
  if (tail_->last == ARRSIZE) {
    Item* n = new Item();
    n->prev = tail_;
    tail_->next = n;
    tail_ = n;
  }

  // Write at current last then advance last
  tail_->val[tail_->last] = val;
  tail_->last += 1;
  size_ += 1;
}

void ULListStr::push_front(const std::string& val)
{
  // Allocate first node if list is empty
  if (head_ == NULL) {
    head_ = new Item();
    tail_ = head_;

    // Place at last slot so there is room before first 
    head_->first = ARRSIZE - 1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val;
    size_ += 1;
    return;
  }

  // If there is room before 'first' in head
  if (head_->first > 0) {
    head_->first -= 1;
    head_->val[head_->first] = val;
    size_ += 1;
    return;
  }

  // Otherwise need new head node 
  Item* n = new Item();
  n->next = head_;
  head_->prev = n;
  head_ = NULL;
  head_->first = ARRSIZE - 1;
  head_->last = ARRSIZE;
  head_->val[head_->first] = val;
  size_ += 1;
}

void ULListStr::pop_back()
{
  if (empty()) return;

  // Remove last element in the tail 
  tail_->last -= 1;
  size_ -= 1;

  // If node is now empty, delete
  if (tail_->first == tail_->last) {
    Item* prev = tail_->prev;
    delete tail_;
    tail_ = prev;

    if (tail_ == NULL) {
      // List now is empty
      head_ = NULL;
    } else {
      tail_->next = NULL;
    }
  }
}

void ULListStr::pop_front()
{
  if (empty()) return;

  // Advance 1st index
  head_->first += 1;
  size_ -= 1;

  // If node is empty, delete
  if (head_->first == head_->last) {
    Item* next = head_->next;
    delete head_;
    head_ = next;

    if(head_ == NULL) {
      // List is now empty
      tail_ = NULL;
    } else {
      head_->prev = NULL;
    }
  }
}

std::string const & ULListStr::back() const
{
  if (empty()) throw std::out_of_range("back() on empty ULListStr");
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if (empty()) throw std::out_of_range("front() on empty ULListStr");
  return head_->val[head_->first];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

std::string* ULListStr::getValAtLoc(size_t loc) const 
{
  if (loc >= size_) return NULL;

  Item* it = head_;
  // Num of logical elements
  size_t indexBase = 0;

  while (it != NULL) {
    // Elements in this node
    size_t used = it->last - it->first;
    if (loc <indexBase + used) {
      // Loc lies in this node
      size_t offset = loc - indexBase;
      size_t arrIdx = it->first + offset;
      return const_cast<std::string*>(&it->val[arrIdx]);
    }
    indexBase += used;
    it = it->next;
  }
  return NULL;
}