cmake_minimum_required(VERSION 2.8)
project(optitrack)

#-----------------

add_definitions(-DNO_SDK -DGMMODULE) 
set(CMAKE_SHARED_LIBRARY_PREFIX "gmsv_")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_win32.dll")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_osx.dll")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_linux.dll")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

include_directories(include)
file(GLOB CPP_FILES "src/*.cpp")

add_library(${CMAKE_PROJECT_NAME} SHARED 
	${CPP_FILES}
	)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${CMAKE_PROJECT_NAME} Ws2_32)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

#-----------------

set(STEAM_DIR "/Users/sven/Library/Application Support/Steam/")
set(CMAKE_INSTALL_PREFIX "${STEAM_DIR}/SteamApps/common/GarrysMod/garrysmod/lua")

INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
	LIBRARY DESTINATION bin
)

