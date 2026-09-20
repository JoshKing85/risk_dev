cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for sheenbidi")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/joshk/programming/risk_V1/out/build/x64-Debug/_deps/sheenbidi-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe]====] [====[-DSHEENBIDI_DIR=C:/Users/joshk/programming/risk_V1/out/build/x64-Debug/_deps/sheenbidi-src]====] [====[-P]====] [====[C:/Users/joshk/programming/risk_V1/out/build/x64-Debug/_deps/sfml-src/tools/sheenbidi/PatchSheenBidi.cmake]====]
)

endblock()
