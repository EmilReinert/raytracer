add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)
#RAYTRACER
add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)
#SDF GENERATOR
add_executable(sdf_generator sdf_generator.cpp)

target_link_libraries(sdf_generator ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(sdf_generator glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS sdf_generator DESTINATION .)

# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  ${FRAMEWORK_NAME}
  )

#ANIMATION
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/emil/Documents/RAYTRACER/program/raytracer/build/video")
add_executable(animation animation.cpp)


target_link_libraries(animation ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(animation glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS animation DESTINATION .)
