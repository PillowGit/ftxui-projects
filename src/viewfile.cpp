#include <fstream>
#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <vector>

using namespace ftxui;

int main(int argc, char *argv[]) {

  // Ensure filepath was give
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0]
              << " <filename>\nTry: \"$(readlink -f filename.ext)\""
              << std::endl;
  }

  // Open file
  std::string filepath = argv[1];
  std::string filename = filepath.substr(filepath.rfind("/") + 1);

  // Create display elements
  auto title = text(filename) | bold | hcenter;
  std::vector<Element> lines{title, separator()};

  // Read lines from file and add to elements
  std::ifstream file(filepath);
  std::string line_content{};
  int i = 1;
  while (file) {
    getline(file, line_content);
    Element line = text(std::to_string(i++) + ".\t" + line_content);
    lines.push_back(line);
  }

  // Now create the ui
  auto container = vbox(std::move(lines));
  auto interface = [&] { return container; };

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(Renderer(interface));

  return 0;
}
