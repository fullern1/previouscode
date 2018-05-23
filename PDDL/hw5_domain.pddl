;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; HW5 blocks world with painting
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (domain hw5_domain)
  (:requirements :strips)

  (:constants red green blue)

  ;; the first five predicates are for the classic block world.  The rest are
  ;;  addional predicates required to extend the model to allow for painting

  (:predicates (on ?x ?y)
	       (on-table ?x)
	       (clear ?x)
	       (arm-empty)
	       (holding ?x)
	       (block ?x)              ; ?x is a block
	       (paint-can ?x ?color)   ; ?x is a paint can with paint color ?color
	       (brush ?x)              ; ?x is a paint brush
	       (water-bucket ?wb)      ; ?x is a water bucket
	       (color ?x ?color)       ; ?x has color ?color
               (open ?can)             ; paint can ?can is open
	       (clean ?brush)          ; brush ?brush is clean
	       (loaded ?brush ?color)  ; brush ?brush is loaded with paint of color ?color
               (true))                 ; dummy effect of no consequence

  ;; the four classic actions for manipulating objects

  (:action pick-up
     :parameters (?ob1)
     :precondition (and (clear ?ob1) (on-table ?ob1) (arm-empty))
     :effect
     (and (not (on-table ?ob1))
	   (not (clear ?ob1))
	   (not (arm-empty))
	   (holding ?ob1)))

  (:action put-down
     :parameters (?ob)
     :precondition (holding ?ob)
     :effect
     (and (not (holding ?ob))
	   (clear ?ob)
	   (arm-empty)
	   (on-table ?ob)))

  (:action stack
     :parameters (?sob ?sunderob)
     :precondition (and (holding ?sob) (clear ?sunderob))
     :effect
     (and (not (holding ?sob))
	   (not (clear ?sunderob))
	   (clear ?sob)
	   (arm-empty)
	   (on ?sob ?sunderob)))

  (:action unstack
     :parameters (?sob ?sunderob)
     :precondition (and (on ?sob ?sunderob) (clear ?sob) (arm-empty))
     :effect
     (and (holding ?sob)
	   (clear ?sunderob)
	   (not (clear ?sob))
	   (not (arm-empty))
	   (not (on ?sob ?sunderob))))

  ;; complete the actions below that extend the blocks world model to include painting

  (:action paint
    :parameters (?obj ?color ?brush)
    :precondition (and (brush ?brush)(holding ?brush)(loaded ?brush ?color)
    (not(clean ?brush))
    (clear ?obj)(on-table ?obj) 		
    (not(arm-empty)))   		      			
    :effect (and (color ?obj ?color))
    )

  (:action wash-brush
    :parameters (?brush ?wb ?color)
    :precondition (and (holding ?brush)(not(clean ?brush))(clear ?wb)
    (not(arm-empty))(water-bucket ?wb)(brush ?brush)(loaded ?brush ?color)
    (on-table ?wb))  
    :effect (and (clean ?brush)
    	    (not(loaded ?brush ?color)))  
    )

  (:action load-brush
    :parameters (?brush ?can ?color)
    :precondition (and (brush ?brush)(holding ?brush)(clean ?brush)
    (paint-can ?can ?color)(open ?can)(clear ?can)(not(arm-empty))
    (on-table ?can))  
    :effect (and (loaded ?brush ?color)
    	    	 (not(clean ?brush)))  
    )

   (:action remove-can-lid 
    :parameters (?can ?color)
    :precondition (and (paint-can ?can ?color)(clear ?can)(not(open ?can))
    (arm-empty)(on-table ?can))  
    :effect (and (open ?can)
    	    (clear ?can))   
    )

   (:action replace-can-lid
    :parameters (?can ?color)
    :precondition (and (paint-can ?can ?color)(clear ?can)(open ?can)
    (arm-empty)(on-table ?can))  
    :effect (and (not(open ?can))
    	    (clear ?can))  
    )

)
