cmake_minimum_required(VERSION 3.16)


project(Mortal-Kombat-PUT-Edition LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DSFML_STATIC)


set(SFML_DIR "${CMAKE_SOURCE_DIR}/dependencies/SFML")


add_executable(rpg-game 
    main.cpp 
    engine.cpp 
    characterselect.cpp 
    mainmenu.cpp 
    buttons.cpp 
    settings.cpp
    arena.cpp   
    player.cpp  
 "gameobject.h" "apteczka.h" "apteczka.cpp" "animation.h" "animation.cpp" "config.h")


target_include_directories(rpg-game PRIVATE "${SFML_DIR}/include")


target_link_libraries(rpg-game PRIVATE 
    debug "${SFML_DIR}/lib/sfml-graphics-s-d.lib"
    optimized "${SFML_DIR}/lib/sfml-graphics-s.lib"
    
    debug "${SFML_DIR}/lib/sfml-window-s-d.lib"
    optimized "${SFML_DIR}/lib/sfml-window-s.lib"
    
    debug "${SFML_DIR}/lib/sfml-system-s-d.lib"
    optimized "${SFML_DIR}/lib/sfml-system-s.lib"
    
    debug "${SFML_DIR}/lib/sfml-audio-s-d.lib"
    optimized "${SFML_DIR}/lib/sfml-audio-s.lib"

    "${SFML_DIR}/lib/freetype.lib"
    opengl32
    winmm
    gdi32
    advapi32
    windowscodecs
    shlwapi
)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")