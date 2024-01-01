(define (domain New_Project_1)
    (:requirements :strips)
    (:types
      lugar - object
      produto1 - object
      produto2 - object
      produto3 - object
      produto4 - object
    )
    (:predicates
      (estaEm1 ?pro - produto1 ?lug - lugar)
      (plivre1 ?prod - produto1)
      (estaEm2 ?pro - produto2 ?lug - lugar)
      (plivre2 ?prod - produto2)
      (estaEm3 ?pro - produto3 ?lug - lugar)
      (plivre3 ?prod - produto3)
      (estaEm4 ?pro - produto4 ?lug - lugar)
      (plivre4 ?prod - produto4)
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
    (:action moverPiso2
     :parameters (?prod - produto2 ?l1 - lugar ?l2 - lugar)
     :precondition
       (and
         (plivre2 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (atras ?l2 ?l1)
       )
     :effect
       (and
         (estaEm2 ?prod ?l1)
         (not (plivre2 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
       )
    )
    (:action moverPiso3
     :parameters (?prod - produto3 ?l1 - lugar ?l2 - lugar)
     :precondition
       (and
         (plivre3 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (esquerda ?l2 ?l1)
       )
     :effect
       (and
         (estaEm3 ?prod ?l1)
         (not (plivre3 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
       )
    )
    (:action moverPiso4
     :parameters (?prod - produto4 ?l1 - lugar ?l2 - lugar)
     :precondition
       (and
         (plivre4 ?prod)
         (livre ?l1)
         (piso ?l1)
         (acima ?l2 ?l1)
       )
     :effect
       (and
         (estaEm4 ?prod ?l1)
         (not (plivre4 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
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
    (:action empilhar2
     :parameters (?prod - produto2 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre2 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (atras ?l4 ?l3)
         (acima ?l3 ?l1)
         (acima ?l4 ?l2)
       )
     :effect
       (and
         (estaEm2 ?prod ?l3)
         (not (plivre2 ?prod))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
    (:action empilhar3
     :parameters (?prod - produto3 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre3 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (esquerda ?l4 ?l3)
         (acima ?l3 ?l1)
         (acima ?l4 ?l2)
       )
     :effect
       (and
         (estaEm3 ?prod ?l3)
         (not (plivre3 ?prod))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
    (:action empilhar4
     :parameters (?prod - produto4 ?l1 - lugar ?l2 - lugar ?l3 - lugar)
     :precondition
       (and
         (plivre4 ?prod)
         (not (livre ?l1))
         (acima ?l3 ?l2)
         (acima ?l2 ?l1)
       )
     :effect
       (and
         (estaEm4 ?prod ?l2)
         (not (plivre4 ?prod))
         (not (livre ?l2))
         (not (livre ?l3))
       )
    )
)