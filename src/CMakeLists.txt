set(INCROOT ${PROJECT_SOURCE_DIR}/include/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/)

set(FILES_HEADER
)

set(FILES_SRC
	${SRCROOT}/main.cpp
)

add_executable(main main.cpp)
target_link_libraries(main ${LIBS})
