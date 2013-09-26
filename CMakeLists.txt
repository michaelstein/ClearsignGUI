cmake_minimum_required(VERSION 2.8)
project(ClearsignGUI)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

####################
# Basic dependencies
####################

# Qt4
find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtOpenGL REQUIRED)
set(QT_WRAP_CPP TRUE)
set(QT_USE_QTOPENGL TRUE)

#########
# Sources
#########

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
else()
    set(ARCH "x86")
endif()

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

QT4_WRAP_CPP(client_QHEADERS_MOC ${client_QHEADERS})
QT4_WRAP_UI(client_QFORMS_HEADER ${client_QFORMS})
QT4_ADD_RESOURCES(client_QRESOURCES_RCC ${client_QRESOURCES})

source_group("headers"    FILES ${client_HEADERS})
source_group("qt_headers" FILES ${client_QHEADERS})
source_group("qt_moc"     FILES ${client_QHEADERS_MOC})
source_group("qt_form"    FILES ${client_QFORMS_HEADER})
source_group("qt_res"     FILES ${client_QRESOURCES_RCC})

# compiler flags
SET(CMAKE_C_FLAGS_RELEASE "-Zi")
SET(CMAKE_CXX_FLAGS_RELEASE "-Zi")

# defines
ADD_DEFINITIONS(
	-DUNICODE
	-D_UNICODE
	#/O2
	${QT_DEFINITIONS}
	-DQT_NETWORK_LIB
	-DQT_LARGEFILE_SUPPORT
	-DQT_HAVE_MMX
	-DQT_HAVE_3DNOW
	-DQT_HAVE_SSE
	-DQT_HAVE_MMXEXT
	-DQT_HAVE_SSE2
	-DQT_THREAD_SUPPORT
)

# Includes
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/src
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

LINK_DIRECTORIES(
	${CMAKE_CURRENT_BINARY_DIR}
)

# Gui type
IF(WIN32)
	SET(GUI_TYPE WIN32)
	ADD_DEFINITIONS(
		/Zc:wchar_t-
		/INCREMENTAL
	)
ENDIF(WIN32)

IF(APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF(APPLE)

ADD_EXECUTABLE(ClearsignGUI ${GUI_TYPE}
		${client_SOURCES} ${client_HEADERS} ${client_QHEADERS}
		${client_QHEADERS_MOC} ${client_QFORMS_HEADER} ${client_QRESOURCES_RCC}
)

TARGET_LINK_LIBRARIES(ClearsignGUI
		${QT_LIBRARIES}
		${QT_QTNETWORK_LIBRARY}
		${QT_QTOPENGL_LIBRARY}
)

set_target_properties(ClearsignGUI PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${ARCH}/${CMAKE_BUILD_TYPE}"
)

#install(TARGETS client
#	RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
#)
