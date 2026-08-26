#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "catcher.hpp"
#include <string>

void handle_command(const std::string& command, Catcher& catcher);

void handle_help();
void handle_new(Catcher& catcher);
void handle_edit(Catcher& catcher);
void handle_cat(Catcher& catcher);
void handle_list(Catcher& catcher);
void handle_blist(Catcher& catcher);
void handle_rlist(Catcher& catcher);
void handle_get(Catcher& catcher);
void handle_search(Catcher& catcher);
void handle_delete(Catcher& catcher);
void handle_count(Catcher& catcher);
void handle_quit();
void handle_invalid_command(Catcher& catcher);

#endif
