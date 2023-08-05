#include "sudoku.h"

#include <cassert>
#include <iostream>

Sudoku::Sudoku()
    : quad{
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 0},
      }
{
}

std::uint_fast16_t Sudoku::options(std::uint_fast8_t x, std::uint_fast8_t y) const
{
  std::uint_fast16_t result(~0);
  const std::uint_fast8_t i(x / 3 * 3);
  const std::uint_fast8_t j(y / 3 * 3);
  // the rect
  result &= ~(1 << quad[i][j]);
  result &= ~(1 << quad[i][j + 1]);
  result &= ~(1 << quad[i][j + 2]);
  result &= ~(1 << quad[i + 1][j]);
  result &= ~(1 << quad[i + 1][j + 1]);
  result &= ~(1 << quad[i + 1][j + 2]);
  result &= ~(1 << quad[i + 2][j]);
  result &= ~(1 << quad[i + 2][j + 1]);
  result &= ~(1 << quad[i + 2][j + 2]);
  // the row and column
  for (std::uint_fast8_t k(0); k < 9; ++k)
  {
    result &= ~(1 << quad[k][y]);
    result &= ~(1 << quad[x][k]);
  }
  return result & 0b1111111110;
}

Sudoku Sudoku::set(std::uint_fast8_t x, std::uint_fast8_t y, std::uint_fast8_t v) const
{
  Sudoku result(*this);
  result.quad[x][y] = v;
  return result;
}

std::vector<Sudoku> Sudoku::solutionsCounted(int &limit) const
{
  for (std::uint_fast8_t i(0); i < 9; ++i)
  {
    for (std::uint_fast8_t j(0); j < 9; ++j)
    {
      if (quad[i][j] == 0)
      {
        const std::uint_fast16_t options(this->options(i, j));
        if (options == 0)
        {
          return {};
        }
        std::vector<Sudoku> results;
        for (std::uint_fast8_t val(1); val <= 9; ++val)
        {
          if (options & (1 << val))
          {
            const std::vector<Sudoku> hypothesis(this->set(i, j, val).solutionsCounted(limit));
            if (!hypothesis.empty())
            {
              results.insert(results.end(), hypothesis.begin(), hypothesis.end());
            }
          }
          if (!limit)
          {
            return results;
          }
        }
        return results;
      }
    }
  }
  --limit;
  return {*this};
}

bool Sudoku::isValidCell(std::uint_fast8_t x, std::uint_fast8_t y) const
{
  const std::uint_fast8_t v(quad[x][y]);
  if (v == 0)
  {
    return true;
  }
  const std::uint_fast8_t a(x / 3 * 3);
  const std::uint_fast8_t b(y / 3 * 3);
  // the rect
  for (std::uint_fast8_t i(a); i != a + 3; ++i)
  {
    for (std::uint_fast8_t j(b); j != b + 3; ++j)
    {
      if ((i != x || j != y) && quad[i][j] == v)
      {
        return false;
      }
    }
  }
  // the row and column
  for (std::uint_fast8_t k(0); k < 9; ++k)
  {
    if (k != x && quad[k][y] == v)
    {
      return false;
    }
    if (k != y && quad[x][k] == v)
    {
      return false;
    }
  }
  return true;
}

bool Sudoku::isValid() const
{
  for (int i(0); i < 9; ++i)
  {
    for (int j(0); j < 9; ++j)
    {
      if (!isValidCell(i, j))
      {
        return false;
      }
    }
  }
  return true;
}

std::vector<Sudoku> Sudoku::solutions(int limit) const
{
  if (!isValid())
  {
    return {};
  }
  return solutionsCounted(limit);
}

Sudoku::Sudoku(const char *m)
{
  int p(0);
  while (*m)
  {
    if (*m == ' ' || (*m >= '0' && *m <= '9'))
    {
      quad[p % 9][p / 9] = *m == ' ' ? 0 : *m - '0';
      ++p;
    }
    ++m;
  }
  assert(p == 81);
}

std::ostream &operator<<(std::ostream &out, const Sudoku &v)
{
  for (int i(0); i < 9; ++i)
  {
    if (i % 3 == 0)
    {
      out << "-------------" << std::endl;
    }
    out << '|';
    for (int j(0); j < 9; ++j)
    {
      out << (v.quad[j][i] == 0 ? ' ' : static_cast<char>('0' + v.quad[j][i]));
      if (j % 3 == 2)
      {
        out << '|';
      }
    }
    out << std::endl;
  }
  out << "-------------" << std::endl;
  return out;
}
