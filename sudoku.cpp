#include "sudoku.h"

#include <cassert>

Sudoku::Sudoku()
  : quad{
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
      }
{

}

std::uint_fast16_t Sudoku::options(std::uint_fast8_t x, std::uint_fast8_t y) const
{
  std::uint_fast16_t result(~0);
  {
    std::uint_fast8_t a(x / 3 * 3 + 3);
    std::uint_fast8_t b(y / 3 * 3 + 3);
    for (std::uint_fast8_t i(a - 3); i < a; ++i) {
      for (std::uint_fast8_t j(b - 3); j < b; ++j) {
        const std::uint_fast8_t v(quad[i][j]);
        if (v) {
          result &= ~(1 << v);
        }
      }
    }
  }
  {
    for (std::uint_fast8_t i(0); i < 9; ++i) {
      {
        const std::uint_fast8_t v(quad[i][y]);
        if (v) {
          result &= ~(1 << v);
        }
      }
      {
        const std::uint_fast8_t v(quad[x][i]);
        if (v) {
          result &= ~(1 << v);
        }
      }
    }
  }
  return result & 0b1111111111;
}

Sudoku Sudoku::set(std::uint_fast8_t x, std::uint_fast8_t y, std::uint_fast8_t v) const
{
  Sudoku result(*this);
  result.quad[x][y] = v;
  return result;
}

std::vector<Sudoku> Sudoku::solutions() const
{
  for (std::uint_fast8_t i(0); i < 9; ++i) {
    for (std::uint_fast8_t j(0); j < 9; ++j) {
      if (quad[i][j] == 0) {
        const std::uint_fast16_t options(this->options(i, j));
        if (options == 1) {
          return {};
        }
        std::vector<Sudoku> results;
        for (std::uint_fast8_t val(1); val <= 9; ++val) if (options & (1 << val)) {
          const std::vector<Sudoku> hypotize(this->set(i, j, val).solutions());
          if (!hypotize.empty()) {
            results.insert(results.end(), hypotize.begin(), hypotize.end());
          }
        }
        return results;
      }
    }
  }
  return { *this };
}

void Sudoku::setField(const char* m)
{
  int p(0);
  while (*m) {
    if (*m == ' ' || (*m >= '0' && *m <= '9')) {
      if (*m != ' ') {
        quad[p % 9][p / 9] = *m - '0';
      }
      ++p;
    }
    ++m;
  }
  assert(p == 81);
}

QDebug operator <<(QDebug j, const Sudoku& v)
{
  for (int i(0); i < 9; ++i) {
    QString s;
    QTextStream out(&s);
    for (int j(0); j < 9; ++j) {
      if(v.quad[j][i] != 0) {
        out << v.quad[j][i];
      } else {
        out << ' ';
      }
      if (j % 3 == 2) {
        out << '|';
      }
    }
    if (i % 3 == 0) {
      j.nospace() << "------------\n";
    }
    j.nospace() << s.toStdString().c_str() << '\n';
  }
  return j;
}
