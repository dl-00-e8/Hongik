import React, { useState, useEffect, useRef } from 'react';
import { useNavigate } from 'react-router-dom';
import { Mic, Plus, Navigation } from 'lucide-react';
import { PRODUCTS } from '../data/mockData';

export default function ChatPage() {
  const navigate = useNavigate();
  const [messages, setMessages] = useState([
    { id: 1, sender: 'bot', text: '안녕하세요! 스마트 카트 AI입니다. 무엇을 도와드릴까요? (예: "우유 어디 있어?", "저녁 메뉴 추천해줘")' }
  ]);
  const [inputText, setInputText] = useState('');
  const chatEndRef = useRef(null);

  useEffect(() => {
    chatEndRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [messages]);

  const handleNavigate = (product) => {
    navigate('/map', { state: { targetProduct: product } });
  };

  const handleSend = (text = inputText) => {
    if (!text.trim()) return;

    // User Message
    const userMsg = { id: Date.now(), sender: 'user', text };
    setMessages(prev => [...prev, userMsg]);
    setInputText('');

    // Mock AI Response
    setTimeout(() => {
      let botText = "죄송합니다. 잘 이해하지 못했습니다.";
      let recommendedProduct = null;

      if (text.includes('우유')) {
        recommendedProduct = PRODUCTS.find(p => p.name.includes('우유'));
        botText = "유기농 우유가 유제품 코너(C3)에 있습니다. 안내해 드릴까요?";
      } else if (text.includes('사과')) {
        recommendedProduct = PRODUCTS.find(p => p.name.includes('사과'));
        botText = "제철 사과가 신선식품 코너(A1)에 있습니다. 당도가 아주 높아요!";
      } else if (text.includes('추천')) {
        botText = "오늘 저녁엔 스테이크 어떠세요? 1++ 한우 등심이 5% 할인 중입니다.";
        recommendedProduct = PRODUCTS.find(p => p.name.includes('한우'));
      }

      const botMsg = { 
        id: Date.now() + 1, 
        sender: 'bot', 
        text: botText, 
        product: recommendedProduct 
      };
      setMessages(prev => [...prev, botMsg]);
    }, 1000);
  };

  return (
    <div className="flex flex-col h-full bg-gray-50">
      {/* Chat Header */}
      <div className="bg-white p-4 shadow-sm border-b flex items-center justify-between z-10">
        <div className="flex items-center gap-3">
          <div className="w-10 h-10 rounded-full bg-blue-100 flex items-center justify-center text-blue-600">
            <div className="w-2 h-2 bg-blue-600 rounded-full animate-bounce mx-[1px]"></div>
            <div className="w-2 h-2 bg-blue-600 rounded-full animate-bounce mx-[1px] delay-75"></div>
          </div>
          <div>
            <h2 className="font-bold text-gray-800">AI 쇼핑 어시스턴트</h2>
            <p className="text-xs text-green-600 flex items-center gap-1">
              <span className="w-2 h-2 bg-green-500 rounded-full"></span> 온라인
            </p>
          </div>
        </div>
      </div>

      {/* Messages Area */}
      <div className="flex-1 overflow-y-auto p-4 space-y-4">
        {messages.map((msg) => (
          <div key={msg.id} className={`flex ${msg.sender === 'user' ? 'justify-end' : 'justify-start'}`}>
            <div className={`max-w-[80%] rounded-2xl p-4 shadow-sm ${msg.sender === 'user' ? 'bg-blue-600 text-white rounded-br-none' : 'bg-white text-gray-800 rounded-tl-none border border-gray-100'}`}>
              <p className="text-sm leading-relaxed">{msg.text}</p>
              
              {/* Action Button in Chat */}
              {msg.product && (
                <div className="mt-3 pt-3 border-t border-gray-100/20 flex gap-2">
                  <button 
                    onClick={() => handleNavigate(msg.product)}
                    className={`flex-1 py-2 rounded-lg text-xs font-bold flex items-center justify-center gap-2 ${msg.sender === 'user' ? 'bg-white/20 hover:bg-white/30' : 'bg-blue-50 text-blue-600 hover:bg-blue-100'}`}
                  >
                    <Navigation size={14} /> 안내 시작
                  </button>
                </div>
              )}
            </div>
          </div>
        ))}
        <div ref={chatEndRef} />
      </div>

      {/* Input Area */}
      <div className="bg-white p-4 border-t safe-area-bottom">
        <div className="flex gap-2">
          <button className="p-3 rounded-full bg-gray-100 text-gray-500 hover:bg-gray-200 transition-colors">
            <Plus size={20} />
          </button>
          <div className="flex-1 relative">
            <input 
              type="text" 
              value={inputText}
              onChange={(e) => setInputText(e.target.value)}
              onKeyPress={(e) => e.key === 'Enter' && handleSend()}
              placeholder="상품 검색 또는 질문하기..."
              className="w-full h-full bg-gray-100 rounded-full pl-5 pr-12 text-sm focus:outline-none focus:ring-2 focus:ring-blue-500 transition-all"
            />
            <button 
              onClick={() => handleSend("오늘 저녁 메뉴 추천해줘")}
              className="absolute right-2 top-1/2 -translate-y-1/2 p-1.5 rounded-full bg-blue-600 text-white hover:bg-blue-700 transition-colors shadow-sm"
            >
              <Mic size={16} />
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}