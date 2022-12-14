#=================================BUILD PROJECT=================================

cmake_minimum_required(VERSION 3.16)

if (WIN32)
	project(Fifteen_Puzzle VERSION 0.1 LANGUAGES CXX)
elseif (UNIX)
	project(Fifteen_Puzzle)
endif()

#================================INCLUSION OF QT================================

# Include THIS directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON) #support source files
set(CMAKE_AUTOUIC ON) #support header files
set(CMAKE_AUTORCC ON) #support *.qrc files

# We need C++ 20 because of std::ranges
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

#==========================INCLUSION OF PROJECT FIELS===========================

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/headers")
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")

include_directories(${SOURCE_DIR})
include_directories(${HEADERS_DIR})
include_directories(${RESOURCE_DIR})

file(GLOB_RECURSE SOURCES
	"${SRC_DIR}/*.cpp"
	"${HEADERS_DIR}/*.cpp"
	"${HEADERS_DIR}/*.hpp"
	"${RESOURCE_DIR}/*.qrc"
)

#==============================SETUP THE EXECUTABLE=============================

# Add the forms directory to the AUTOUIC search paths
#set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${RESOURCE_DIR})

# Set icon for application
set(APP_ICON_WIN "${CMAKE_CURRENT_SOURCE_DIR}/resources/src_icon.rc")

if (WIN32)
	qt_add_executable(
		appFifteen_Puzzle
		WIN32
		src/main.cpp
		headers/gamepage.cpp
		headers/gamepage.hpp
		resources/resource.qrc
		${APP_ICON_WIN}
	)
elseif (UNIX)
	qt_add_executable(
		appFifteen_Puzzle
		src/main.cpp
		headers/gamepage.cpp
		headers/gamepage.hpp
		resources/resource.qrc
		${APP_ICON_WIN}
	)
endif()


qt_add_qml_module(appFifteen_Puzzle
	URI Fifteen_Puzzle
	VERSION 1.0
	QML_FILES
	resources/main.qml
	resources/GamePage.qml
	resources/Tile.qml
	resources/SmartBar.qml
	resources/TwoButtonPage.qml
)

# Add the target includes for appFifteen_Puzzle
target_include_directories(
	appFifteen_Puzzle
	PRIVATE ${RESOURCE_DIR}
	PRIVATE ${HEADERS_DIR}
	PRIVATE ${SRC_DIR}
)

set_target_properties(appFifteen_Puzzle PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

#===============================LINKING LIBRARIES===============================

# Links the executable to Qt's libraries
# Applies compiler and linker flags as specified by the linked-to libraries
target_link_libraries(
	appFifteen_Puzzle
	PRIVATE
	Qt6::Quick
)

install(TARGETS appFifteen_Puzzle
	BUNDLE DESTINATION .
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
