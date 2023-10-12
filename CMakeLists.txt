# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project ("Calculator")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Calculator "Source.cpp" "App.cpp" "App.h" "Func.cpp" "Func.h" "DllCatalogue.h" "DllCatalogue.cpp" "Funcs.h" "Funcs.cpp" "Expression.h" "Expression.cpp" "Associativity.h" "CalculationMessage.h" "CalculationMessage.cpp" "Precedence.h" "StringUtils.h" "StringUtils.cpp" "Tokens.h" "Tokens.cpp")

add_custom_target(LoadPlugins ALL)

add_custom_command(
TARGET LoadPlugins
COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/plugins
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins

)

add_dependencies("Calculator" LoadPlugins)