(define (domain New_Project_1)
    (:requirements :strips)
    (:types
      lugar - object
      produto1 - object
      produto2 - object
      produto3 - object
      produto4 - object
      produto5 - object
      produto6 - object
      produto7 - object
      produto8 - object
      produto9 - object
      produto10 - object
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
      (estaEm5 ?pro - produto5 ?lug - lugar)
      (plivre5 ?prod - produto5)
      (estaEm6 ?pro - produto6 ?lug - lugar)
      (plivre6 ?prod - produto6)
      (estaEm7 ?pro - produto7 ?lug - lugar)
      (plivre7 ?prod - produto7)
      (estaEm8 ?pro - produto8 ?lug - lugar)
      (plivre8 ?prod - produto8)
      (estaEm9 ?pro - produto9 ?lug - lugar)
      (plivre9 ?prod - produto9)
      (estaEm10 ?pro - produto10 ?lug - lugar)
      (plivre10 ?prod - produto10)
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
    (:action moverPiso5
     :parameters (?prod - produto5 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre5 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (livre ?l3)
         (piso ?l3)
         (livre ?l4)
         (piso ?l4)
         (atras ?l2 ?l1)
         (atras ?l4 ?l3)
         (esquerda ?l3 ?l1)
       )
     :effect
       (and
         (estaEm5 ?prod ?l1)
         (not (plivre5 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
    (:action moverPiso6
     :parameters (?prod - produto6 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre6 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (esquerda ?l2 ?l1)
         (esquerda ?l4 ?l3)
         (acima ?l3 ?l1)
       )
     :effect
       (and
         (estaEm6 ?prod ?l1)
         (not (plivre6 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
    (:action moverPiso7
     :parameters (?prod - produto7 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre7 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (atras ?l2 ?l1)
         (atras ?l4 ?l3)
         (acima ?l3 ?l1)
       )
     :effect
       (and
         (estaEm7 ?prod ?l1)
         (not (plivre7 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
    (:action moverPiso8
     :parameters (?prod - produto8 ?l1 - lugar ?l2 - lugar ?l3 - lugar)
     :precondition
       (and
         (plivre8 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (livre ?l3)
         (piso ?l3)
         (atras ?l2 ?l1)
         (atras ?l3 ?l2)
       )
     :effect
       (and
         (estaEm8 ?prod ?l1)
         (not (plivre8 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
       )
    )
    (:action moverPiso9
     :parameters (?prod - produto9 ?l1 - lugar ?l2 - lugar ?l3 - lugar)
     :precondition
       (and
         (plivre9 ?prod)
         (livre ?l1)
         (piso ?l1)
         (livre ?l2)
         (piso ?l2)
         (livre ?l3)
         (piso ?l3)
         (esquerda ?l2 ?l1)
         (esquerda ?l3 ?l2)
       )
     :effect
       (and
         (estaEm9 ?prod ?l1)
         (not (plivre9 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
       )
    )
    (:action moverPiso10
     :parameters (?prod - produto10 ?l1 - lugar ?l2 - lugar ?l3 - lugar)
     :precondition
       (and
         (plivre10 ?prod)
         (livre ?l1)
         (piso ?l1)
         (acima ?l2 ?l1)
         (acima ?l3 ?l2)
       )
     :effect
       (and
         (estaEm10 ?prod ?l1)
         (not (plivre10 ?prod))
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
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
    (:action empilhar5
     :parameters (?prod - produto5 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar ?l5 - lugar ?l6 - lugar ?l7 - lugar ?l8 - lugar)
     :precondition
       (and
         (plivre5 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (not (livre ?l4))
         (atras ?l6 ?l5)
         (atras ?l8 ?l7)
         (esquerda ?l7 ?l5)
         (acima ?l5 ?l1)
         (acima ?l6 ?l2)
         (acima ?l7 ?l3)
         (acima ?l8 ?l4)
       )
     :effect
       (and
         (estaEm5 ?prod ?l5)
         (not (plivre5 ?prod))
         (not (livre ?l5))
         (not (livre ?l6))
         (not (livre ?l7))
         (not (livre ?l8))
       )
    )
    (:action empilhar6
     :parameters (?prod - produto6 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar ?l5 - lugar ?l6 - lugar)
     :precondition
       (and
         (plivre6 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (esquerda ?l4 ?l3)
         (esquerda ?l6 ?l5)
         (acima ?l5 ?l3)
         (acima ?l3 ?l1)
         (acima ?l4 ?l2)
       )
     :effect
       (and
         (estaEm6 ?prod ?l3)
         (not (plivre6 ?prod))
         (not (livre ?l3))
         (not (livre ?l4))
         (not (livre ?l5))
         (not (livre ?l6))
       )
    )
    (:action empilhar7
     :parameters (?prod - produto7 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar ?l5 - lugar ?l6 - lugar)
     :precondition
       (and
         (plivre7 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (atras ?l4 ?l3)
         (atras ?l6 ?l5)
         (acima ?l5 ?l3)
         (acima ?l3 ?l1)
         (acima ?l4 ?l2)
       )
     :effect
       (and
         (estaEm7 ?prod ?l3)
         (not (plivre7 ?prod))
         (not (livre ?l3))
         (not (livre ?l4))
         (not (livre ?l5))
         (not (livre ?l6))
       )
    )
    (:action empilhar8
     :parameters (?prod - produto8 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar ?l5 - lugar ?l6 - lugar)
     :precondition
       (and
         (plivre8 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (atras ?l5 ?l4)
         (atras ?l6 ?l5)
         (acima ?l4 ?l1)
         (acima ?l5 ?l2)
         (acima ?l6 ?l3)
       )
     :effect
       (and
         (estaEm8 ?prod ?l4)
         (not (plivre8 ?prod))
         (not (livre ?l4))
         (not (livre ?l5))
         (not (livre ?l6))
       )
    )
    (:action empilhar9
     :parameters (?prod - produto9 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar ?l5 - lugar ?l6 - lugar)
     :precondition
       (and
         (plivre9 ?prod)
         (not (livre ?l1))
         (not (livre ?l2))
         (not (livre ?l3))
         (esquerda ?l5 ?l4)
         (esquerda ?l6 ?l5)
         (acima ?l4 ?l1)
         (acima ?l5 ?l2)
         (acima ?l6 ?l3)
       )
     :effect
       (and
         (estaEm9 ?prod ?l4)
         (not (plivre9 ?prod))
         (not (livre ?l4))
         (not (livre ?l5))
         (not (livre ?l6))
       )
    )
    (:action empilhar10
     :parameters (?prod - produto10 ?l1 - lugar ?l2 - lugar ?l3 - lugar ?l4 - lugar)
     :precondition
       (and
         (plivre10 ?prod)
         (not (livre ?l1))
         (acima ?l3 ?l2)
         (acima ?l4 ?l3)
         (acima ?l2 ?l1)
       )
     :effect
       (and
         (estaEm10 ?prod ?l2)
         (not (plivre10 ?prod))
         (not (livre ?l2))
         (not (livre ?l3))
         (not (livre ?l4))
       )
    )
)