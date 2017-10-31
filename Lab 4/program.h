//program.h: Contains declarations of lowercase and usage methods. Declares enumerations for program behavior and for arguments
//Name: Oscar Arias
//ID: 438241
//Email: oarias@wustl.edu

#pragma once
#ifndef program_h
#define program_h

#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <numeric>

using namespace std;

enum args { program_name, input_file, expected_arg_length};
enum cases { success, game_not_given, wrong_cmd_args, bad_allocation, game_does_not_exist, game_currently_exists, file_not_open, file_not_closed, write_fail, read_fail };

int usage(const string & program, const string & message);
string lowercase(string & input_string);

#endif