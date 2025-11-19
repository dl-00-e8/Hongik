import React from 'react';
import { useNavigate } from 'react-router-dom';
import { Home, ArrowLeft } from 'lucide-react';

export default function NotFound() {
  const navigate = useNavigate();

  return (
    <div className="h-full flex flex-col items-center justify-center bg-gray-50 p-6">
      <div className="text-center">
        {/* 404 Icon */}
        <div className="mb-6">
          <div className="text-9xl font-bold text-gray-200">404</div>
        </div>

        {/* Error Message */}
        <h1 className="text-2xl font-bold text-gray-800 mb-2">페이지를 찾을 수 없습니다</h1>
        <p className="text-gray-500 mb-8">
          요청하신 페이지가 존재하지 않거나<br />
          이동되었을 수 있습니다.
        </p>

        {/* Action Buttons */}
        <div className="flex flex-col sm:flex-row gap-3 justify-center">
          <button
            onClick={() => navigate(-1)}
            className="flex items-center justify-center gap-2 px-6 py-3 bg-gray-100 text-gray-700 rounded-xl font-bold hover:bg-gray-200 transition-colors"
          >
            <ArrowLeft size={20} />
            이전 페이지
          </button>
          <button
            onClick={() => navigate('/')}
            className="flex items-center justify-center gap-2 px-6 py-3 bg-blue-600 text-white rounded-xl font-bold hover:bg-blue-700 transition-colors"
          >
            <Home size={20} />
            홈으로 가기
          </button>
        </div>
      </div>

      {/* Decorative Elements */}
      <div className="mt-12 text-gray-300">
        <svg
          className="w-64 h-64 opacity-50"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
        >
          <path
            strokeLinecap="round"
            strokeLinejoin="round"
            strokeWidth={0.5}
            d="M9.172 16.172a4 4 0 015.656 0M9 10h.01M15 10h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
          />
        </svg>
      </div>
    </div>
  );
}