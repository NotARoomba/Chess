import React from 'react'
import Board from '../components/Board'

export default function Home() {

  return (
    <div className='flex justify-center'>
      <Board isRandom fen='4r1k1/p1prnpb1/Pp1pq1pp/3Np2P/2P1P3/R4N2/1PP2PP1/3QR1K1 w - - 2 20' />
      <div className='font-inter text-text text-left flex flex-col align-middle'>
          <p className='m-16 mb-0 text-9xl font-bold'>Chess</p>
          <p className='text-lg m-5 ml-16'>Lorem ipsum dolor sit amet consectetur adipisicing elit. Excepturi officia quis consequatur? Dolorum ea exercitationem alias. Libero officiis vero aspernatur, veritatis facere voluptatibus, culpa ut voluptates illo a dolorem repellendus.</p>
      </div>
    </div>
  )
}
