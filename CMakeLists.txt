cmake_minimum_required(VERSION 3.16)
project(BC-TRAIL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Find Qt packages
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/advantech/inc
)

# Link directories
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/advantech/lib
)

# Add sources
set(SOURCES
    src/main.cpp
    src/fsm_controller.cpp
    src/gimbal_controller.cpp
    src/tracker_interface.cpp
    src/joystick_interface.cpp
    src/control_loop.cpp
    src/main_window.cpp
)

# Add headers
set(HEADERS
    include/fsm_controller.h
    include/gimbal_controller.h
    include/tracker_interface.h
    include/joystick_interface.h
    include/control_loop.h
    include/main_window.h
)

# Add UI files
set(UI_FILES
    ui/main_window.ui
)

# Add resources
set(RESOURCES
    resources/bc-trail.qrc
)

# Create executable
add_executable(bc-trail
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCES}
)

# Link against Qt and Advantech libraries
target_link_libraries(bc-trail
    PRIVATE
    Qt6::Core
    Qt6::Widgets
    Threads::Threads
    SDL2::SDL2
    biodaq
    biodaqutil
    bio1816b
    bio1824
    pthread
    rt
)

# Set real-time thread priority permissions
if(UNIX AND NOT APPLE)
    # Add installation rule to set SUID bit for real-time priority
    install(TARGETS bc-trail
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                  GROUP_READ GROUP_EXECUTE
                  WORLD_READ WORLD_EXECUTE SETUID
    )
endif()
