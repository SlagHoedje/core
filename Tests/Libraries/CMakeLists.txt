function(assemble_test name source)
    add_executable(Test${name} ${source})
    target_link_libraries(Test${name} ${ARGN})
    add_test(NAME Test${name} COMMAND Test${name})

    set_tests_properties(Test${name} PROPERTIES FAIL_REGULAR_EXPRESSION "FAIL")
endfunction()

add_subdirectory(Core)
  