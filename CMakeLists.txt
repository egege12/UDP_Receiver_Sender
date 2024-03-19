cmake_minimum_required(VERSION 3.16)

project(UDP_Receiver_Sender VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)


set(PROJECT_SOURCES
    main.cpp
    socketudp.cpp
    socketudp.h
    comUdpData.h
    InternalOp.h
    qml.qrc
    comDataTableModel.h
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(appUDP_Receiver_Sender
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(appUDP_Receiver_Sender SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(appUDP_Receiver_Sender
          ${PROJECT_SOURCES}
        )
    endif()
endif()


set_target_properties(appUDP_Receiver_Sender PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appUDP_Receiver_Sender
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Network
)

install(TARGETS appUDP_Receiver_Sender
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
