;; three blocks (A B and C) are on the table along with three closed
;; paint cans (red, green, blue), a water bucket and a clean brush.
;; Paint A, B and C red, blue and green, respectively. End with the
;; arm empty and the brush clean and all of the paint cans closed.

(define (problem p3)
  (:domain hw5_domain)
  (:objects A B C can1 can2 can3 brush1 wb1)
  (:init (arm-empty)
         (block a) (on-table a) (clear a)
         (block b) (on-table b) (clear b)
         (block c) (on-table c) (clear c)
	 (water-bucket wb1) (on-table wb1)(clear wb1)
         (paint-can can1 red) (on-table can1) (not (open can1)) (clear can1)
         (paint-can can2 green) (on-table can2)(not (open can2)) (clear can2)
         (paint-can can3 blue) (on-table can3) (not (open can3)) (clear can3)
	 (brush brush1)(clean brush1)(on-table brush1)(clear brush1))
  (:goal (and (arm-empty)
          (color a red)
          (color b blue)
          (color c green)
          (clean brush1)
          (not (open can1))
          (not (open can2))
          (not (open can3)))))



