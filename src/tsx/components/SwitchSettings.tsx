import { capitalize } from "../utils/Functions";
import { SwitchSettingsProps } from "../utils/Types";

export default function SwitchSettings({title, options, selected, setSelected}: SwitchSettingsProps) {
    return <div className="w-10/12 justify-center m-auto">
        <div className="text-3xl text-text">
            {title}
        </div>
        <div className="flex text-2xl mt-2 justify-around bg-primary/20 rounded-full p-3">
        {options.map((o, i) => (<div key={i} className={(o === selected ? 'bg-primary/50' : 'bg-transparent') + ' cursor-pointer h-full p-3 w-full rounded-full transition-all duration-300 from:bg-transparent to:bg-primary/50'} onClick={() => setSelected(o)}>
            {capitalize(o)}
        </div>))}
        </div>
    </div>
}