(setq tc1 (list 11 33 23 45 13 25 8 135))
(setq tc2 (list 83 72 65 54 47 33 29 11))

(defun insertionsort (lst)
  (do ((i 1 (1+ i)))
      ((>= i (length lst)))
    (let ((key (nth i lst)) (j (- i 1)))
      (do ((temp j (decf j)))
          ((or (< j 0) (<= (nth j lst) key)))
        (setf (nth (1+ j) lst) (nth j lst))
      )
      (setf (nth (1+ j) lst) key)
    )
    (print lst)
  )
)

(format t "B911139~%")

(print "TC1")
(print tc1)
(insertionsort tc1)

(format t "~%")

(print "TC2")
(print tc2)
(insertionsort tc2)