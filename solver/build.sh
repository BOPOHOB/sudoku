# https://stackoverflow.com/questions/59487224/webpack-throws-error-with-emscripten-cant-resolve-fs
em++ main.cpp sudoku.cpp -s "SINGLE_FILE=1" -O3 -s ENVIRONMENT='web' -s NO_EXIT_RUNTIME=1 -o sudoku.js -s "EXPORTED_RUNTIME_METHODS=['ccall']" -sMODULARIZE
