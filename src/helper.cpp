#include "helper.hpp"

#include <iostream>

bool is_file_valid(const std::fstream& file, Catcher& catcher)
{
   if (!file)
      catcher.insert("Could not open file 'note.txt'!"s);
   return file.is_open();
}

size_t get_note_index(const std::string& prompt, Catcher& catcher)
{
   std::cout << prompt;

   std::string index_str;
   std::getline(std::cin >> std::ws, index_str);
   size_t index = 1;

   try
   {
      index = std::stoul(index_str);
      if (index == 0)
         throw std::runtime_error("");
   }
   catch (...)
   {
      catcher.insert("Expected an index. Could not convert input to number."s);
   }
   return index;
}

void print_note(const std::string& line, size_t index)
{
   std::cout << "[" << index << "] " << line << '\n';
}

std::string encrypt(const std::string& string)
{
   if (string.empty())
      return "";

   srand(string.back() + 10);
   std::string result;

   for (size_t i = 0; i < string.size() - 1; ++i)
   {
      int shift = rand() % 6;
      result.push_back(string.at(i) - shift);
      result.push_back(shift + 100);
   }

   result.push_back(string.back());
   srand(time(nullptr));
   return result;
}

std::string decrypt(const std::string& string)
{
   if (string.empty())
      return "";

   srand(string.back() + 10);
   std::string result;

   for (size_t i = 0; i < string.size() - 2; i += 2)
   {
      int shift = string.at(i + 1) - 100;
      result.push_back(string.at(i) + shift);
   }

   result.push_back(string.back());
   srand(time(nullptr));
   return result;
}

Color::Color(const char* color)
   : color(color), res(false)
{
   std::cout << color;
}

Color::~Color()
{
   if (!res)
      std::cout << "\033[0m";
}

void Color::again()
{
   std::cout << color;
   res = false;
}

void Color::reset()
{
   std::cout << "\033[0m";
   res = true;
}
