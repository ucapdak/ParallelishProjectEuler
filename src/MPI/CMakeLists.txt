add_executable(mpitest
    main.cc
)

target_link_libraries(mpitest ${MPI_LIBRARIES})
