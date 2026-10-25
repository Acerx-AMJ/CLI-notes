#include "commands.hpp"
#include <iostream>

int main()
{
   srand(time(nullptr));
   std::cout << "CLI note-taking application.\n";
   Catcher catcher;

   while (true)
   {
      std::cout << "> ";

      std::string command;
      std::getline(std::cin >> std::ws, command);

      handle_command(command, catcher);
      catcher.display();
   }
}