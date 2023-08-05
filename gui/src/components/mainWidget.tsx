import { type FC, useCallback,useEffect, useMemo, useRef,useState } from 'react';
import { ClearOutlined, EyeOutlined } from '@ant-design/icons';
import { Button, Pagination, Popover, Switch } from 'antd';
import type { TooltipPlacement } from 'antd/es/tooltip';
import classNames from 'classnames';
import { FullScreenLoader } from 'elements/fullScreen/fullScreen';
import Sudoku, { type Board, type solve } from 'sudoku';

import cn from './mainWidget.module.less';

const Selector: FC<{onSelected: (v: number) => void; clearable: boolean}> = ({ onSelected, clearable }) => (
  <div className={cn.picker}>
    {new Array(9).fill(null).map((_, id) => (
      <Button key={id} onClick={() => onSelected(id + 1)}>{id + 1}</Button>
    ))}
   {clearable && <Button  icon={<ClearOutlined />} onClick={() => onSelected(0)} />}
  </div>
)

const placement = (row: number, col: number): TooltipPlacement => [
  ['rightTop', 'bottom', 'leftTop'],
  ['right', 'bottom', 'left'],
  ['rightBottom', 'top', 'leftBottom'],
][Math.floor(col / 3)][Math.floor(row / 3)] as TooltipPlacement;

type NumberWgtProps = {
  val: number;
  col: number;
  row: number;
  showDefault: boolean;
  onValueChanged: (value: number, row: number, col: number) => void;
  valSuggest?: number;
};
const NumberWgt: FC<NumberWgtProps> = ({ val, col, row, onValueChanged, valSuggest, showDefault }) => {
  const [isPopupOpen, setPopupOpen] = useState<boolean>(false);
  const onSelected = useCallback((v: number) => {
    onValueChanged(v, col, row);
    setPopupOpen(false);
  }, [col, row, onValueChanged, setPopupOpen]);
  const isEmpty = val === 0;
  const [showSuggested, setShowSuggested] = useState(false);
  const isVisible = showSuggested || showDefault;
  if (!isVisible && isEmpty) {
    return <Button className={classNames(cn.cell, cn.computed)} icon={<EyeOutlined />} onClick={() => setShowSuggested(true)} />;
  }
  return (
    <Popover placement={placement(row, col)} open={isPopupOpen} onOpenChange={setPopupOpen} content={<Selector clearable={!isEmpty} onSelected={onSelected} />} trigger="click">
      <Button className={classNames(cn.cell, {[cn.computed]: isEmpty})} onClick={() => setPopupOpen(true)}>{isEmpty ? valSuggest : val}</Button>
    </Popover>
  );
};

const defaultStateArray = `
  7|   |   |
 8 | 6 |3 2|
   |21 |6  |
###########|
  2|  8| 96|
  4| 3 |   |
   |6 9|   |
###########|
17 |  2| 35|
9  |   |2  |
  8|   | 1 |
`.split('').filter(v => v === ' ' || isFinite(parseInt(v, 10))).map(v => parseInt(v, 10)).map(v => isFinite(v) ? v : 0);
const defaultState = new Array(9).fill(null).map((_, row) => defaultStateArray.slice(row * 9, row * 9 + 9)) as Board;

const MainWidget: FC = () => {
  const solver = useRef<null | solve>(null);
  const board = useMemo<Board>(() => defaultState, []);
  const [currentSolution, setCurrentSolution] = useState<number>(0);
  const [solutions, setSolutions] = useState<Board[]>([]);
  const [showSolution, setShowSolution] = useState<boolean>(true);
  const recalculate = useCallback(() => {
    if (solver.current) {
      const s = solver.current(board);
      setSolutions(s);
      if (s.length <= currentSolution && s.length > 0) {
        setCurrentSolution(s.length - 1);
      }
    }
  }, [setSolutions, board, currentSolution]);
  const clearAll = useCallback(() => {
    board.map(col => col.fill(0));
    recalculate();
  }, [board, recalculate]);
  const setValue = useCallback((value: number, row: number, col: number) => {
    board[row][col] = value;
    recalculate();
  }, [board, recalculate]);
  useEffect(() => {
    Sudoku().then((f: solve) => {
      solver.current = f;
      recalculate();
    });
  }, [recalculate]);
  if (solver.current === null) {
    return <FullScreenLoader>Solver compiling</FullScreenLoader>;
  }
  const cells = board.map((col, colId) => col.map((val, rowId) => (
    <NumberWgt
      key={`${rowId}_${colId}`}
      val={val}
      col={colId}
      row={rowId}
      onValueChanged={setValue}
      showDefault={showSolution}
      valSuggest={solutions[currentSolution]?.[rowId][colId]}
    />
  ))).flat();
  return (
    <div className={cn.wrap}>
      <div className={cn.manager}>
        <Pagination current={currentSolution + 1} pageSize={1} onChange={v => setCurrentSolution(v - 1)} simple total={solutions.length} />
        <Button icon={<ClearOutlined />} onClick={clearAll} />
        <Switch checkedChildren="show" unCheckedChildren="hide" checked={showSolution} onChange={setShowSolution} />
      </div>
      <div className={cn.table}>
        {
          new Array(3).fill(null).map((_, col) => new Array(3).fill(null).map((__, row) => (
            <div key={`${row}_${col}`}>
              {new Array(9).fill(null).map((___, cel) => cells[col * 3 * 9 + row * 3 + (cel % 3) + Math.floor(cel / 3) * 9])}
            </div>
          ))).flat()
        }
      </div>
    </div>
  );
};

export { MainWidget };

