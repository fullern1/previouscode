;; There is only one block, A, which is on the table.  A closed paint
;; can with red paint is on the table.  There is a clean brush on the
;; table.  Our goal is to have A be red and the arm empty.  (removed
;; requirement that the brush be clean 11/12).

(define (problem p1)
  (:domain hw5_domain)
  (:objects A CAN1 BRUSH1)
  (:init (arm-empty)
         (block A) (on-table A) (clear A) 
         (paint-can CAN1 red) (on-table CAN1) (clear CAN1) (not (open CAN1))
	 (brush BRUSH1)(clean BRUSH1)(on-table BRUSH1)(clear BRUSH1))
  (:goal (and (arm-empty)(color A red))))



