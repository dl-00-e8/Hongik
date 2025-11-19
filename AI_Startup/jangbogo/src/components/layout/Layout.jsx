import React from 'react';
import { Outlet } from 'react-router-dom';
import Header from './Header';
import Footer from './Footer';

export default function Layout() {
  return (
    <div className="flex flex-col h-screen bg-gray-100 font-sans text-gray-800 overflow-hidden select-none">
      <Header />
      <main className="flex-1 overflow-hidden relative bg-white">
        <Outlet />
      </main>
      <Footer />
    </div>
  );
}