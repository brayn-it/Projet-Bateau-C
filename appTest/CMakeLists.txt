cmake_minimum_required(VERSION 3.21)
project(apptest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS graphics window system network REQUIRED)
find_package(libphysics REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME}
	${SRC_DIR}/main.cpp
	${SRC_DIR}/jeu.cpp
	${SRC_DIR}/bateau.cpp
	${SRC_DIR}/ligne.cpp
	${SRC_DIR}/obstacle.cpp
	${SRC_DIR}/menu.cpp
	${SRC_DIR}/feutricolore.cpp
	${SRC_DIR}/course.cpp
	${SRC_DIR}/dashboard.cpp
	${SRC_DIR}/resultdashboard.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
	PRIVATE
	sfml-graphics 
	sfml-audio
	libphysics::libphysics
)

if (WIN32)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
		sfml-main
	)
endif (WIN32)

target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION "$<CONFIG>/bin"
)

install(PROGRAMS
       ${CMAKE_CURRENT_SOURCE_DIR}/run.sh
       DESTINATION .)
