file(GLOB source "*.cpp")
add_library(Src ${source})
target_include_directories(Src PUBLIC ${PROJECT_SOURCE_DIR}/include)