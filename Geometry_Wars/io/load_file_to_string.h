#pragma once

#include <string>
#include <sstream>
#include <fstream>



inline std::string load_file_to_string(const std::string& file_name)
{
    std::ifstream file{ file_name };
    std::stringstream string_stream;

    string_stream << file.rdbuf();
    return string_stream.str();
}
