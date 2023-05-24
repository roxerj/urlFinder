#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cctype>
#include <regex>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <filesystem> // Added this library for file operations

std::string toLowerCase(const std::string &str) {
    std::string lowercased = str;
    std::transform(lowercased.begin(), lowercased.end(), lowercased.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowercased;
}

int main()
{
    std::string file_name;
    std::ifstream in_file;

    // List all .txt files in the current directory
    std::cout << "Available .txt files in the current directory: \n";
    for(const auto & entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if(entry.path().extension() == ".txt")
            std::cout << entry.path().filename() << "\n";
    }

    // Ask for file name and verify if it exists
    do {
        std::cout << "\nEnter file name: ";
        std::cin >> file_name;
        in_file.open(file_name);
        if(!in_file)
        {
            std::cerr << "Error opening file, try again" << std::endl;
        }
    } while (!in_file);

    std::string line;
    std::unordered_map<std::string, int> word_counter;
    std::vector<std::string> urls;
    std::regex url_pattern(R"((http|https)://[\w.-]+(?:\.[\w\.-]+)+[\w\-\._~:/?#[\]@!\$&'\(\)\*\+,;=.]+)");

    while(getline(in_file, line))
    {
        std::smatch match;
        while (std::regex_search (line, match, url_pattern)) {
            urls.push_back(match.str());
            line = match.prefix().str() + " " + match.suffix().str();
        }

        std::istringstream iss(line);
        std::string word;
        while (iss >> word)
        {
            word.erase(word.begin(), std::find_if(word.begin(), word.end(), [](unsigned char c){ return !std::ispunct(c); }));
            word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char c){ return !std::ispunct(c); }).base(), word.end());

            word = toLowerCase(word);

            if(word.empty())
            {
                continue;
            }

            word_counter[word]++;
        }
    }
    in_file.close();

    std::ofstream out_file;
    out_file.open("rezultatai.txt");
    
    for(const auto& url: urls)
    {
        out_file << url << std::endl;
    }

    for(const auto& pair: word_counter)
    {
        if(pair.second > 1)
        {
            out_file << pair.first << " " << pair.second << std::endl;
        }
    }
    out_file.close();

    return 0;
}
