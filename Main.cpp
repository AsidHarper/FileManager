#include <iostream>
#pragma warning(disable:4996)
#include <direct.h>
#include <io.h>

void printMenu() {
    std::cout << "File Manager Menu:\n"
        << "1. List files in a directory\n"
        << "2. Create a directory\n"
        << "3. Delete a directory\n"
        << "4. Create a file\n"
        << "5. Delete a file\n"
        << "0. Quit\n"
        << "Enter your choice: ";
}

void ListFiles(const std::string& path) {
    struct _finddata_t fileInfo;
    intptr_t handle = _findfirst((path + "/*").c_str(), &fileInfo);

    if (handle == -1) {
        std::cout << "Error: Unable to list files in directory " << path << std::endl;
        return;
    }

    do {
        if ((fileInfo.attrib & _A_SUBDIR) != 0) {
            if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0) {
                std::cout << fileInfo.name << " (directory)" << std::endl;
            }
        }
        else {
            std::cout << fileInfo.name << " (file)" << std::endl;
        }
    } while (_findnext(handle, &fileInfo) == 0);

    _findclose(handle);
}

bool CreateFile(const std::string& path) {
    FILE* file = fopen(path.c_str(), "w");

    if (file == nullptr) {
        std::cout << "Error: Unable to create file " << path << std::endl;
        return false;
    }

    fclose(file);
    std::cout << "File " << path << " created successfully" << std::endl;
    return true;
}

bool DeleteFile(const std::string& path) {
    if (_unlink(path.c_str()) != 0) {
        std::cout << "Error: Unable to delete file " << path << std::endl;
        return false;
    }

    std::cout << "File " << path << " deleted successfully" << std::endl;
    return true;
}

bool CreateDirectory(const std::string& path) {
    if (_mkdir(path.c_str()) != 0) {
        std::cout << "Error: Unable to create directory " << path << std::endl;
        return false;
    }

    std::cout << "Directory " << path << " created successfully" << std::endl;
    return true;
}

bool DeleteDirectory(const std::string& path) {
    if (_rmdir(path.c_str()) != 0) {
        std::cout << "Error: Unable to delete directory " << path << std::endl;
        return false;
    }

    std::cout << "Directory " << path << " deleted successfully" << std::endl;
    return true;
}

int main() {
    int choice = -1;

    while (choice != 0) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string directory;
        std::string filePath;

        switch (choice) {
        case 1:
            std::cout << "Enter directory path: ";
            std::cin >> directory;
            ListFiles(directory);
            break;
        case 2:
            std::cout << "Enter directory path: ";
            std::cin >> directory;
            CreateDirectory(directory);
            break;
        case 3:
            std::cout << "Enter directory path: ";
            std::cin >> directory;
            DeleteDirectory(directory);
            break;
        case 4:
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            CreateFile(filePath);
            break;
        case 5:
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            DeleteFile(filePath);
            break;
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}