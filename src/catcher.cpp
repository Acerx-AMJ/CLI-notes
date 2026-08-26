#include "catcher.hpp"

#include <iostream>

void Catcher::insert(const std::string& error)\
{
   errors.push_back(error);
}

bool Catcher::ok() const
{
   return errors.empty();
}

void Catcher::display()
{
   if (ok())
      return;
   
   std::cout << "\033[31m" << errors.size() << " Error(s) occurred:\033[0m\n";
   for (const auto& error : errors)
      std::cout << error << '\n';
   
   errors.clear();
}
