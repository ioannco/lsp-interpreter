(defun pg (a) (cond ((= a 0) T) (T (pg (- a 1)))))
(defun start (L) (cond((null L) NIL)((null (cdr L)) NIL)(T (cons (car L) (start (cdr L))))))(defun start (L))
(defun gk (a) (null a))
