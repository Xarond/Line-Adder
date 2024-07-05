#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void prependHeader(const fs::path& file_path) {
    std::string temp_name = file_path.string() + ".tmp";
    std::ifstream input(file_path);
    std::ofstream output(temp_name);

    // Lines, that you want to add
    output << "//*************************\n";
    output << "// Text to add\n";
    output << "//*************************\n";


    output << input.rdbuf();

    input.close();
    output.close();

    // Zastąpienie oryginalnego pliku
    fs::rename(temp_name, file_path);
}

int main() {
    std::string directory_path;
    std::cout << "Direcotry Path: ";
    std::cin >> directory_path;

    try {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file()) {
                prependHeader(entry.path());
            }
        }
        std::cout << "Complete.\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}