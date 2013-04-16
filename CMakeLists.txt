## CMakeLists.txt
#

cmake_minimum_required( VERSION 2.8 )

project( fdfpp )

# set project version number: 0.1 until it's 'useable'
set( fdfpp_VERSION_MAJOR 0)
set( fdfpp_VERSION_MINOR 9)
set( fdfpp_VERSION_PATCH 1)

#set( WITH_SHARED_LIBS False )

message(STATUS "Cmake detected the following system: " ${CMAKE_SYSTEM_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(fdfpp_SOURCES
	${PROJECT_SOURCE_DIR}/fdf.c
	${PROJECT_SOURCE_DIR}/fdfpp.cpp
	)

set(fdfpp_HEADERS
	${PROJECT_SOURCE_DIR}/fdf.h
	${PROJECT_SOURCE_DIR}/fdfpp.h
	)

#----------------------------------------------------------------------------
## fdfpp testing with GTest
#----------------------------------------------------------------------------
 set(fdfpp_unittest_SOURCES
	${PROJECT_SOURCE_DIR}/fdfpp.cpp
        ${PROJECT_SOURCE_DIR}/fdfpp_unittest.cpp
       )

 set(fdfpp_unittest_HEADERS
 	${PROJECT_SOURCE_DIR}/fdf.h
 	${PROJECT_SOURCE_DIR}/fdfpp.h
 	)
	
#----------------------------------------------------------------------------
## Microsoft Visual C++ flags
#----------------------------------------------------------------------------

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  message(STATUS "Processing system dependent settings for "
  		 ${CMAKE_SYSTEM_NAME})
  # Settings for Microsoft Visual Studio, MSVC++
  # C compiler flags
  message(STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
  if(CMAKE_C_COMPILER MATCHES cl)
    if(NOT WITH_SHARED_LIBS)
     if(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
       set(CMAKE_C_FLAGS "/nologo /W3 /EHsc /Gy")
       set(CMAKE_C_FLAGS_DEBUG "/MTd /Z7 /Od")
       set(CMAKE_C_FLAGS_RELEASE "/MT /O2")
       set(CMAKE_C_FLAGS_MINSIZEREL "/MT /O2")
       set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /O2")
     elseif (CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
     # this one has not been tested
       set(CMAKE_C_FLAGS "/nologo /W3 /EHsc /Gy")
       set(CMAKE_C_FLAGS_DEBUG "/MTd /Z7 /Od")
       set(CMAKE_C_FLAGS_RELEASE "/MT /O2")
       set(CMAKE_C_FLAGS_MINSIZEREL "/MT /O2")
       set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /O2")
       # Microsoft Platform SDK include files
       #set(MSC_MFC_C_INCLUDE_DIR
       #  "C:/Program Files/Microsoft Platform SDK/Include/mfc")
     endif(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
     elseif(WITH_SHARED_LIBS)
       if(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
       # not tested
         set(CMAKE_C_FLAGS "/nologo /W3 /EHa /Gy")
         set(CMAKE_C_FLAGS_DEBUG "/MDd /Z7 /Od")
         set(CMAKE_C_FLAGS_RELEASE "/MD /O2")
         set(CMAKE_C_FLAGS_MINSIZEREL "/MD /O2")
         set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MD /O2")
     elseif (CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
         set(CMAKE_C_FLAGS "/nologo /W3 /EHa /Gy")
         set(CMAKE_C_FLAGS_DEBUG "/MDd /Z7 /Od")
         set(CMAKE_C_FLAGS_RELEASE "/MD /O2")
         set(CMAKE_C_FLAGS_MINSIZEREL "/MD /O2")
         set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MD /O2")

     endif(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
    endif(NOT WITH_SHARED_LIBS)
  endif(CMAKE_C_COMPILER MATCHES cl)	
  # C++ compiler flags
  message(STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})
  if(CMAKE_CXX_COMPILER MATCHES cl)
    if(NOT WITH_SHARED_LIBS)
     if(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
       set(CMAKE_CXX_FLAGS "/nologo /W3 /EHsc /Gy")
       set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od")
       set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2")
       set(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2")
       set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /O2")
     elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
       set(CMAKE_CXX_FLAGS "/nologo /W3 /EHsc /Gy")
       set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od")
       set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2")
       set(CMAKE_CXX_FLAGS_MINSIZEREL "/MT /O2")
       set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /O2")
#       set(MSC_MFC_CXX_INCLUDE_DIR
#          "C:/Program Files/Microsoft Platform SDK/Include/mfc")       
     endif(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
    elseif(WITH_SHARED_LIBS)
     if(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
       set(CMAKE_CXX_FLAGS "/nologo /W3 /c /clr /EHa /Gy")
       set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Z7 /Od")
       set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2")
       set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O2")
       set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /O2")
     elseif(CMAKE_GENERATOR STREQUAL "Visual Studio 9 2008")
       set(CMAKE_CXX_FLAGS "/nologo /W3 /c /clr /EHa /Gy")
       set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Z7 /Od")
       set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2")
       set(CMAKE_CXX_FLAGS_MINSIZEREL "/MD /O2")
       set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /O2")
       set(CMAKE_EXE_LINKER_FLAGS "/NODEFAULTLIB:MSVCRT /NODEFAULTLIB:LIBCMT")
     endif(CMAKE_GENERATOR STREQUAL "Visual Studio 10")
    endif(NOT WITH_SHARED_LIBS)
  endif(CMAKE_CXX_COMPILER MATCHES cl)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # GNU GCC settings
  find_package( Threads )
  set(CMAKE_C_FLAGS "-O2")
  set(CMAKE_CXX_FLAGS "-O2")
  set(CMAKE_C_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  message(STATUS "CMAKE_SYSTEM_NAME " ${CMAKE_SYSTEM_NAME})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

#----------------------------------------------------------------------------
## set GTEST location for unit tests
#----------------------------------------------------------------------------
set(GTEST_ROOT ${GTEST_DIR})
set(GTEST_MSVC_SEARCH "MT")
message(STATUS "GTEST_ROOT:           " ${GTEST_ROOT})
find_package(GTest)
message(STATUS "GTEST_FOUND:          " ${GTEST_FOUND})
message(STATUS "GTEST_INCLUDE_DIRS:   " ${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_LIBRARIES:      " ${GTEST_LIBRARY})
message(STATUS "GTEST_MAIN_LIBRARIES: " ${GTEST_MAIN_LIBRARIES})
message(STATUS "GTEST_FOUND:          " ${GTEST_FOUND})
message(STATUS "GTEST_INCLUDE_DIRS:   " ${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_LIBRARIES:      " ${GTEST_LIBRARY})
message(STATUS "GTEST_MAIN_LIBRARIES: " ${GTEST_MAIN_LIBRARIES})


if(BUILD_STATIC_LIBS)
	add_library(fdfstatic STATIC fdf.c fdf.h)
	set_target_properties(fdfstatic PROPERTIES OUTPUT_NAME fdf)
endif(BUILD_STATIC_LIBS)


#----------------------------------------------------------------------------
## Build fdfpp 
#----------------------------------------------------------------------------

add_library(fdf SHARED
		${PROJECT_SOURCE_DIR}/fdf.c
		${PROJECT_SOURCE_DIR}/fdf.h
		)

add_library(fdfStatic STATIC
		${PROJECT_SOURCE_DIR}/fdf.c
		${PROJECT_SOURCE_DIR}/fdf.h
		)

set_target_properties(fdfStatic PROPERTIES OUTPUT_NAME fdf)

#set_target_properties(fdf PROPERTIES VERSION "${GENERIC_LIB_VERSION}"
#			  SOVERSION "${GENERIC_LIB_SOVERSION}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(fdfpp SHARED
        ${PROJECT_SOURCE_DIR}/fdfpp.cpp
        ${PROJECT_SOURCE_DIR}/fdfpp.h
        ${PROJECT_SOURCE_DIR}/fdf.c
        ${PROJECT_SOURCE_DIR}/fdf.h
            )                 

add_library(fdfppStatic STATIC
        ${PROJECT_SOURCE_DIR}/fdfpp.cpp
        ${PROJECT_SOURCE_DIR}/fdfpp.h
            )

set_target_properties(fdfppStatic PROPERTIES OUTPUT_NAME fdfpp)
                  


#----------------------------------------------------------------------------
## Build fdfpp unit tests
#----------------------------------------------------------------------------
message( STATUS "GTEST_FOUND: " ${GTEST_FOUND})
include_directories(${GTEST_INCLUDE_DIRS})
if( GTEST_FOUND )
    message( STATUS "GTEST_BOTH_LIBRARIES: " ${GTEST_BOTH_LIBRARIES} )
    add_executable( fdfpp_unittest1
    		    ${fdfpp_unittest_SOURCES}
		    ${fdfpp_unittest_HEADERS}
		   )
    target_link_libraries( fdfpp_unittest1
                    ${GTEST_BOTH_LIBRARIES}
		    fdf
                    fdfpp
		    ${CMAKE_THREAD_LIBS_INIT}
		    )
endif( GTEST_FOUND )
    
# ----------------------------------------------------------------------------
## Add files to CMake Install
# ----------------------------------------------------------------------------
message(STATUS "CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})
if (NOT FDFPP_NO_DEVELOPMENT)
   INSTALL ( FILES ${fdfpp_HEADERS}
             DESTINATION ./include
             COMPONENT headers
             )
   INSTALL ( TARGETS fdfStatic fdfppStatic
             ARCHIVE DESTINATION ./lib
	     COMPONENT dev_libraries
             )
   
   INSTALL ( TARGETS fdf fdfpp
   	   DESTINATION bin
	   RUNTIME DESTINATION bin
	   COMPONENT runtime_libraries
	   )
	   
endif (NOT FDFPP_NO_DEVELOPMENT)
# ----------------------------------------------------------------------------
## CMake variables to configure CPack
# ----------------------------------------------------------------------------
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "FDF/FDFPP: fast data format library and C++ interface")
set(CPACK_PACKAGE_VENDOR "University of Wisconsin-Madison")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${fdfpp_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${fdfpp_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${fdfpp_VERSION_PATCH})
# set(CPACK_PACKAGE_INSTALL_DIRECTORY "fdfpp-${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "fdfpp")
#set(CPACK_PACKAGE_EXECUTABLES "" "" )

			       
if (WIN32 AND NOT UNIX)
   # There is a bug in NSI thst does not handle full unix paths properly.
   # Make sure there is at least one set of four (4) backslashes.
   # set(CPACK_PACKAGE_ICON
   #  "${Cmake_SOURCE_DIR}/Uilities/Release\\\\InstallIcon.bmp")
   # set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
   # set(CPACK_NSIS_DISPLAY_NAME
   #"${CPACK_PACKAGE_INSTALL_DIRECTORY} FDFPP: C++ interface to FDF")
   # set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.somesite.org")
   # set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.someothersite.org")
   set(CPACK_NSIS_CONTACT "jerahmie@uwalumni.com")
   set(CPACK_NSIS_MODIFY_PATH ON)
else (WIN32 AND NOT UNIX)
   #  set(CPACK_STRIP_FILES "bin/MyExecutable")
   # set(CPACK_SOURCE_STRIP_FILES "")
endif (WIN32 AND NOT UNIX)
# set(CPACK_PACKAGE_EXECUTABLES "FDFPPEXE" "FDFPP EXE")
include(CPack)
#cpack_add_component_group(devel DISPLAY_NAME "FDFPP development files"
#				EXPANDED )
#cpack_add_component(fdfpp_devel DISPLAY_NAME
#				"FDFPP Development Libraries and headers"
#			       DESCRIPTION
#			       "FDFPP C/C++ Libraries Development Libraries and headers"
#			       GROUP devel )
