;; An impossible task -- no way to clean brush1

(define (problem p9)
  (:domain hw5_domain)
  (:objects a b can1 can2 brush1 wb1) 
  (:init (arm-empty)
	 (block a) (on-table a) (clear a)
	 (block b) (on-table b) (clear b)
         (brush brush1)(clean brush1)(on-table brush1)(clear brush1)
         (paint-can can1 red) (on-table can1) (not (open can1) )
         (paint-can can2 blue) (on-table can2) (not (open can2) ))
  (:goal (and (color a red) (color b blue))))

