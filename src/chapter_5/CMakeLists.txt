cmake_minimum_required(VERSION 3.13...3.22)

project(c5 DESCRIPTION "A custom hash table implementation"
           LANGUAGES   CXX
)

add_executable(${PROJECT_NAME} ChapterFive.cc)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Werror
        -Wextra
        "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${GA_BIN_DIR}/chapter_5"
)
