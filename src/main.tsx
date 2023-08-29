import React from 'react'
import ReactDOM from 'react-dom/client'
import { BrowserRouter, Route, Routes } from "react-router-dom";


import "./css/index.css";
import Home from "./tsx/pages/Home";
import Play from './tsx/pages/Play';
import Error from './tsx/pages/Error';
import NavBar from './tsx/components/NavBar';

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <BrowserRouter>
      <NavBar />
      <Routes>
        <Route path='/' element={<Home />} errorElement={<Error />} />
        <Route path='/play' element={<Play />} errorElement={<Error />} />
        <Route path='*' element={<Error />}/>
      </Routes>
    </BrowserRouter>
  </React.StrictMode>,
)
