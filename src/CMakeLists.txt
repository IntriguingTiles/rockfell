if (DEFINED WIIU)
	include ("${DEVKITPRO}/wut/share/wut.cmake" REQUIRED)

	find_package (PkgConfig REQUIRED)
	pkg_search_module (TURBOJPEG REQUIRED libturbojpeg)
	pkg_search_module (PNG REQUIRED libpng)
	pkg_search_module (SDL2 REQUIRED sdl2)

	link_directories (${TURBOJPEG_LIBDIR} ${PNG_LIBDIR} ${SDL2_LIBDIR} ${SDL2_IMAGE_LIBDIR})
else ()
	find_package (SDL2 REQUIRED)
endif ()
	
find_package (SDL2_image REQUIRED)
include_directories (${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

if (NOT DEFINED SDL2_LIBRARIES)
	set (SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)
endif ()

add_executable (rockfell ${ROCKFELL_HIDE_CONSOLE} "main.cpp" "menu.cpp" "menu.h" "button.cpp" "button.h" "interfaces.h" "globals.h" "sdl_goop.cpp" "sdl_goop.h" "input.h" "input.cpp" "entities/base_entity.h" "entities/base_entity.cpp" "entities/player.cpp" "entities/player.h" "rockfell.cpp")
target_link_libraries (rockfell ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${TURBOJPEG_LIBRARIES} ${PNG_LIBRARIES})

if (DEFINED WIIU)
	wut_create_rpx (rockfell)
endif ()