add_executable(tutorial01_first_window tutorial01.cpp)
target_link_libraries(tutorial01_first_window ${ALL_LIBS})

set(DST ${TASK_1_INSTALL_DIR}/tutorial01_first_window)
install(TARGETS tutorial01_first_window DESTINATION ${DST})
