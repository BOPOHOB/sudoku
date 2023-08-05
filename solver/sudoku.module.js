const Sudoku = require('./sudoku.js');

const parse = (s) =>
  s.split('\n').filter(v => v.length === 81)
    .map(v => v.split('').map(v => parseInt(v, 10)))
    .map(v => new Array(9).fill(null).map((_, i) =>
      new Array(9).fill(null).map((__, j) => v[j * 9 + i])
    ));

const transpose = (matrix) => {
  const result = [];
  if (matrix.length === 0) {
    return [];
  }
  result.length = matrix[0].length;
  for (let i = 0; i < matrix.length; ++i) {
    console.assert(matrix[i].length === matrix[0].length);
    result[i] = new Array(matrix.length);
    for (let j = 0; j < matrix[i].length; ++j) {
      result[i][j] = matrix[j][i];
    }
  }
  return result;
}

const dump = (matrix) => transpose(matrix).map(r => r.map(v => v >= 0 && v <= 9 ? `${v}` : ' ').join('')).join('');

function init() {
  return Sudoku().then(instance => (matrix) => parse(instance.ccall(
    'solve',
    'string',
    ['string'],
    [dump(matrix)]
  )));
}

module.exports = init;
