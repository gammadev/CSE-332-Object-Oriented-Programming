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

enum args { program_name, input_file, expected_arg_length, game_not_given };
enum cases { success, file_not_open, wrong_cmd_args, bad_allocation };

int usage(const string & program, const string & message);
string lowercase(string & input_string);

#endif