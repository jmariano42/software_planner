# CMakeList.txt : CMake project for software_planner_transpiler, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (software_planner_transpiler "software_planner_transpiler.cpp" "software_planner_transpiler.h"     "abstract_syntax_tree.h" "code_generator.h" "lexer.h" "parser.h" "token_type.h" "token.h" "token_modifier.h" "token_scope.h" "token_data_type.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET software_planner_transpiler PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
