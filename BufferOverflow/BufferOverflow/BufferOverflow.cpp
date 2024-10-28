// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  variable, and its position in the declaration. It must always be directly before the variable used for input.
  //  You must notify the user if they entered too much data.


  const std::string account_number = "CharlieBrown42";
  char user_input[20];
  std::cout << "Enter a value: ";

  // User std::cin.getline to safely read input and prevent buffer overflow
  std::cin.getline(user_input, sizeof(user_input));

  if (std::cin.fail()) {
	  // If failbit is set, the input was too long
	  std::cin.clear(); // Clear the error state
	  // Discard the remaining characters in the input buffer
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  std::cout << "You entered too much data. Input truncated to " << (sizeof(user_input) - 1) << " characters." << std::endl;
  }

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
