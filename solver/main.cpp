#include "sudoku.h"

#include <emscripten/emscripten.h>

char *dump(const std::vector<Sudoku> &results)
{
  char *const d = new char[results.size() * (sizeof(Sudoku) + 1) + 1];
  char *it = d;
  for (const Sudoku &result : results)
  {
    *static_cast<Sudoku *>(static_cast<void *>(it)) = result;
    for (int i(0); i < sizeof(Sudoku); ++i)
    {
      *it += '0';
      ++it;
    }
    *it = '\n';
    ++it;
  }
  *it = 0;
  return d;
}

extern "C" EMSCRIPTEN_KEEPALIVE char *solve(char *board)
{
  return dump(Sudoku(board).solutions());
}
