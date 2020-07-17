cmake_minimum_required (VERSION 3.8)

project ("rockfell")

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package (Git)

if (GIT_FOUND)
	execute_process (WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} describe --always --dirty
					 OUTPUT_VARIABLE ROCKFELL_GIT_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)

	execute_process (WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
					 OUTPUT_VARIABLE ROCKFELL_GIT_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (ROCKFELL_GIT_HASH)
		add_definitions (-DROCKFELL_GIT_HASH="${ROCKFELL_GIT_HASH}")
		add_definitions (-DROCKFELL_GIT_BRANCH="${ROCKFELL_GIT_BRANCH}")
	else ()
		add_definitions (-DROCKFELL_GIT_BRANCH="version")
		add_definitions (-DROCKFELL_GIT_HASH="0.1")
	endif ()
else ()
	add_definitions (-DROCKFELL_GIT_BRANCH="version")
	add_definitions (-DROCKFELL_GIT_HASH="0.1")
endif ()

if (MSVC)
	string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	add_compile_options (/W4 /WX)
else ()
	add_compile_options (-Wall -Werror)
endif ()

if (NOT CMAKE_BUILD_TYPE MATCHES "Debug")
	# hide the console on windows if this isn't a debug build
	set (ROCKFELL_HIDE_CONSOLE WIN32)
endif ()

add_subdirectory (${PROJECT_SOURCE_DIR}/src)