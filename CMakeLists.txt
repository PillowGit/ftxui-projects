# Define a cmake project
cmake_minimum_required(VERSION 3.11)
project(ftxuiprojs
        VERSION 0.1
        LANGUAGES CXX)

# ftxui library fetch portion
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Include libuiohook library for keyboard input library
#find_package(uiohook REQUIRED)

# Define executables
add_executable(keylog src/keylog.cpp)
target_link_libraries(keylog PRIVATE ftxui::component) #uiohook)
