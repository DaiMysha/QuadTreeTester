set(INCROOT ${PROJECT_SOURCE_DIR}/include/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/)

set(FILES_HEADER
)

set(FILES_SRC
	${SRCROOT}/main.cpp
)

add_executable(main ${FILES_HEADER} ${FILES_SRC})
add_executable(bench benchmark.cpp)
target_link_libraries(main ${LIBS})
