cmake_minimum_required(VERSION 3.16)

project(UDP_Receiver_Sender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup()

qt_add_executable(appUDP_Receiver_Sender
    main.cpp
    socketudp.cpp
    socketudp.h
)

qt_add_qml_module(appUDP_Receiver_Sender
    URI UDP_Receiver_Sender
    VERSION 1.0
    QML_FILES Main.qml
)

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
