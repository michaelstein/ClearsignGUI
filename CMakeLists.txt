cmake_minimum_required(VERSION 2.8.11)
project(ClearsignGUI)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

# Global settings
set(GLOBAL_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)

# Sets global output directory for single configuration (GCC)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GLOBAL_OUTPUT_PATH})

# Sets global output directory for sub-configurations (msvc, mingw)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${GLOBAL_OUTPUT_PATH})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Global link directories
link_directories(${GLOBAL_OUTPUT_PATH})

# Check for Qt installation directory.
if(QTDIR)
  list(APPEND CMAKE_PREFIX_PATH ${QTDIR})
endif()

# Platform specific options.
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11")
	message( "Qt Directory: ${QTDIR}" )
else()
	add_definitions(/MP)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ARCH "x64")
	if(UNIX)
		set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")
	endif(UNIX)
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

####################
# Basic dependencies
####################

# Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC OFF)
add_definitions(-DNOMINMAX)
set(QT_USE_QTMAIN TRUE)
if(POLICY CMP0020)
	cmake_policy(SET CMP0020 NEW)
endif()
get_target_property(QtCore_location Qt5::Core LOCATION)
message("Qt5: " ${QtCore_location})

#########
# Sources
#########

set(client_HEADERS
		
)

SET(client_QHEADERS
	src/gui/mainwindow.h
)

SET(client_SOURCES
	src/gui/mainwindow.cpp
	src/main.cpp
)

SET(client_QFORMS
	res/forms/mainwindowform.ui
)

SET(client_QRESOURCES
	res/res.qrc
)

QT5_WRAP_CPP(client_QHEADERS_MOC ${client_QHEADERS})
QT5_WRAP_UI(client_QFORMS_HEADER ${client_QFORMS})
QT5_ADD_RESOURCES(client_QRESOURCES_RCC ${client_QRESOURCES})

source_group("headers"    FILES ${client_HEADERS})
source_group("qt_headers" FILES ${client_QHEADERS})
source_group("qt_moc"     FILES ${client_QHEADERS_MOC})
source_group("qt_form"    FILES ${client_QFORMS_HEADER})
source_group("qt_res"     FILES ${client_QRESOURCES_RCC})

#
# Preprocessor definitions
#
add_definitions(
	-DUNICODE
	-D_UNICODE
)

if(WIN32)
	add_definitions(
		/INCREMENTAL
	)
endif()

#
# Include directories
#
include_directories(
	${PROJECT_SOURCE_DIR}/src
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

#
# Library link directories
#
link_directories(
	${CMAKE_CURRENT_BINARY_DIR}
)

#
# Some other stuff...
#
if(WIN32)
	set(GUI_TYPE WIN32)
endif(WIN32)
if(APPLE)
	set(GUI_TYPE MACOSX_BUNDLE)
endif(APPLE)

ADD_EXECUTABLE(ClearsignGUI ${GUI_TYPE}
		${client_SOURCES} ${client_HEADERS} ${client_QHEADERS}
		${client_QHEADERS_MOC} ${client_QFORMS_HEADER} ${client_QRESOURCES_RCC}
)

#
# Link executable targets
#
target_link_libraries(ClearsignGUI Qt5::Core Qt5::Widgets)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(ClearsignGUI -L/lib64 -lpthread)
endif()
