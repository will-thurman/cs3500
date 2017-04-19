(defun mylast (x)
  (if (atom (cdr x))
    (car x)
    (mylast(cdr x))
  )
)

(defun mycount (x l)
  (if (atom (cdr l))
    (if (eq x (car l))
      1
      0
    )
    
    (if (eq x (car l))
      (+ 1 (mycount x (cdr l)))
      (+ 0 (mycount x (cdr l)))
    )
  )
)

(defun mymember (x l)
  (if (atom (cdr l))
    (if (eq x (car l))
      t
      nil
    )
    
    (if (eq x (car l))
      t
      (mymember x (cdr l))
    )
  )
)

(defun mypurge (l)
  (if (atom (cdr l))
    (cons (car l) nil)
    
    (if (mymember (car l) (cdr l))
      (mypurge (cdr l))
      
      (cons (car l) (mypurge (cdr l)))
    )
  )
)

(defun mycommon (l1 l2)
  (if (atom (cdr l1))
    (if (mymember (car l1) l2)
      (cons (car l1) nil)
      
      nil
    )
    
    (if (mymember (car l1) l2)
      (cons (car l1) (mycommon (cdr l1) l2))
      
      (mycommon (cdr l1) l2)
    )
  )
)

(defun mygen (x y z)
  (if (> x y)
    nil
    
    (cons x (mygen (+ x z) y z))
  )
)

(defun mymap (f l)
  (if (atom (cdr l))
    (cons (funcall f (car l)) nil)
    
    (cons (funcall f (car l)) (mymap f (cdr l)))
  )
)

(defun myreduce(f l)
  (if (atom (cdr l))
    (car l)
    
    (funcall f (car l) (myreduce f (cdr l)))
  )
)