import React from 'react'

export default function Error() {
    return <div className='text-text flex flex-col align-middle text-center mt-24'>
        <p className='font-bold my-5 text-9xl animate-pulse duration-1000'>
            404
        </p>
        <p className='text-4xl'>
            Page not found
        </p>
    </div>
}