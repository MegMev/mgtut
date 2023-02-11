CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

project(mgtut)

#---------------------------------------------------------------
# external dependencies
# Load macros and functions for Gaudi-based projects
find_package(Gaudi)
set(GAUDI_GENCONF_DIR "genConfDir")
if (${Gaudi_VERSION} VERSION_LESS 35.1)
  set(GAUDI_GENCONF_DIR "genConf")
endif()

find_package(DD4hep)
find_package(ROOT)
find_package(k4FWCore)
find_package(EDM4HEP)
find_package(Geant4)
find_package(CLHEP)

#---------------------------------------------------------------
include(GNUInstallDirs)
include(CTest)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/InstallArea/ CACHE PATH
    "Install path prefix, prepended onto install directories." FORCE )
endif()

# Set up C++ Standard
# ``-DCMAKE_CXX_STANDARD=<standard>`` when invoking CMake
set(CMAKE_CXX_STANDARD "17" CACHE STRING "")

if(NOT CMAKE_CXX_STANDARD MATCHES "14|17")
  message(FATAL_ERROR "Unsupported C++ standard: ${CMAKE_CXX_STANDARD}")
endif()

# This mandatory
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#---------------------------------------------------------------
add_subdirectory(examples)

#########################
# Configure and install #
#########################
# configure_file(cmake/thismegat.sh       bin/this${PROJECT_NAME}.sh       @ONLY)
# install(FILES    ${CMAKE_BINARY_DIR}/bin/this{PROJECT_NAME}.sh DESTINATION bin )
# configure_file(cmake/thismegat_only.sh       bin/this{PROJECT_NAME}_only.sh       @ONLY)
# install(FILES    ${CMAKE_BINARY_DIR}/bin/this{PROJECT_NAME}_only.sh DESTINATION bin )


#########################
# Test #
#########################
# if(BUILD_TESTING)
#   add_subdirectory(test)
# endif()

