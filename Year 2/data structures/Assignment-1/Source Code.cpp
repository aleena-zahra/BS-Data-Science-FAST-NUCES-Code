#include <iostream>
#include <cstdlib> 

void openHtmlFile(const std::string& filePath) {
#ifdef _WIN32
    std::string command = "start " + filePath;
#elif __linux__
    std::string command = "xdg-open " + filePath;
#elif __APPLE__
    std::string command = "open " + filePath;
#else
    std::cerr << "Unsupported operating system" << std::endl;
    return;
#endif
    std::system(command.c_str());
}

int main() {
    std::string filePath = "file1.html"; // Replace with your HTML file path
    openHtmlFile(filePath);
    return 0;
}
