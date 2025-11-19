import React from 'react';
import { useNavigate } from 'react-router-dom';
import { 
  Home, 
  Map, 
  MessageSquare, 
  ShoppingCart, 
  User, 
  Bell, 
  Heart, 
  Clock, 
  Settings, 
  HelpCircle,
  ChevronRight,
  LogIn,
  UserPlus
} from 'lucide-react';

export default function MenuPage() {
  const navigate = useNavigate();

  const menuSections = [
    {
      title: '주요 기능',
      items: [
        { icon: Home, label: '홈', path: '/', color: 'blue' },
        { icon: Map, label: '매장 지도', path: '/map', color: 'green' },
        { icon: MessageSquare, label: 'AI 대화', path: '/chat', color: 'purple' },
        { icon: ShoppingCart, label: '장바구니', path: '/cart', color: 'orange' },
      ]
    },
    {
      title: '마이 페이지',
      items: [
        { icon: User, label: '내 정보', path: '/profile', color: 'indigo', disabled: true },
        { icon: Clock, label: '주문 내역', path: '/orders', color: 'pink', disabled: true },
        { icon: Heart, label: '찜한 상품', path: '/favorites', color: 'red', disabled: true },
      ]
    },
    {
      title: '설정 및 도움말',
      items: [
        { icon: Bell, label: '알림 설정', path: '/notifications', color: 'yellow', disabled: true },
        { icon: Settings, label: '환경 설정', path: '/settings', color: 'gray', disabled: true },
        { icon: HelpCircle, label: '고객 지원', path: '/support', color: 'teal', disabled: true },
      ]
    }
  ];

  const handleNavigation = (item) => {
    if (item.disabled) {
      return; // 비활성화된 항목은 아무 동작 안 함
    }
    navigate(item.path);
  };

  return (
    <div className="h-full overflow-y-auto bg-gray-50 pb-20">
      {/* Header Section */}
      <div className="bg-gradient-to-r from-blue-600 to-indigo-600 text-white p-6 rounded-b-[2rem] shadow-lg mb-6">
        <h1 className="text-2xl font-bold mb-2">더보기</h1>
        <p className="text-sm opacity-90">스마트 카트의 모든 기능을 확인하세요</p>
      </div>

      {/* Login/Signup Section */}
      <div className="px-6 mb-6">
        <div className="bg-white rounded-2xl p-5 shadow-sm border border-gray-100">
          <div className="flex items-center gap-4 mb-4">
            <div className="w-16 h-16 bg-gray-200 rounded-full flex items-center justify-center">
              <User size={32} className="text-gray-400" />
            </div>
            <div className="flex-1">
              <p className="font-bold text-gray-800 text-lg">로그인이 필요합니다</p>
              <p className="text-xs text-gray-500">더 많은 혜택을 받아보세요</p>
            </div>
          </div>
          
          <div className="flex gap-3">
            <button className="flex-1 bg-blue-600 text-white py-3 rounded-xl font-bold hover:bg-blue-700 transition-colors flex items-center justify-center gap-2">
              <LogIn size={18} />
              로그인
            </button>
            <button className="flex-1 bg-gray-100 text-gray-700 py-3 rounded-xl font-bold hover:bg-gray-200 transition-colors flex items-center justify-center gap-2">
              <UserPlus size={18} />
              회원가입
            </button>
          </div>
          
          <p className="text-xs text-center text-gray-400 mt-3">
            ⚠️ 추후 업데이트 예정입니다
          </p>
        </div>
      </div>

      {/* Menu Sections */}
      <div className="px-6 space-y-6">
        {menuSections.map((section, idx) => (
          <div key={idx}>
            <h2 className="text-sm font-bold text-gray-500 mb-3 px-2">{section.title}</h2>
            <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
              {section.items.map((item, itemIdx) => {
                const Icon = item.icon;
                const isDisabled = item.disabled;
                
                return (
                  <button
                    key={itemIdx}
                    onClick={() => handleNavigation(item)}
                    disabled={isDisabled}
                    className={`w-full flex items-center gap-4 p-4 transition-colors ${
                      itemIdx !== section.items.length - 1 ? 'border-b border-gray-100' : ''
                    } ${
                      isDisabled 
                        ? 'cursor-not-allowed opacity-50' 
                        : 'hover:bg-gray-50 active:bg-gray-100'
                    }`}
                  >
                    <div className={`w-10 h-10 rounded-full flex items-center justify-center bg-${item.color}-100 text-${item.color}-600`}>
                      <Icon size={20} />
                    </div>
                    <div className="flex-1 text-left">
                      <p className="font-semibold text-gray-800">{item.label}</p>
                      {isDisabled && (
                        <p className="text-xs text-gray-400">업데이트 예정</p>
                      )}
                    </div>
                    <ChevronRight size={20} className="text-gray-400" />
                  </button>
                );
              })}
            </div>
          </div>
        ))}
      </div>

      {/* App Info */}
      <div className="px-6 mt-8 mb-6">
        <div className="bg-white rounded-2xl p-5 shadow-sm border border-gray-100 text-center">
          <p className="text-sm font-bold text-gray-800 mb-1">Jangbogo Smart Cart</p>
          <p className="text-xs text-gray-500">Version 1.0.0</p>
          <p className="text-xs text-gray-400 mt-2">© 2025 Jangbogo. All rights reserved.</p>
        </div>
      </div>
    </div>
  );
}