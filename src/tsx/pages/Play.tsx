import { Chess } from 'chess.js';
import Board from '../components/Board'
import { useState } from 'react';
import GameBar from '../components/GameBar';

export default function Play() {
  const [game, setGame] = useState(new Chess());
  const [orientation, setOrientation] = useState('white');
    return <div className='flex max-h-[calc(100vh - 80px)]'>
        <Board isRandom={false} game={game} setGame={setGame} orientation={orientation} />
        <GameBar orientation={orientation} setOrientation={setOrientation} />
    </div>
}