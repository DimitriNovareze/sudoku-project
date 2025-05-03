cmake_minimum_required(VERSION 3.16)

project(Project_Sudoku VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appProject_Sudoku
    main.cpp
)

qt_add_qml_module(appProject_Sudoku
    URI Project_Sudoku
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES damiersudoku.h damiersudoku.cpp
    SOURCES
    QML_FILES
    QML_FILES Carre.qml
    QML_FILES Level.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appProject_Sudoku PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appProject_Sudoku
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appProject_Sudoku
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appProject_Sudoku
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
