import React from "react";

export default function NavBar() {
    return <div className="h-16 flex justify-between">
        <div className="align-left">
            <p className="text-stone-100 text-left m-4 text-4xl">Chess</p>
        </div>
        <div className="align-right flex text-2xl">
        <p className="text-stone-100 text-left m-4">Play</p>
        <p className="text-stone-100 text-left m-4">Login</p>
        </div>
    </div>
}