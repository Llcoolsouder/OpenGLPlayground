option (PACKAGE_DEPENDENCIES "Package with dependencies" OFF)
if (PACKAGE_DEPENDENCIES)
    message("Packaging with dependencies.")
    get_property(
        OPENGL_LIBS
        TARGET OpenGL::OpenGL
        PROPERTY IMPORTED_LOCATION)
    message("OpenGL libs are at ${OPENGL_LIBS}")
    message("GLEW libs are at ${GLEW_LIBRARIES}")
    message("GLFW is at ${GLFW3_LIBRARY}")
    install(
        FILES ${OPENGL_LIBS} ${GLEW_LIBRARIES} ${GLFW3_LIBRARY}
        DESTINATION lib)
    install(
        DIRECTORY ${GLM_INCLUDE_DIRS}/glm
        DESTINATION include)
    install(
        DIRECTORY ${GLEW_INCLUDE_DIRS}/GL
        DESTINATION include)
    install(
        DIRECTORY ${GLFW3_INCLUDE_DIR}/GLFW
        DESTINATION include)
endif(PACKAGE_DEPENDENCIES)

install(
	TARGETS ${PROJECT_NAME}
	DESTINATION lib)
install(
    FILES ${HEADER_FILES}
    DESTINATION include)