project(RaytracingInOneWeekend)

include_directories(../../thirdParty/progress-cpp/include/)

#Add header & source files
macro(read_directory curdir)
	file(GLOB children RELATIVE ${curdir} ${curdir}/*)
	
	set(groupList "")
	
	foreach(child ${children})
		if (NOT (IS_DIRECTORY ${curdir}/${child}))
			list(APPEND src ${curdir}/${child})
			list(APPEND groupList ${curdir}/${child})
		endif()
	endforeach()
	
	list(LENGTH groupList length)
	if (length GREATER 0)
		string(REPLACE ${PROJECT_SOURCE_DIR} "" GROUPNAME ${curdir})
		string(REPLACE "/" "\\" GROUPNAME ${GROUPNAME})
		source_group(${GROUPNAME} FILES ${groupList})
	endif()

	foreach(child ${children})
		read_directory(${curdir}/${child})
	endforeach()
endmacro()
read_directory(${PROJECT_SOURCE_DIR}/src/)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if (MSVC)
add_definitions(/MP)
endif()

add_executable(RaytracingInOneWeekend ${src})

target_link_libraries(RaytracingInOneWeekend PRIVATE Threads::Threads)