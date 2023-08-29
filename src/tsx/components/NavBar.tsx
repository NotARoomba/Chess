import React from "react";
import { Link, useLocation } from "react-router-dom";

export default function NavBar() {
    const location = useLocation();
    console.log(location.pathname == '/play');
    return <div className="h-20 flex justify-between bg-background/80 text-text">
        <Link to='/' className="group align-left flex align-middle transition">
            <img src='/img/logo.png' className="h-14 m-2 rounded-xl" />
            <div className="flex flex-col justify-center align-middle max-w-fit">
                <p className="text-left m-4 mb-0 text-4xl font-bold">Chess</p>
                <hr className=" max-w-0 group-hover:max-w-full transition-all duration-500 h-1 border-none bg-primary rounded-xl mb-4" />
            </div>
        </Link>
        <div className="align-right flex text-2xl">
        <Link to="/play" className={"text-left m-4 rounded-xl py-2 px-12 hover:bg-primary transition-all duration-300 font-semibold " + (location.pathname == '/play' ? "bg-primary" : "bg-secondary")}>Play</Link>
        <Link to="/login" className={"text-left m-4 py-2 rounded-xl px-12 hover:bg-primary transition-colors duration-300 font-semibold " + (location.pathname == '/login' ? "bg-primary" : "bg-secondary")}>Login</Link>
        </div>
    </div>
}