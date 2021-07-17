cmake_minimum_required(VERSION 3.0.0)
project(kscsv VERSION 0.1.0)

add_executable(kscsv
    main.c
    # example_read_loop.c
    # example_read.c
    # example_write.c
    kscsv.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
