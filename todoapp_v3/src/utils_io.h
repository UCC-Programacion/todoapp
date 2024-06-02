#pragma once

#include <iostream>

namespace utils {

namespace io {
  // copied from
  // https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
  inline void ignoreLine()
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  inline int get_int(
    std::string label = "Enter an int value: ",
    std::string error_label = "Oops, that input is invalid.  Please try again.\n")
  {
    while (true) // Loop until user enters a valid input
    {
      std::cout << label;
      int x {};
      std::cin >> x;

      // Check for failed extraction
      if (!std::cin) // has a previous extraction failed?
      {
        // yep, so let's handle the failure
        std::cin.clear(); // put us back in 'normal' operation mode
        ignoreLine(); // and remove the bad input
        std::cout << error_label;
      } else {
        ignoreLine(); // remove any extraneous input
        return x;
      }
    }
  }
}

}
