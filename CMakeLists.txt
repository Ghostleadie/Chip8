# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RaylibApp")

#
# Dependencies
#

# Raylib
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()

set(IMGUI_VERSION 1.91.8)
find_package(imgui ${IMGUI_VERSION} QUIET) # QUIET or REQUIRED
if (NOT imgui_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            imgui
            URL https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.tar.gz
    )
    FetchContent_GetProperties(imgui)
    if (NOT imgui_POPULATED) # Have we downloaded imgui yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(imgui)
    endif()
endif()
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(imgui INTERFACE ${imgui_SOURCE_DIR})

# RlImGui __________________________________________
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY "https://github.com/raylib-extras/rlImGui.git"
        GIT_TAG        main
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)
FetchContent_GetProperties(rlimgui)
if(NOT rlimgui_POPULATED)
    FetchContent_Populate(rlimgui)
    FetchContent_MakeAvailable(rlimgui)
endif()

add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
target_link_libraries(rlimgui PRIVATE raylib imgui)
target_include_directories(rlimgui INTERFACE ${rlimgui_SOURCE_DIR})

find_package(spdlog QUIET)
if(NOT spdlog_FOUND)
    FetchContent_Declare(
        spdlog
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.15.2.zip
    )
    message("Fetching spdlog")
endif()

FetchContent_MakeAvailable(spdlog)
set_target_properties(spdlog PROPERTIES FOLDER "Dependencies")

# Include sub-projects.
add_subdirectory ("RaylibApp")
