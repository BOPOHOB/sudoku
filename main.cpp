#include <QCoreApplication>

#include "sudoku.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Sudoku v;
  v.setField("  7|   |   "
             " 8 | 6 |3 2"
             "   |21 |6  "
             "-----------"
             "  2|  8| 96"
             "  4| 3 |   "
             "   |6 9|   "
             "-----------"
             "17 |  2| 35"
             "9  |   |2  "
             "  8|   | 1 ");

  std::vector<Sudoku> solutions(v.solutions());
  qDebug() << "solutions" << solutions.size();
  if (solutions.size() > 10) {
    return 0;
  }
  for (const Sudoku& v : solutions) {
    qDebug() << "solution\n" << v;
  }

  return 0;
}
