;; init: c/b/a; wb1/can2/can1/brush1
;; goal: a/b/c; brish1/can1; a is red, b is green, c is red

;; Block A is on the table, B is on A and C on B. A green paint can is on the sprayer and a blue paint
;; can on the green paint can and a water bucket on the blue can.  A
;; clean brush is on the water bucket.  The goal is to make A red, B
;; green and C blue and to have A on B, B on C and C on the table. The
;; brush should be clean and on top of the paint can with green paint.


(define (problem p5)
  (:domain hw5_domain)
  (:objects A B C can1 can2 brush1 wb1)
  (:init (arm-empty)
         (block a) (on-table a)
         (block b) (on b a) 
	 (block c) (on c b) (clear c) 
	 (water-bucket wb1) (on wb1 can2) (clear wb1)
         (paint-can can1 red) (not (open can1)) (on can1 brush1) 
         (paint-can can2 green)  (not (open can2)) (on can2 can1)
	 (brush brush1)(clean brush1)(on-table brush1))
  (:goal (and (arm-empty)
    	   (on a b)
	   (on b c)
	   (on-table c)
	   (color a red)
	   (color b green)
	   (color c red)
	   (clean brush1)
	   (on brush1 can1)
           (not (open can1))
           (not (open can2)))))
