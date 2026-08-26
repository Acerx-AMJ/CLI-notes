#ifndef HELPER_HPP
#define HELPER_HPP

#include "catcher.hpp"
#include <fstream>

bool is_file_valid(const std::fstream& file, Catcher& catcher);
size_t get_note_index(const std::string& prompt, Catcher& catcher);
void print_note(const std::string& line, size_t index);

std::string encrypt(const std::string& string);
std::string decrypt(const std::string& string);

class Color
{
protected:
   const char* color;
   bool res = false;

public:

   Color(const char* color);
   virtual ~Color();

   void again();
   void reset();
};

class Red : public Color
{
public:
   Red(): Color("\033[31m") {}
};

class Green : public Color
{
public:
   Green(): Color("\033[32m") {}
};

class Blue : public Color
{
public:
   Blue(): Color("\033[34m") {}
};

#endif
