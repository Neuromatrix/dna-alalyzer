#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include "Analyzer.h"
#include "Merger.h"
void generateReadme(Server::Analyzer::Analyzer& analyzer, const std::string& outputPath) {
    std::ofstream readme(outputPath);

    if (!readme.is_open()) {
        std::cerr << "Error: Unable to open README file for writing.\n";
        return;
    }

    readme << "# Результаты функций анализатора\n\n";

    // Call all functions of the Analyzer class
    std::string sequenceResult = analyzer.GetSequence();
    double gcContentResult = analyzer.CalculateGCContent();
    auto codonUsageResult = analyzer.CalculateCodonUsage();
    auto orfsResult = analyzer.FindORFs();

    // Print results in README with enhanced formatting
    readme << "## Результаты анализа последовательности ДНК\n";
    readme << "В данном разделе представлены результаты вызовов функций анализатора для последовательности ДНК.\n\n";

    readme << "### Результат последовательности\n";
    readme << "- **Результат:** " << sequenceResult << "\n\n";

    readme << "### Результат содержания GC\n";
    readme << "- **Результат:** " << gcContentResult * 100 << "%\n";
    readme << "- **Описание:** Содержание GC (гуанин-цитозин) в ДНК - это процентное отношение суммы гуанина и цитозина к общему числу нуклеотидов. Более высокое содержание GC может указывать на более стабильную ДНК-структуру.\n\n";

    readme << "### Результат использования кодонов\n";
    readme << "- **Результат:** ";  // Print the codon usage map here
    for (const auto& pair : codonUsageResult) {
        readme << pair.first << ": " << pair.second << ", ";
    }
    readme << "\n";
    readme << "- **Описание:** Анализ использования кодонов предоставляет информацию о частоте встречаемости различных кодонов в последовательности ДНК. Это важно для понимания процесса трансляции и синтеза белка.\n\n";

    readme << "### Результат поиска открытых рамок считывания (ORFs)\n";
    readme << "- **Результат:** ";  // Print the ORFs vector here
    for (const auto& orf : orfsResult) {
        readme << orf << ", ";
    }
    readme << "\n";
    readme << "- **Описание:** Открытые рамки считывания (ORFs) представляют собой участки ДНК, которые могут быть транслированы в белок. Они являются ключевыми элементами в геноме, и их поиск важен для понимания функциональности генетической информации.\n";

    readme.close();
    std::cout << "Файл README успешно сгенерирован.\n";
}
std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return fileData;
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
}
std::vector<std::string> readDataFromDirectory(const std::string& directoryPath) {
    std::vector<std::string> fileData;

    try {
        // Iterate through files in the specified directory
        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                // Read data from each TXT file
                std::ifstream file(entry.path());
                if (file.is_open()) {
                    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    fileData.push_back(content);
                    file.close();
                } else {
                    std::cerr << "Error: Unable to open file " << entry.path() << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return fileData;
}

std::vector<std::string> readPathsFromFile(const std::string& filePath) {
    std::vector<std::string> paths;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            paths.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }

    return paths;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <-merge|-analyze|-smerge> \n";
        exit(EXIT_FAILURE);
    }

    std::string option = argv[1];
    std::string cFilePath = "Command.txt";

    if (option != "-merge" && option != "-analyze" && option != "-smerge") {
        std::cerr << "Invalid option. Use <-merge|-analyze|-smerge>\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> paths = readPathsFromFile(cFilePath);

    if (option == "-analyze") {
        if (!paths.empty()) {
            std::string fileData = readFile(paths.front());
            fileData.erase(std::remove_if(fileData.begin(), fileData.end(), [](unsigned char c) {
                return std::isspace(c);
            }), fileData.end());

            Server::Analyzer::Analyzer analyze(fileData);
            std::string output = "../Data/Out.md";
            generateReadme(analyze, output);
        }
    } else if (option == "-merge") {
        std::vector <std::string> ldata;
        for (const auto& filePath : paths) {
            std::string fileData = readFile(filePath);
            fileData.erase(std::remove_if(fileData.begin(), fileData.end(), [](unsigned char c) {
                return std::isspace(c);
            }), fileData.end());
            ldata.push_back(fileData);
        }
        std::string receive = Server::Merger::Merge(ldata);
        std::string outputPath = "../Data/Merged.txt";
        std::ofstream merged(outputPath);

        if (!merged.is_open()) {
            std::cerr << "Error: Unable to open README file for writing.\n";
            return 1;
        }
        merged << receive;
    } else if (option == "-smerge") {
        auto ldata = readDataFromDirectory(paths.front());
        std::string receive = Server::Merger::Merge(ldata);
        std::string outputPath = "../Data/Merged.txt";
        std::ofstream merged(outputPath);

        if (!merged.is_open()) {
            std::cerr << "Error: Unable to open README file for writing.\n";
            return 1;
        }
        std::string ut = receive;
        ut.erase(std::remove_if(ut.begin(), ut.end(), [](unsigned char c) {
            return std::isspace(c);
        }), ut.end());
        merged << ut;
    }

    return 0;
}
