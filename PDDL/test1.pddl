;;; There is a stack of three blocks with C on B, B on A and A on the
;;; table.  Reverse the stack.

(define (problem test1)
  (:domain hw5_domain)
  (:objects A B C)
  (:init (arm-empty)
         (block A)
	 (on-table A)
         (block B)
	 (on B A) 
         (block C)
	 (on C B)
	 (clear C))
  (:goal (and (on A B) (on B C))))



