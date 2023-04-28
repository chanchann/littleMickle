#include <filesystem>
#include <iostream>

int main() {
  std::filesystem::path current_path = std::filesystem::current_path();

  std::filesystem::path dir_name = current_path.filename();

  std::cout << "Current directory name: " << dir_name << "\n";

  return 0;
}
