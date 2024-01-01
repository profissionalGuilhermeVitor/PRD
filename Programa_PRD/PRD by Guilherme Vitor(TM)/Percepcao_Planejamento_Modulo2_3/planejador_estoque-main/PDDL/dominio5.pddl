(define (domain New_Project_1)
    (:requirements :strips)
    (:types
      lugar - object
      produto1 - object
    )
    (:predicates
      (estaEm1 ?pro - produto1 ?lug - lugar)
      (plivre1 ?prod - produto1)
      (atras ?lug - lugar ?lug - lugar)
      (esquerda ?lug - lugar ?lug - lugar)
      (acima ?lug - lugar ?lug - lugar)
      (livre ?lug - lugar)
      (piso ?lug - lugar)
    )
    (:action moverPiso1
     :parameters (?prod - produto1 ?l1 - lugar)
     :precondition
       (and
         (plivre1 ?prod)
         (livre ?l1)
         (piso ?l1)
       )
     :effect
       (and
         (estaEm1 ?prod ?l1)
         (not (plivre1 ?prod))
         (not (livre ?l1))
       )
    )
    (:action empilhar1
     :parameters (?prod - produto1 ?l1 - lugar ?l2 - lugar)
     :precondition
       (and
         (plivre1 ?prod)
         (not (livre ?l1))
         (acima ?l2 ?l1)
       )
     :effect
       (and
         (estaEm1 ?prod ?l2)
         (not (plivre1 ?prod))
         (not (livre ?l2))
       )
    )
)