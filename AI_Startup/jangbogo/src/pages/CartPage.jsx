import React from 'react';
import { ShoppingCart, X, Plus, Minus, Scan } from 'lucide-react';
import { useCart } from '../contexts/CartContext';

export default function CartPage() {
  const { cart, cartTotal, updateQty, removeFromCart } = useCart();

  return (
    <div className="h-full flex flex-col bg-gray-50">
      <div className="p-5 bg-white border-b shadow-sm">
        <h2 className="font-bold text-xl">
          장바구니 <span className="text-blue-600 text-lg font-medium ml-1">({cart.length})</span>
        </h2>
      </div>

      <div className="flex-1 overflow-y-auto p-4 space-y-3">
        {cart.length === 0 ? (
          <div className="h-full flex flex-col items-center justify-center text-gray-400 gap-4">
            <ShoppingCart size={64} strokeWidth={1} />
            <p>장바구니가 비어있습니다.</p>
            <button className="text-blue-500 text-sm font-bold">상품 둘러보기</button>
          </div>
        ) : (
          cart.map(item => (
            <div key={item.id} className="bg-white rounded-xl p-4 shadow-sm border border-gray-100 flex items-center gap-4">
              <div className="w-16 h-16 bg-gray-100 rounded-lg flex items-center justify-center text-2xl">
                📦
              </div>
              <div className="flex-1">
                <div className="flex justify-between items-start mb-1">
                  <h3 className="font-bold text-gray-800">{item.name}</h3>
                  <button onClick={() => removeFromCart(item.id)} className="text-gray-400 hover:text-red-500">
                    <X size={18} />
                  </button>
                </div>
                <p className="text-sm text-gray-500 mb-3">{item.price.toLocaleString()}원</p>
                <div className="flex items-center gap-3">
                  <button onClick={() => updateQty(item.id, -1)} className="p-1 rounded-full bg-gray-100 hover:bg-gray-200">
                    <Minus size={14} />
                  </button>
                  <span className="font-bold text-sm w-6 text-center">{item.qty}</span>
                  <button onClick={() => updateQty(item.id, 1)} className="p-1 rounded-full bg-gray-100 hover:bg-gray-200">
                    <Plus size={14} />
                  </button>
                </div>
              </div>
            </div>
          ))
        )}
      </div>

      <div className="bg-white p-6 rounded-t-3xl shadow-[0_-5px_20px_rgba(0,0,0,0.05)] z-10">
        <div className="flex justify-between items-center mb-6">
          <span className="text-gray-500 font-medium">총 예상 결제금액</span>
          <span className="text-2xl font-bold text-blue-600">{cartTotal.toLocaleString()}원</span>
        </div>
        <button className="w-full bg-blue-600 text-white py-4 rounded-xl font-bold text-lg hover:bg-blue-700 transition-colors shadow-lg shadow-blue-200 flex items-center justify-center gap-2">
          <Scan size={20} /> 간편 결제하기
        </button>
      </div>
    </div>
  );
}