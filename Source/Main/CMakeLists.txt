add_executable(Main main.cpp)
target_link_libraries(Main Core)
target_compile_options(Main PRIVATE -Werror -Wall -Wextra)
