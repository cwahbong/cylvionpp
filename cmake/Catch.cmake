FUNCTION(PREPARE_CATCH)
  IF(TARGET Catch)
    RETURN()
  ENDIF(TARGET Catch)
  INCLUDE(ExternalProject)
  ExternalProject_Add(
    Catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    GIT_TAG c984fc3ecde60b59efa2203e82261acac8ac8502
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
  )
  MESSAGE("Catch added...")
ENDFUNCTION(PREPARE_CATCH)

FUNCTION(ADD_CATCH_TEST_EXECUTABLE target_name)
  PREPARE_CATCH()
  ADD_EXECUTABLE(${target_name} ${ARGN})
  ADD_DEPENDENCIES(${target_name} Catch)
  ADD_TEST(NAME ${target_name} COMMAND ${target_name})

  ExternalProject_Get_Property(Catch source_dir)
  TARGET_INCLUDE_DIRECTORIES(${target_name} PRIVATE ${source_dir}/include)
ENDFUNCTION(ADD_CATCH_TEST_EXECUTABLE)
