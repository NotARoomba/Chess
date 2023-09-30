import { useState } from 'react'
import Board from '../components/Board'
import { Chess } from 'chess.js';

export default function Home() {
  const [game, setGame] = useState(new Chess());

  return (
    <div className='flex justify-center mt-12'>
      <Board game={game} setGame={setGame} isRandom />
      <div className='font-inter text-text text-left flex flex-col align-middle'>
          <p className='m-16 mb-0 text-9xl font-bold'>Chess</p>
          <p className='text-xl m-5 ml-16'>Lorem ipsum dolor sit amet consectetur adipisicing elit. Excepturi officia quis consequatur? Dolorum ea exercitationem alias. Libero officiis vero aspernatur, veritatis facere voluptatibus, culpa ut voluptates illo a dolorem repellendus.</p>
          <div className='grid'>
          <div className='group bg-secondary rounded-xl w-3/6 hover:w-11/12 flex justify-center justify-self-start ml-16 transition-width duration-500'>
          <img className='h-32 translate-x-48 rotate-2 group-hover:translate-x-0 duration-500' src='/img/pieces/p-w.svg' />
            <img className='h-32 translate-x-48 rotate-6 opacity-0 group-hover:translate-x-0 group-hover:opacity-100 duration-500' src='/img/pieces/k-w.svg' />
            <img className='h-32 translate-x-16 -rotate-3 opacity-0 group-hover:translate-x-0 group-hover:opacity-100 duration-500' src='/img/pieces/b-w.svg' />
            <img className='h-32 -translate-x-16 -rotate-6 opacity-0 group-hover:translate-x-0 group-hover:opacity-100 duration-500' src='/img/pieces/n-w.svg' />
            <img className='h-32 -translate-x-48 rotate-2 group-hover:translate-x-0 duration-500' src='/img/pieces/q-w.svg' />
            <img className='h-32 -translate-x-48 -rotate-3 group-hover:translate-x-0 duration-500' src='/img/pieces/r-w.svg' />
          </div>
            </div>
      </div>
    </div>
  )
}
