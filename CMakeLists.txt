cmake_minimum_required(VERSION 3.16)
project(Mortal-Kombat-PUT-Edition LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML")

# Wszystkie pliki źródłowe i nagłówkowe projektu
add_executable(rpg-game 
    main.cpp 
    engine.cpp 
    engine.h
    characterSelect.cpp
    characterSelect.h
    mainmenu.cpp 
    mainMenu.h
    buttons.cpp 
    buttons.h
    settings.cpp
    settings.h
    arena.cpp
    arena.h
    player.cpp
    player.h
    animation.cpp
    animation.h
    apteczka.cpp
    apteczka.h
    gameobject.h
)

target_include_directories(rpg-game PRIVATE "${SFML_DIR}/include")

# Linkowanie bibliotek SFML
target_link_libraries(rpg-game PRIVATE 
    "${SFML_DIR}/lib/sfml-graphics-d.lib"
    "${SFML_DIR}/lib/sfml-window-d.lib"
    "${SFML_DIR}/lib/sfml-system-d.lib"
    "${SFML_DIR}/lib/sfml-audio-d.lib"
    opengl32.lib
    winmm.lib
    gdi32.lib
    advapi32.lib
    windowscodecs.lib
    shlwapi.lib
    kernel32.lib
    user32.lib
    winspool.lib
    shell32.lib
    ole32.lib
    oleaut32.lib
    uuid.lib
    comdlg32.lib
)

# Kopiowanie folderu Icons
add_custom_command(TARGET rpg-game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/Icons"
    "$<TARGET_FILE_DIR:rpg-game>/Icons"
)