;; brushes can be painted also!

(define (problem p7)
  (:domain hw5_domain)
  (:objects c1 c2 b1 b2)
  (:init (arm-empty)
         (paint-can c1 red) (on-table c1) (clear c1) (not (open c1))
         (paint-can c2 green) (on-table c2) (clear c2)  (not (open c2))
	 (brush b1)(clean b1)(on-table b1)(clear b1)
	 (brush b2)(clean b2)(on-table b2)(clear b2))
  (:goal (and (arm-empty)
              (color b1 red)
	      (color b2 green))))





