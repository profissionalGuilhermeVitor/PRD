(define (domain blocks-domain)

(:requirements :strips :typing :fluents :disjunctive-preconditions :equality :negative-preconditions )

(:types 
        block - object
        gar - object
)

(:predicates 
	(inhand ?block - block) 
	(emptyhand) 
	(on ?block ?on_block - block) 
	(clear ?block - block)
	(table ?block - block)
)
(:action pickBlock
    :parameters 
    (
        ?b - block
        ?t - block
    )
    :precondition
    (and 
        (not (inhand ?b))
        (not (inhand ?t))
        (not(table ?b))
        (on ?b ?t)
        (emptyhand)
        (clear ?b)
        (not(= ?b ?t))
    )
    :effect 
    (and
        (inhand ?b)
        (not(emptyhand))
        (clear ?t)
        (not(on ?b ?t))
    )
)
(:action stack
    :parameters 
    (
        ?b - block 
        ?t - block
    )
    :precondition 
        (and
            (inhand ?b)
            (not(emptyhand))
            (or
                (and
                    (table ?t)
                    (clear ?t)
                )
                (clear ?t)
                )
            (not(= ?b ?t))
        )
    :effect 
        (and
            (on ?b ?t)
            (not(clear ?t))
            (clear ?b)
            (not(inhand ?b))
            (emptyhand)
        )
     )
)