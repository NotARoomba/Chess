import { GameBarProps } from "../utils/Types";
import SwitchSettings from "./SwitchSettings";

export default function GameBar({orientation, setOrientation}: GameBarProps) {
    return <div className="w-7/12 text-text bg-secondary ml-16 text-center p-3 font-bold rounded-2xl">
        <div className=" text-5xl">
            {/* {game.turn() === 'b' ? 'Black' : 'White'} to move */}
            Settings
        </div>
        <hr className=" border-2 rounded-2xl my-4" />
        <SwitchSettings title="Switch Color" selected={orientation} setSelected={setOrientation} options={['white', 'black']} />
    </div>
}