import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { Battery, Wifi, PlayCircle, StopCircle } from 'lucide-react';

export default function Header() {
  const navigate = useNavigate();
  const [isMoving, setIsMoving] = useState(false);

  return (
    <header className="bg-slate-900 text-white px-6 py-3 flex justify-between items-center shadow-md z-10">
      <div className="flex items-center space-x-4">
        <button 
          onClick={() => navigate('/')}
          className="flex flex-col hover:opacity-80 transition-opacity cursor-pointer"
        >
          <span className="text-lg font-bold text-blue-400">Jangbogo</span>
          <span className="text-xs text-gray-400">ID: #CART-2049</span>
        </button>
        <div className={`px-3 py-1 rounded-full text-xs font-semibold flex items-center gap-2 ${isMoving ? 'bg-green-600 animate-pulse' : 'bg-gray-700'}`}>
          {isMoving ? <><PlayCircle size={14} /> 자율주행 중</> : <><StopCircle size={14} /> 대기 모드</>}
        </div>
      </div>
      <div className="flex items-center space-x-6">
        <div className="flex items-center gap-2 text-sm">
          <span className="text-gray-400">Power Assist</span>
          <span className="w-2 h-2 rounded-full bg-green-500"></span>
        </div>
        <div className="flex items-center gap-1">
          <Wifi size={18} className="text-blue-400" />
          <span className="text-xs">IPS Connected</span>
        </div>
        <div className="flex items-center gap-1">
          <Battery size={20} className="text-green-400" />
          <span className="text-sm font-bold">82%</span>
        </div>
      </div>
    </header>
  );
}