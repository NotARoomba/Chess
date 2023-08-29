import { useEffect, useState } from "react";
import { BoardProps } from "../utils/Types";
import { Chess } from "chess.js";
import Piece from "./Piece";

export default function RandomBoard({isRandom, fen}: BoardProps) {
    console.log(isRandom)
    // make a chess board using the fen
    const [game, setGame] = useState<Chess>(new Chess());
    const [count, setCount] = useState(0);
    useEffect(() => {
        if (!isRandom) game.load(fen);
        else {
            const interval = setInterval(() => setCount(count+1), 1500)
            const moves = game.moves()
            const move = moves[Math.floor(Math.random() * moves.length)]
            game.move(move)
            return () => clearInterval(interval)
        }
    }, [isRandom, fen, game, count])
    return <div className="h-4/5 aspect-square mt-10">
       {game.board().map((row, i) => {
        return <div className="flex">{row.map((v, j) => {
            return (<div key={i+j*2} className={'w-20 aspect-square ' + ((i+j)%2==0?'bg-text':'bg-primary')}>
                <Piece piece={v?.type} color={v?.color} />
            </div>)
        })}</div>
       })}
    </div>
}