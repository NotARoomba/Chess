import {PieceProps} from '../utils/Types'

export default function Piece({piece, color}: PieceProps) {
    return <>{piece?<img src={`/img/pieces/${piece}-${color}.svg`} />:<></>}</>
}