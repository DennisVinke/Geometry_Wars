#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>



namespace fs = std::filesystem;


/// Finds a folder useful for loading in data
inline auto find_folder(const std::string& folder_name)
{
    auto directory = fs::current_path();
    auto root = directory.root_directory();

    while (directory != root)
    {
        if (fs::exists(directory / folder_name) && fs::is_directory(directory / folder_name))
        {
            return std::make_pair(directory / folder_name, true);
        }

        directory = directory.parent_path();
    }

    return std::make_pair(fs::current_path(), false);
}



/// load a text file into a c++ std::string
inline std::string load_file_to_string(const fs::path& file_path)
{
    std::ifstream file{ file_path.string() };
    std::stringstream string_stream;

    string_stream << file.rdbuf();
    return string_stream.str();
}
