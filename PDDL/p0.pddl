;; There is only one block, A, which is on the table.  There is a
;; brush B on the table that is loaded with red paint.  Our goal is to
;; have A be red and the arm empty.

(define (problem p0)
  (:domain hw5_domain)
  (:objects a brush1)
  (:init (arm-empty)
         (block a) (on-table a) (clear a)
         (brush brush1) (on-table brush1) (clear brush1) (loaded brush1 red))
  (:goal (and (color a red) (arm-empty))))

