#ifndef SUDOKU_H
#define SUDOKU_H

#include <cinttypes>
#include <vector>
#include <iostream>

class Sudoku
{
  std::uint_fast8_t quad[9][9];

  std::uint_fast16_t options(std::uint_fast8_t x, std::uint_fast8_t y) const;
  Sudoku set(std::uint_fast8_t x, std::uint_fast8_t y, std::uint_fast8_t v) const;
  std::vector<Sudoku> solutionsCounted(int &limit) const;
  bool isValidCell(std::uint_fast8_t x, std::uint_fast8_t y) const;
  bool isValid() const;

public:
  Sudoku();
  Sudoku(const char *);

  std::vector<Sudoku> solutions(int limit = 100) const;
  friend std::ostream &operator<<(std::ostream &out, const Sudoku &v);
};

std::ostream &operator<<(std::ostream &out, const Sudoku &v);

#endif // SUDOKU_H
