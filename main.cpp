#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <cctype>
#include <regex>
#include <algorithm>
#include <sstream>
#include <map>
#include <iomanip>
#include <filesystem>

std::string toLowerCase(const std::string &str) // convert string to lowercase
{
    std::string lowercased = str;
    std::transform(lowercased.begin(), lowercased.end(), lowercased.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowercased;
}

bool containsNumber(const std::string &str) // check if string contains a number
{
    return std::any_of(str.begin(), str.end(), ::isdigit);
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
    std::map<std::string, std::pair<int, std::vector<int>>> word_counter; // map of words and their count and line numbers, using map to sort the words alphabetically
    std::set<std::string> urls;
    std::regex url_pattern(R"(((http|https)://|www\.)[\w.-]+(?:\.[\w\.-]+)+[\w\-\._~:/?#[\]@!\$&'\(\)\*\+,;=.]*)"); // regex for urls
    int line_number = 1;
    int word_count = 0;

    while(getline(in_file, line)) // read file line by line
    {
        std::smatch match; // regex match
        while (std::regex_search (line, match, url_pattern)) // find all urls in the line
        {
            urls.insert(match.str());
            line = match.prefix().str() + " " + match.suffix().str();
        }

        std::istringstream iss(line);
        std::string word;
        while (iss >> word) // read line word by word
        {
            word.erase(word.begin(), std::find_if(word.begin(), word.end(), [](unsigned char c){ return !std::ispunct(c); }));
            word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char c){ return !std::ispunct(c); }).base(), word.end());

            word = toLowerCase(word);

            if(word.empty() || containsNumber(word)) // skip empty words and words with numbers
            {
                continue;
            }

            word_counter[word].first++; // increment word count
            word_counter[word].second.push_back(line_number); // add line number to the map
        }
        line_number++;
    }
    in_file.close();

    std::ofstream out_file;
    out_file.open("rezultatai.txt");

    out_file << "LINKS (" << urls.size() << ")\n";
    for(const auto& url: urls) // print urls to file, remove the last character if it's a dot
    {
        std::string fixed_url = url;
        if (!fixed_url.empty() && fixed_url.back() == '.') 
        {
            fixed_url.pop_back(); // remove the last character
        }
        out_file << fixed_url << "\n";
    }
    out_file << "\n";


    out_file << std::left << "WORD COUNTER\n";
    out_file << std::setw(20) << "Word" << " | " << std::setw(5) << "Count" << " | " << "Found in rows\n";
    out_file << "--------------------------------------------------------------\n";
    for(const auto& pair: word_counter)
    {
        if(pair.second.first > 1)
        {
            word_count++;
            out_file << std::setw(20) << pair.first << " | " << std::setw(5) << pair.second.first << " | ";
            int lineCounter = 0;
            for(auto lineNum : pair.second.second)
            {
                if(lineCounter != 0 && lineCounter % 10 == 0) // 10 lines numbers per line
                    out_file << "\n" << std::setw(28) << " "; // 28: 20 (word column width) + 3 (inter-column space) + 5 (count column width)
                out_file << lineNum << " ";
                lineCounter++;
            }
            out_file << "\n--------------------------------------------------------------\n";
        }
    }

    out_file.close();
    std::cout << "Number of links: " << urls.size() << std::endl;
    std::cout << "Number of unique words (count >= 2): " << word_count << std::endl;
    std::cout << "Check rezultatai.txt for results\n" << std::endl;
    return 0;
}
