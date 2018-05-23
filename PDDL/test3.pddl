;; In this impossible problem there are two blocks on the table, A and
;; B.  The goal is to have A on B and B on A.

(define (problem test_impossible)
  (:domain hw5_domain)
  (:objects A B)
  (:init (arm-empty)
	 (on-table A)
         (clear A)
	 (on-table B)
         (clear B))
  (:goal (and (on A B) (on B A))))



