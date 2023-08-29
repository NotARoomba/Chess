import {  ReactElement, useEffect, useState } from "react";
import { Chess } from "chess.js";
import { Chessboard } from "react-chessboard";

export default function RandomBoard() {
    const [game, setGame] = useState(new Chess());
    const [count, setCount] = useState(0);

    const pieces = [
        "wP",
        "wN",
        "wB",
        "wR",
        "wQ",
        "wK",
        "bP",
        "bN",
        "bB",
        "bR",
        "bQ",
        "bK",
      ];
      const customPieces = () => {
        const returnPieces: {[key: string]: ({ squareWidth }: {squareWidth: string}) => ReactElement} = {};
        pieces.map((p) => {
          returnPieces[p] = ({ squareWidth }) => (
            <div
              style={{
                width: squareWidth,
                height: squareWidth,
                backgroundImage: `url(/img/pieces/${p[1].toLowerCase()}-${p[0]}.svg)`,
                backgroundSize: "100%",
                // filter: p[0]=='b'?'invert(8%) sepia(0%) saturate(1364%) hue-rotate(142deg) brightness(100%) contrast(100%)':''
              }}
            />
          );
          return null;
        });
        return returnPieces;
      };

  useEffect(() => {
    function makeAMove(move: string | {from: string, to: string, promotion: string}) {
        const gameCopy: Chess = game;
        const result = gameCopy.move(move);
        setGame(gameCopy);
        return result; // null if the move was illegal, the move object if the move was legal
    }

    function makeRandomMove() {
        const possibleMoves = game.moves();
        if (game.isGameOver() || game.isDraw() || possibleMoves.length === 0)
            return; // exit if the game is over
        const randomIndex = Math.floor(Math.random() * possibleMoves.length);
        makeAMove(possibleMoves[randomIndex]);
    }
    const interval = setInterval(() => setCount(count+1), 1500)
    makeRandomMove()
    return () => clearInterval(interval)
  }, [count, game])

  return <Chessboard customPieces={customPieces()} customBoardStyle={{'borderRadius': '15px'}} customDarkSquareStyle={{'backgroundColor': '#253856'}} customLightSquareStyle={{'backgroundColor': '#314B72'}} position={game.fen()} isDraggablePiece={() => false} />;
}