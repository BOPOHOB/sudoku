/* tslint:disable */
/* eslint-disable */
export type Board = [
    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],

    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],

    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],
    [number,number,number, number,number,number, number,number,number],
];
export type solve = (input: Board) => Board[];
type Solver = Promise<solve>;
export default () => Solver;
