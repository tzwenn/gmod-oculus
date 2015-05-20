cmake_minimum_required(VERSION 2.8)
project(oculusdrv)

#-----------------

add_definitions(-DNO_SDK -DGMMODULE) 
set(CMAKE_SHARED_LIBRARY_PREFIX "gmcl_")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_win32.dll")
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_osx.dll")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
set(CMAKE_SHARED_LIBRARY_SUFFIX "_linux.dll")
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

set(OVR_PATH "/opt/LibOVR")

include_directories(include)
include_directories("${OVR_PATH}/Include")

file(GLOB CPP_FILES "cpp/*.cpp")
file(GLOB H_FILES "cpp/*.h")

file(GLOB LUA_FILES "lua/*.lua")

add_library(${CMAKE_PROJECT_NAME} SHARED 
	${CPP_FILES}
	${H_FILES}
)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${CMAKE_PROJECT_NAME} Ws2_32)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

set(LIBRARIES
	"${OVR_PATH}/Lib/Mac/Release/LibOVR.framework"
	"-framework CoreFoundation"
	"-framework ApplicationServices"
	"-framework IOKit"
	"-framework OpenGL")

target_link_libraries(${CMAKE_PROJECT_NAME}
	${LIBRARIES})

#-----------------

add_executable(${CMAKE_PROJECT_NAME}_test
	test.cpp
	${LUA_FILES}
)

target_link_libraries(${CMAKE_PROJECT_NAME}_test
	${CMAKE_PROJECT_NAME}
	${LIBRARIES}
)

set_target_properties(${CMAKE_PROJECT_NAME}_test PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

#-----------------

set(STEAM_DIR "/Users/$ENV{USER}/Library/Application Support/Steam")
set(CMAKE_INSTALL_PREFIX "${STEAM_DIR}/SteamApps/common/GarrysMod/garrysmod/lua")

INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
	LIBRARY DESTINATION bin
)

INSTALL(FILES lua/oculus.lua
	DESTINATION postprocess
)
