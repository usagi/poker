cmake_minimum_required( VERSION 3.7 )

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-DNDEBUG -Os")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/source)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(Boost REQUIRED
  timer
  system
  filesystem
  random
)

include(ExternalProject)

ExternalProject_Add( external_cmdline
  GIT_REPOSITORY git@github.com:tanakh/cmdline.git
  PREFIX            ${CMAKE_CURRENT_BINARY_DIR}/external
  INSTALL_DIR       ${CMAKE_CURRENT_BINARY_DIR}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND
    COMMAND ${CMAKE_COMMAND}
      -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/external/src/external_cmdline/cmdline.h
        ${CMAKE_CURRENT_BINARY_DIR}/include/cmdline.h
)

add_executable( draw_poker source/draw_poker.cxx )
add_dependencies( draw_poker external_cmdline )
target_link_libraries( draw_poker ${Boost_LIBRARIES} )

add_library( player_a SHARED source/player_a.cxx )
add_library( player_b SHARED source/player_b.cxx )
