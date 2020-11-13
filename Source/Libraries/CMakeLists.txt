function(assemble_lib target_name)
    add_library(${target_name} ${ARGN})

    target_compile_options(${target_name} PRIVATE -Werror -Wall -Wextra)
endfunction()

add_subdirectory(Core)
