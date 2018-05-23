;; Block A is on the table, B is on A and C on B.  Cans of red, green
;; and blue paint are on the table along with three clean brushes.
;; There is no water bucket.  The goal is to make A red, B green and C
;; red and to have A on B, B on C and C on the table and the arm empty.

(define (problem p6)
  (:domain hw5_domain)
  (:objects a b c c1 c2 c3 b1 b2 b3)
  (:init (arm-empty)
         (block a) (on-table a)
	 (block b)(on b a)
	 (block c)(on c b)(clear c)
         (paint-can c1 red) (on-table c1) (clear c1) (not (open c1))
         (paint-can c2 green) (on-table c2) (clear c2)  (not (open c2))
         (paint-can c3 blue) (on-table c3) (clear c3)  (not (open c3))
         (on c1 c2) (on c2 c3) (on-table c3) (clear c1)
	 (brush b1)(clean b1)(on b1 b2)(clear b1)
	 (brush b2)(clean b2)(on b2 b3)
	 (brush b3)(clean b3)(on-table b3))
  (:goal (and (arm-empty)
              (color a red)
	      (color b green)
	      (color c red)
              (on a b)
	      (on b c)
	      (on-table c))))




