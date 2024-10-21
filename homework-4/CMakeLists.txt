# CMakeList.txt : CMake project for Graphics, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Graphics")


# Add source to this project's executable.
add_executable (Graphics "src/main.cpp" "include/lines.h" "src/lines.cpp" "include/AssimpImport.h" "include/Mesh3D.h" "include/Object3D.h" "include/Frustum.h" "src/Mesh3D.cpp" "src/Object3D.cpp" "src/AssimpImport.cpp" "src/triangles.cpp") 

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Graphics PROPERTY CXX_STANDARD 20)
endif()

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(Graphics PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(Graphics PRIVATE assimp::assimp)

target_include_directories(Graphics PUBLIC "./include")
