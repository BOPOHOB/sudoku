#ifndef SUDOKU_H
#define SUDOKU_H

#include <cinttypes>
#include <QDebug>
#include <vector>

class Sudoku
{
  std::uint_fast8_t quad[9][9];

public:
  Sudoku();

  std::uint_fast16_t options(std::uint_fast8_t x, std::uint_fast8_t y) const;
  Sudoku set(std::uint_fast8_t x, std::uint_fast8_t y, std::uint_fast8_t v) const;
  void setField(const char*);

  std::vector<Sudoku> solutions() const;
  friend QDebug operator<<(QDebug out, const Sudoku& v);
};

QDebug operator<<(QDebug out, const Sudoku& v);

#endif // SUDOKU_H
