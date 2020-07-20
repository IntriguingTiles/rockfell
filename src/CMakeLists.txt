find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

if (NOT DEFINED SDL2_LIBRARIES)
	set (SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)
endif ()

add_executable (rockfell ${ROCKFELL_HIDE_CONSOLE} "main.cpp" "menu.cpp" "menu.h" "button.cpp" "button.h" "interfaces.h" "globals.h" "sdl_goop.cpp" "sdl_goop.h" "input.h" "input.cpp")
target_link_libraries (rockfell ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})