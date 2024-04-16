cmake_minimum_required(VERSION 3.14)
project(Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES source/main.cpp
        source/App.cpp
        source/App.h
        source/Reader.cpp
        source/Reader.h)
add_executable(Client ${SOURCE_FILES})

# Добавление textures
FILE(
        COPY "textures"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
FILE(
        COPY "config.txt"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
if(WIN32)
    set(SFML_ROOT "C:\\SFML-2.6.1")
    set(SFML_STATIC_LIBRARIES TRUE)
else()
    include_directories(/usr/local/include)
endif()

# Поиск компонентов библиотеки
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    # Добавление headers
    target_include_directories(Client PRIVATE ${SFML_INCLUDE_DIR})
    # Линковка библиотек
    target_link_libraries(Client PRIVATE m sfml-graphics sfml-window sfml-system)
endif()
