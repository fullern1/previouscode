;; Block A is on the table, B is on A and C on B.  On the table are a water
;; bucket, cans of red, green and blue paint stacked on each other and a clean
;; brush.  The goal is to make A red, B green and C blue and to have A on B, B
;; on C and C on the table, the cans closed and the brush clean and arm empty.


(define (problem p4)
  (:domain hw5_domain)
  (:objects A B C can1 can2 can3 brush1 wb1)
  (:init (arm-empty)
      (block a) (on-table a)
      (block b) (on b a) 
      (block c) (on c b) (clear c) 
      (water-bucket wb1) (on-table wb1)(clear wb1)
      (paint-can can1 red) (on-table can1) (not (open can1))
      (paint-can can2 green) (on can2 can1) (not (open can2))
      (paint-can can3 blue) (on can3 can2) (clear can3) (not (open can3))
      (brush brush1)(clean brush1)(on-table brush1)(clear brush1))
  (:goal (and (arm-empty)
           (on a b)
           (on b c)
           (on-table c)
           (clear a)
           (color a red)
           (color b green)
           (color c blue)
           (not (open can1))
           (not (open can2))
           (not (open can3))
           (clean brush1))))



