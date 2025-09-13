#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
  ULListStr u;
  // push_back into empty ->new tail, then more 
  u.push_back("7");
  u.push_back("8");
  u.push_back("9");

  // push_front uses head room and allocates new head when needed 
  u.push_front("frontA");
  u.push_front("frontB");

  std::cout << "size = " << u.size() << "\n";
  std::cout << "front = " << u.front() << ", back = " << u.back() << "\n";

  // pop front / back
  u.pop_front();
  u.pop_back();

  std::cout << "size = " << u.size() << "\n";
  std::cout << "front = " << u.front() << ", back = " << u.back() << "\n";

  // Random-access using get / set 
  u.set(0, "X");
  std::cout << "get(0) = " << u.get(0) << "\n";

  return 0;
}