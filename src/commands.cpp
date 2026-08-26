#include "commands.hpp"

#include "helper.hpp"
#include <chrono>
#include <iostream>

void handle_command(const std::string& command, Catcher& catcher)
{
   if (command == "help")
      handle_help();
   else if (command == "new")
      handle_new(catcher);
   else if (command == "edit")
      handle_edit(catcher);
   else if (command == "cat")
      handle_cat(catcher);
   else if (command == "list")
      handle_list(catcher);
   else if (command == "blist")
      handle_blist(catcher);
   else if (command == "rlist")
      handle_rlist(catcher);
   else if (command == "get")
      handle_get(catcher);
   else if (command == "search")
      handle_search(catcher);
   else if (command == "delete")
      handle_delete(catcher);
   else if (command == "count")
      handle_count(catcher);
   else if (command == "quit")
      handle_quit();
   else if (command == "encrypt")
   {
      std::string thing;
      std::getline(std::cin >> std::ws, thing);
      std::cout << "'" << encrypt(thing) << "'" << '\n';
   }
   else if (command == "decrypt")
   {
      std::string thing;
      std::getline(std::cin >> std::ws, thing);
      std::cout << "'" << decrypt(thing) << "'" << '\n';
   }
   else
      handle_invalid_command(catcher);
}

void handle_help()
{
   Blue _;
   std::cout << "\nCommands:\n";
   std::cout << "help     display all commands.\n";
   std::cout << "new      add a new note.\n";
   std::cout << "edit     edit a specific note.\n";
   std::cout << "cat      list encrypted notes.\n";
   std::cout << "list     list all notes.\n";
   std::cout << "blist    list all notes in a reverse order.\n";
   std::cout << "rlist    list all notes in a random order.\n";
   std::cout << "get      get a specific note.\n";
   std::cout << "search   search all notes.\n";
   std::cout << "delete   delete a specific note.\n";
   std::cout << "count    count the amount of notes.\n";
   std::cout << "quit     quit the REPL.\n\n";
}

void handle_new(Catcher& catcher)
{
   Blue _;
   std::cout << "\nWrite a note:\n";
   _.reset();

   std::string note;
   std::getline(std::cin >> std::ws, note);

   auto now = std::chrono::system_clock::now();
   std::time_t time = std::chrono::system_clock::to_time_t(now);
   std::string date = std::ctime(&time);
   date.pop_back();

   std::fstream file ("note.txt", std::ios::app);
   if (!is_file_valid(file, catcher))
      return;

   file << encrypt(date + " - "s + note) << '\n';

   Green _g;
   std::cout << "\nSuccessfully wrote a new note!\n";
}

void handle_edit(Catcher& catcher)
{
   Blue _;
   size_t index = get_note_index("\nInput index of the note to edit: "s, catcher);
   _.reset();

   if (!catcher.ok())
      return;

   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;

   size_t it = 0;
   std::string line, original;
   std::vector<std::string> lines;

   while (std::getline(file, line))
   {
      if (index == ++it)
      {
         original = decrypt(line);

         Blue _;
         std::cout << "\nOriginal note: '" << original << "'.\n";
         std::cout << "Write note:\n";
         _.reset();

         std::string note;
         std::getline(std::cin >> std::ws, note);

         size_t end_pos = original.find('-');

         if (end_pos == original.npos)
         {
            catcher.insert("Tried to edit corrupted note."s);
            return;
         }

         line = encrypt(original.substr(0, end_pos) + "- "s + note);
      }
      lines.push_back(line);
   }
   
   if (it < index)
   {
      catcher.insert("Expected an index 1-"s + std::to_string(it) + " including."s);
      return;
   }

   file.close();
   file.open("note.txt", std::ios::out);
   if (!is_file_valid(file, catcher))
      return;

   for (const auto& l : lines)
      file << l << '\n';
   
   Green _g;
   std::cout << "Successfully edited note!\n";
}

void handle_cat(Catcher& catcher)
{
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;

   std::string line;
   size_t index = 0;

   std::cout << '\n';

   while (std::getline(file, line))
      print_note(line, ++index);
}

void handle_list(Catcher& catcher)
{
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;

   std::string line;
   size_t index = 0;

   std::cout << '\n';

   while (std::getline(file, line))
      print_note(decrypt(line), ++index);
}

void handle_blist(Catcher& catcher)
{
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;
   
   std::string line;
   std::vector<std::string> lines;

   while (std::getline(file, line))
      lines.push_back(line);
   
   std::cout << '\n';

   for (long i = lines.size() - 1; i >= 0; --i)
      print_note(decrypt(lines.at(i)), i + 1);
}

void handle_rlist(Catcher& catcher)
{
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;
   
   size_t index = 0;
   std::string line;
   std::vector<std::pair<std::string, size_t>> lines;

   while (std::getline(file, line))
      lines.push_back({line, ++index});
   
   for (size_t i = 0; i < lines.size(); ++i)
   {
      size_t r = i + rand() % (lines.size() - i);
      swap(lines.at(i), lines.at(r));
   }

   std::cout << '\n';

   for (const auto& [l, i] : lines)
      print_note(decrypt(l), i);
}

void handle_get(Catcher& catcher)
{
   Blue _;
   size_t index = get_note_index("\nInput index of the note to get: "s, catcher);
   _.reset();

   if (!catcher.ok())
      return;
   
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;
   
   size_t it = 0;
   std::string line;

   while (std::getline(file, line))
   {
      if (++it == index)
      {
         print_note(decrypt(line), it);
         return;
      }
   }
   catcher.insert("Expected an index 1-"s + std::to_string(it) + " including."s);
}

void handle_search(Catcher& catcher)
{
   Blue _;
   std::cout << "\nSearch in notes:\n";
   _.reset();

   std::string search;
   std::getline(std::cin >> std::ws, search);

   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;

   std::string line;
   size_t index = 1;

   while (std::getline(file, line))
   {
      line = decrypt(line);
      if (line.find(search) != line.npos)
         print_note(line, index);
      ++index;
   }
}

void handle_delete(Catcher& catcher)
{
   Blue _;
   size_t index = get_note_index("\nInput index of the note to delete: "s, catcher);
   _.reset();

   if (!catcher.ok())
      return;
   
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;
   
   size_t it = 0;
   std::string line, original;
   std::vector<std::string> lines;

   while (std::getline(file, line))
      if (index != ++it)
         lines.push_back(line);
      else
         original = decrypt(line);
   
   if (it < index)
   {
      catcher.insert("Expected an index 1-"s + std::to_string(it) + " including."s);
      return;
   }

   file.close();
   file.open("note.txt", std::ios::out);
   if (!is_file_valid(file, catcher))
      return;

   for (const auto& l : lines)
      file << l << '\n';
   
   Green _g;
   std::cout << "Successfully deleted note '" << original << "'\n";
}

void handle_count(Catcher& catcher)
{
   std::fstream file ("note.txt");
   if (!is_file_valid(file, catcher))
      return;

   std::string line;
   size_t count = 0;

   while (std::getline(file, line))
      if (!line.empty())
         ++count;

   Blue _;
   std::cout << "\nYou have " << count << " notes.\n";
}

void handle_quit()
{
   std::exit(0);
}

void handle_invalid_command(Catcher& catcher)
{
   catcher.insert("Invalid command. See 'help' for a list of commands."s);
}
