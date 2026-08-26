#ifndef CATCHER_HPP
#define CATCHER_HPP

#include <string>
#include <vector>

using namespace std::string_literals;

struct Catcher
{
private:
   std::vector<std::string> errors;

public:

   void insert(const std::string& error);

   bool ok() const;

   void display();
};

#endif
