cmake_minimum_required(VERSION 3.15)
project(PDA_OOP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library
add_library(pda_lib
    src/Note.cpp
    src/PDA.cpp
    src/PDAItem.cpp
    src/Reminder.cpp
    src/Task.cpp
)

target_include_directories(pda_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Application
add_executable(pda_app app/main.cpp)
target_link_libraries(pda_app PRIVATE pda_lib)

# Install Rules
include(GNUInstallDirs)

install(TARGETS pda_lib pda_app
    EXPORT PDA_OOPTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Copy data directory for a "ready-to-run" experience
install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_BINDIR}/data)
# Also copy sample_data as a fallback/example
install(DIRECTORY sample_data/ DESTINATION ${CMAKE_INSTALL_BINDIR}/sample_data)

install(FILES 
    src/Note.h
    src/PDA.h
    src/PDAItem.h
    src/Reminder.h
    src/Task.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export configuration
install(EXPORT PDA_OOPTargets
    FILE PDA_OOPTargets.cmake
    NAMESPACE PDA_OOP::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PDA_OOP
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/PDA_OOPConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PDA_OOP
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/PDA_OOPConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/PDA_OOPConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/PDA_OOPConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/PDA_OOP
)
