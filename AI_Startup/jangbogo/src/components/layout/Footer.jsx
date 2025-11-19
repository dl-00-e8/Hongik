import React from 'react';
import { useNavigate, useLocation } from 'react-router-dom';
import { Home, Map as MapIcon, Mic, ShoppingCart, Menu } from 'lucide-react';
import { useCart } from '../../contexts/CartContext';

export default function Footer() {
  const navigate = useNavigate();
  const location = useLocation();
  const { cart } = useCart();

  const navItems = [
    { path: '/', icon: Home, label: '홈' },
    { path: '/map', icon: MapIcon, label: '매장 지도' },
    { path: '/chat', icon: Mic, label: 'AI 대화', isCenter: true },
    { path: '/cart', icon: ShoppingCart, label: '장바구니', badge: cart.length },
    { path: '/menu', icon: Menu, label: '더보기' },
  ];

  return (
    <nav className="bg-white border-t border-gray-200 px-6 py-2 flex justify-around items-center h-20 pb-4 safe-area-bottom">
      {navItems.map((item) => {
        const isActive = location.pathname === item.path;
        const Icon = item.icon;

        if (item.isCenter) {
          return (
            <div key={item.path} className="relative -top-6">
              <button 
                onClick={() => navigate(item.path)}
                className={`w-16 h-16 rounded-full flex items-center justify-center shadow-lg transform transition-transform active:scale-95 ${isActive ? 'bg-blue-600 text-white ring-4 ring-blue-100' : 'bg-blue-500 text-white'}`}
              >
                <div className="flex flex-col items-center">
                  <Icon size={24} />
                  <span className="text-[10px] font-bold mt-1">{item.label}</span>
                </div>
              </button>
            </div>
          );
        }

        return (
          <button 
            key={item.path}
            onClick={() => navigate(item.path)}
            className={`flex flex-col items-center justify-center w-16 transition-colors ${isActive ? 'text-blue-600' : 'text-gray-400 hover:text-gray-600'}`}
          >
            <div className="relative">
              <Icon size={24} strokeWidth={isActive ? 2.5 : 2} />
              {item.badge > 0 && (
                <span className="absolute -top-1 -right-2 bg-red-500 text-white text-[10px] font-bold px-1.5 rounded-full min-w-[16px] text-center">
                  {item.badge}
                </span>
              )}
            </div>
            <span className="text-xs mt-1 font-medium">{item.label}</span>
          </button>
        );
      })}
    </nav>
  );
}