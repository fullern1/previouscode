;; impossible - a brush can't paint itself

(define (problem p10)
  (:domain hw5_domain)
  (:objects c1 c2 b1)
  (:init (arm-empty)
         (paint-can c1 red) (on-table c1) (clear c1) (not (open c1))
	 (brush b1)(clean b1)(on-table b1)(clear b1))
  (:goal (and (arm-empty)
              (color b1 red))))






