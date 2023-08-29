export interface BoardProps {
    fen: string;
    isRandom: boolean;
}
export interface PieceProps {
    piece: string | undefined;
    color: string| undefined;
}