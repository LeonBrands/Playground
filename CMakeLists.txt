#CMake
cmake_minimum_required(VERSION 3.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

#Setup project
set(PROJECT_NAME Playground)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Check if submodules are downloaded
if(	NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/glfw/CMakeLists.txt" OR
NOT EXISTS "${PROJECT_SOURCE_DIR}/thirdParty/progress-cpp/CMakeLists.txt")
	message(STATUS "The git submodules were not updated, attempting to do so now")
	find_package(Git)
	if (NOT GIT_FOUND)
		message(FATAL_ERROR "Couldn't find Git executable thus the git submodules weren't downloaded. To build this, you'll need to download git and try again, or run git submodule update --init --recursive yourself.")
	else()
		message(STATUS "Git found, updating submodules")
		execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
						WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
						RESULT_VARIABLE GIT_SUBMOD_RESULT)
		if(NOT GIT_SUBMOD_RESULT EQUAL "0")
			message(FATAL_ERROR "git submodule update failed with ${GIT_SUBMOD_RESULT}")
		endif()
	endif()
endif()

#Add subprojects
add_subdirectory(raytracing/one_weekend)