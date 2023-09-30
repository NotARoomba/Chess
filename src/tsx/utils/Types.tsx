import { ChessInstance } from "chess.js";

export enum ChessColor {
    WHITE = 'white',
    BLACK = 'black',
}
export interface BoardProps {
    isRandom: boolean;
    game: ChessInstance;
    setGame: (a: ChessInstance) => void;
    orientation?: string;
}
export interface PieceProps {
    piece: string | undefined;
    color: string| undefined;
}
export interface GameBarProps {
    orientation: string;
    setOrientation: (orientation: string) => void;
}
export interface SwitchSettingsProps {
    title: string;
    options: string[];
    selected: string;
    setSelected: (newSelect: string) => void;
}