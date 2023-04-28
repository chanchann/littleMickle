#include <filesystem>
#include <iostream>

int main() {
  std::filesystem::path current_path = std::filesystem::current_path();

  std::cout << current_path << std::endl;

  std::cout << current_path.parent_path() << std::endl;

  std::filesystem::path dir_name = current_path.filename();

  std::cout << "Current directory name: " << dir_name << "\n";

  std::cout << current_path.parent_path() / dir_name << std::endl;

  return 0;
}
