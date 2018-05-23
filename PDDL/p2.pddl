;; Block A is on the table, block B on A and there is nothing on B.  A
;; water bucket, a brush, a can of red paint and a can of blue paint
;; are on the table and clear.  The goal is to for A to be colored red
;; and B blue and the brush be clean.

(define (problem p2)
  (:domain hw5_domain)
  (:objects a b wb1 can1 can2 brush1 bucket1)
  (:init (arm-empty)
         (block a) (on-table a)
         (block b) (on b a) (clear b) 
	 (water-bucket wb1) (on-table wb1) (clear wb1)
         (paint-can can1 red)  (on-table can1) (clear can1) (not (open can1))
         (paint-can can2 blue) (on-table can2) (clear can2) (not (open can2))
	 (brush brush1) (on-table brush1) (clear brush1) (clean brush1))
  (:goal (and (arm-empty)(on b a)(color a red)(color b blue)(clean brush1))))



