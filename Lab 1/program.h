//program.h: Contains declarations of lowercase and usage methods. Declares enumerations for program behavior and for arguments
//Name: Oscar Arias
//Email: oarias@wustl.edu

#pragma once
#ifndef program_h
#define program_h

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum args { program_name, input_file, expected_arg_length };
enum cases { success, file_not_open, wrong_cmd_args, extract_dimensions_error, line_not_read, piece_parse_failure, dimensions_never_extracted, vector_board_mismatch};

int usage(const string & program, const string & message);
string lowercase(string & input_string);

#endif