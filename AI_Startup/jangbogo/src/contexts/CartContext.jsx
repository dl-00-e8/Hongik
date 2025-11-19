import React, { createContext, useContext, useState, useEffect } from 'react';

const CartContext = createContext();

export function CartProvider({ children }) {
  const [cart, setCart] = useState([]);
  const [cartTotal, setCartTotal] = useState(0);

  const addToCart = (product) => {
    const existing = cart.find(p => p.id === product.id);
    if (existing) {
      setCart(cart.map(p => p.id === product.id ? { ...p, qty: p.qty + 1 } : p));
    } else {
      setCart([...cart, { ...product, qty: 1 }]);
    }
  };

  const removeFromCart = (productId) => {
    setCart(cart.filter(p => p.id !== productId));
  };

  const updateQty = (productId, delta) => {
    setCart(cart.map(p => {
      if (p.id === productId) {
        const newQty = Math.max(1, p.qty + delta);
        return { ...p, qty: newQty };
      }
      return p;
    }));
  };

  useEffect(() => {
    const total = cart.reduce((acc, curr) => acc + (curr.price * curr.qty), 0);
    setCartTotal(total);
  }, [cart]);

  return (
    <CartContext.Provider value={{ cart, cartTotal, addToCart, removeFromCart, updateQty }}>
      {children}
    </CartContext.Provider>
  );
}

export function useCart() {
  const context = useContext(CartContext);
  if (!context) {
    throw new Error('useCart must be used within CartProvider');
  }
  return context;
}