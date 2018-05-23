;;; There is a stack of four blocks on the table: a/b/c/d. Reverse it.

(define (problem test2)
  (:domain hw5_domain)
  (:objects a b c d)
  (:init (arm-empty)
	 (on a b)
	 (on b c)
	 (on c d)
	 (on-table d)
	 (clear a))
  (:goal (and
	  (on d c)
	  (on c b)
	  (on b a)
	  (on-table a)
	  (clear d))))
