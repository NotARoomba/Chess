import {  ReactElement, useEffect, useState } from "react";
import { ChessInstance, Square } from "chess.js";
import { Chessboard } from "react-chessboard";
import { BoardProps } from "../utils/Types";
import { BoardOrientation, PromotionPieceOption } from "react-chessboard/dist/chessboard/types";

export default function Board({isRandom, game, setGame, orientation}: BoardProps) {
    const [count, setCount] = useState(0);
    const [moveFrom, setMoveFrom] = useState("");
  const [moveTo, setMoveTo] = useState<Square | null>(null);
  const [showPromotionDialog, setShowPromotionDialog] = useState(false);
  const [rightClickedSquares, setRightClickedSquares] = useState({});
  const [optionSquares, setOptionSquares] = useState({});

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
      function onDrop(sourceSquare: Square, targetSquare: Square, piece: string) {
        const gameCopy: ChessInstance = { ...game };
        const move = gameCopy.move({
          from: sourceSquare,
          to: targetSquare,
          promotion: (piece[1].toLowerCase() ?? "q") as 'b' | 'q' | 'r' | 'n' | undefined,
        });
        setGame(gameCopy);
    
        // illegal move
        if (move === null) return false;
        // exit if the game is over
        if (game.game_over() || game.in_draw()) return false;
    
        //findBestMove();
        setMoveFrom("");
        setMoveTo(null);
        setOptionSquares({});
        return true;
      }
      function getMoveOptions(square: Square) {
        const moves = game.moves({
          square,
          verbose: true,
        });
        if (moves.length === 0) {
          setOptionSquares({});
          return false;
        }
    
        const newSquares: {[key: string]: number | string | Square | {background: string, borderRadius: string} | {background: string}} = {};
        moves.map((move) => {
          newSquares[move.to] = {
            background:
              game.get(move.to) &&
              game.get(move.to)?.color !== game.get(square)?.color
                ? "radial-gradient(circle, rgba(0,0,0,.1) 85%, transparent 85%)"
                : "radial-gradient(circle, rgba(0,0,0,.1) 25%, transparent 25%)",
            borderRadius: "50%",
          };
          return move;
        });
        newSquares[square] = {
          background: "rgba(255, 255, 0, 0.4)",
        };
        setOptionSquares(newSquares);
        return true;
      }
      function onSquareClick(square: Square) {
        setRightClickedSquares({});
    
        // from square
        if (!moveFrom) {
          const hasMoveOptions = getMoveOptions(square);
          if (hasMoveOptions) setMoveFrom(square);
          return;
        }
    
        // to square
        if (!moveTo) {
          // check if valid move before showing dialog
          const moves = game.moves({
            square: moveFrom,
            verbose: true,
          });
          const foundMove = moves.find(
            (m) => m.from === moveFrom && m.to === square
          );
          // not a valid move
          if (!foundMove) {
            // check if clicked on new piece
            const hasMoveOptions = getMoveOptions(square);
            // if new piece, setMoveFrom, otherwise clear moveFrom
            setMoveFrom(hasMoveOptions ? square : "");
            return;
          }
    
          // valid move
          setMoveTo(square);
    
          // if promotion move
          if (
            (foundMove.color === "w" &&
              foundMove.piece === "p" &&
              square[1] === "8") ||
            (foundMove.color === "b" &&
              foundMove.piece === "p" &&
              square[1] === "1")
          ) {
            setShowPromotionDialog(true);
            return;
          }
    
          // is normal move
          const gameCopy = { ...game };
          const move = gameCopy.move({
            from: moveFrom as Square,
            to: square,
            promotion: "q",
          });
    
          // if invalid, setMoveFrom and getMoveOptions
          if (move === null) {
            const hasMoveOptions = getMoveOptions(square);
            if (hasMoveOptions) setMoveFrom(square);
            return;
          }
    
          setGame(gameCopy);
    
          // setTimeout(makeRandomMove, 300);
          setMoveFrom("");
          setMoveTo(null);
          setOptionSquares({});
          return;
        }
      }
    
      function onPromotionPieceSelect(piece: PromotionPieceOption | undefined) {
        // if no piece passed then user has cancelled dialog, don't make move and reset
        if (piece) {
          const gameCopy = { ...game };
          gameCopy.move({
            from: moveFrom as Square,
            to: moveTo as Square,
            promotion: piece[1].toLowerCase() as "n" | "b" | "r" | "q" | undefined ?? "q",
          });
          setGame(gameCopy);
          // setTimeout(makeRandomMove, 300);
        }
    
        setMoveFrom("");
        setMoveTo(null);
        setShowPromotionDialog(false);
        setOptionSquares({});
        return true;
      }
    
  useEffect(() => {
    function makeAMove(move: string) {
      const gameCopy: ChessInstance = game;
      const result = gameCopy.move(move);
      setGame(gameCopy);
      return result; // null if the move was illegal, the move object if the move was legal
    }
    function makeRandomMove() {
      const possibleMoves = game.moves();
      if (game.game_over() || game.in_draw() || possibleMoves.length === 0)
          return; // exit if the game is over
      const randomIndex = Math.floor(Math.random() * possibleMoves.length);
      makeAMove(possibleMoves[randomIndex]);
    }
    if (isRandom) {
      const interval = setInterval(() => setCount(count+1), 1500)
      makeRandomMove()
      return () => clearInterval(interval)
    }
  }, [count, game, isRandom, setGame])

  return <Chessboard customPieces={customPieces()} customBoardStyle={{'borderRadius': '15px'}} onSquareClick={onSquareClick}
  onPromotionPieceSelect={onPromotionPieceSelect}
  customSquareStyles={{
    ...optionSquares,
    ...rightClickedSquares,
  }}
  promotionToSquare={moveTo}
  showPromotionDialog={showPromotionDialog} boardOrientation={orientation as BoardOrientation ??  'white'} customDarkSquareStyle={{'backgroundColor': '#253856'}} customLightSquareStyle={{'backgroundColor': '#314B72'}} position={game.fen()} onPieceDrop={onDrop} isDraggablePiece={() => !isRandom} />;
}