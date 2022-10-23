cmake_minimum_required(VERSION 3.0)

project(image)

add_executable(${PROJECT_NAME} main.cpp)


find_package(SDL2 REQUIRED)

include(FindPkgConfig)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

if(PSP)
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
    )
endif()

file(COPY hello.png DESTINATION ${CMAKE_BINARY_DIR})

