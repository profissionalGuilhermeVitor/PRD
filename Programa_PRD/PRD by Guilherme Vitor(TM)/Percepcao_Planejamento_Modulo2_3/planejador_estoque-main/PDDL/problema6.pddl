(define (problem Planning_Problem)
    (:domain New_Project_1)
    (:objects
      lx1y1z1 - lugar
      lx2y1z1 - lugar
      lx3y1z1 - lugar
      lx4y1z1 - lugar
      lx1y2z1 - lugar
      lx2y2z1 - lugar
      lx3y2z1 - lugar
      lx4y2z1 - lugar
      lx1y3z1 - lugar
      lx2y3z1 - lugar
      lx3y3z1 - lugar
      lx4y3z1 - lugar
      lx1y4z1 - lugar
      lx2y4z1 - lugar
      lx3y4z1 - lugar
      lx4y4z1 - lugar
      lx1y1z2 - lugar
      lx2y1z2 - lugar
      lx3y1z2 - lugar
      lx4y1z2 - lugar
      lx1y2z2 - lugar
      lx2y2z2 - lugar
      lx3y2z2 - lugar
      lx4y2z2 - lugar
      lx1y3z2 - lugar
      lx2y3z2 - lugar
      lx3y3z2 - lugar
      lx4y3z2 - lugar
      lx1y4z2 - lugar
      lx2y4z2 - lugar
      lx3y4z2 - lugar
      lx4y4z2 - lugar
      lx1y1z3 - lugar
      lx2y1z3 - lugar
      lx3y1z3 - lugar
      lx4y1z3 - lugar
      lx1y2z3 - lugar
      lx2y2z3 - lugar
      lx3y2z3 - lugar
      lx4y2z3 - lugar
      lx1y3z3 - lugar
      lx2y3z3 - lugar
      lx3y3z3 - lugar
      lx4y3z3 - lugar
      lx1y4z3 - lugar
      lx2y4z3 - lugar
      lx3y4z3 - lugar
      lx4y4z3 - lugar
      lx1y1z4 - lugar
      lx2y1z4 - lugar
      lx3y1z4 - lugar
      lx4y1z4 - lugar
      lx1y2z4 - lugar
      lx2y2z4 - lugar
      lx3y2z4 - lugar
      lx3y2z4 - lugar
      lx1y3z4 - lugar
      lx2y3z4 - lugar
      lx3y3z4 - lugar
      lx4y3z4 - lugar
      lx1y4z4 - lugar
      lx2y4z4 - lugar
      lx3y4z4 - lugar
      lx4y4z4 - lugar
      prod1 - produto2
      prod2 - produto2
      prod3 - produto2
      prod4 - produto2
      prod5 - produto3
      prod6 - produto3
      prod7 - produto3
      prod8 - produto3
      prod9 - produto3
      prod10 - produto3
      prod11 - produto3
      prod12 - produto3
      prod13 - produto3
      prod14 - produto3
      prod15 - produto3
      prod16 - produto3
      prod17 - produto4
      prod18 - produto4
      prod19 - produto4
      prod20 - produto4
      prod21 - produto4
      prod22 - produto4
      prod23 - produto4
      prod24 - produto4
      prod25 - produto4
      prod26 - produto4
      prod27 - produto4
      prod28 - produto4
      prod29 - produto4
      prod30 - produto4
      prod31 - produto4
      prod32 - produto4
    )
    (:init
      (livre lx1y1z1)
      (piso lx1y1z1)
      (livre lx2y1z1)
      (piso lx2y1z1)
      (livre lx3y1z1)
      (piso lx3y1z1)
      (livre lx4y1z1)
      (piso lx4y1z1)
      (livre lx1y2z1)
      (piso lx1y2z1)
      (livre lx2y2z1)
      (piso lx2y2z1)
      (livre lx3y2z1)
      (piso lx3y2z1)
      (livre lx4y2z1)
      (piso lx4y2z1)
      (livre lx1y3z1)
      (piso lx1y3z1)
      (livre lx2y3z1)
      (piso lx2y3z1)
      (livre lx3y3z1)
      (piso lx3y3z1)
      (livre lx4y3z1)
      (piso lx4y3z1)
      (livre lx1y4z1)
      (piso lx1y4z1)
      (livre lx2y4z1)
      (piso lx2y4z1)
      (livre lx3y4z1)
      (piso lx3y4z1)
      (livre lx4y4z1)
      (piso lx4y4z1)
      (livre lx1y1z2)
      (livre lx2y1z2)
      (livre lx3y1z2)
      (livre lx4y1z2)
      (livre lx1y2z2)
      (livre lx2y2z2)
      (livre lx3y2z2)
      (livre lx4y2z2)
      (livre lx1y3z2)
      (livre lx2y3z2)
      (livre lx3y3z2)
      (livre lx4y3z2)
      (livre lx1y4z2)
      (livre lx2y4z2)
      (livre lx3y4z2)
      (livre lx4y4z2)
      (livre lx1y1z3)
      (livre lx2y1z3)
      (livre lx3y1z3)
      (livre lx4y1z3)
      (livre lx1y2z3)
      (livre lx2y2z3)
      (livre lx3y2z3)
      (livre lx4y2z3)
      (livre lx1y3z3)
      (livre lx2y3z3)
      (livre lx3y3z3)
      (livre lx4y3z3)
      (livre lx1y4z3)
      (livre lx2y4z3)
      (livre lx3y4z3)
      (livre lx4y4z3)
      (livre lx1y1z4)
      (livre lx2y1z4)
      (livre lx3y1z4)
      (livre lx4y1z4)
      (livre lx1y2z4)
      (livre lx2y2z4)
      (livre lx3y2z4)
      (livre lx3y2z4)
      (livre lx1y3z4)
      (livre lx2y3z4)
      (livre lx3y3z4)
      (livre lx4y3z4)
      (livre lx1y4z4)
      (livre lx2y4z4)
      (livre lx3y4z4)
      (livre lx4y4z4)
      (atras lx2y1z1 lx1y1z1)
      (atras lx3y1z1 lx2y1z1)
      (atras lx4y1z1 lx3y1z1)
      (atras lx2y2z1 lx1y2z1)
      (atras lx3y2z1 lx2y2z1)
      (atras lx4y2z1 lx3y2z1)
      (atras lx2y3z1 lx1y3z1)
      (atras lx3y3z1 lx2y3z1)
      (atras lx4y3z1 lx3y3z1)
      (atras lx2y4z1 lx1y4z1)
      (atras lx3y4z1 lx2y4z1)
      (atras lx4y4z1 lx3y4z1)
      (atras lx2y1z2 lx1y1z2)
      (atras lx3y1z2 lx2y1z2)
      (atras lx4y1z2 lx3y1z2)
      (atras lx2y2z2 lx1y2z2)
      (atras lx3y2z2 lx2y2z2)
      (atras lx4y2z2 lx3y2z2)
      (atras lx2y3z2 lx1y3z2)
      (atras lx3y3z2 lx2y3z2)
      (atras lx4y3z2 lx3y3z2)
      (atras lx2y4z2 lx1y4z2)
      (atras lx3y4z2 lx2y4z2)
      (atras lx4y4z2 lx3y4z2)
      (atras lx2y1z3 lx1y1z3)
      (atras lx3y1z3 lx2y1z3)
      (atras lx4y1z3 lx3y1z3)
      (atras lx2y2z3 lx1y2z3)
      (atras lx3y2z3 lx2y2z3)
      (atras lx4y2z3 lx3y2z3)
      (atras lx2y3z3 lx1y3z3)
      (atras lx3y3z3 lx2y3z3)
      (atras lx4y3z3 lx3y3z3)
      (atras lx2y4z3 lx1y4z3)
      (atras lx3y4z3 lx2y4z3)
      (atras lx4y4z3 lx3y4z3)
      (atras lx2y1z4 lx1y1z4)
      (atras lx3y1z4 lx2y1z4)
      (atras lx4y1z4 lx3y1z4)
      (atras lx2y2z4 lx1y2z4)
      (atras lx3y2z4 lx2y2z4)
      (atras lx3y2z4 lx3y2z4)
      (atras lx2y3z4 lx1y3z4)
      (atras lx3y3z4 lx2y3z4)
      (atras lx4y3z4 lx3y3z4)
      (atras lx2y4z4 lx1y4z4)
      (atras lx3y4z4 lx2y4z4)
      (atras lx4y4z4 lx3y4z4)
      (esquerda lx1y2z1 lx1y1z1)
      (esquerda lx2y2z1 lx2y1z1)
      (esquerda lx3y2z1 lx3y1z1)
      (esquerda lx4y2z1 lx4y1z1)
      (esquerda lx1y3z1 lx1y2z1)
      (esquerda lx2y3z1 lx2y2z1)
      (esquerda lx3y3z1 lx3y2z1)
      (esquerda lx4y3z1 lx4y2z1)
      (esquerda lx1y4z1 lx1y3z1)
      (esquerda lx2y4z1 lx2y3z1)
      (esquerda lx3y4z1 lx3y3z1)
      (esquerda lx4y4z1 lx4y3z1)
      (esquerda lx1y2z2 lx1y1z2)
      (esquerda lx2y2z2 lx2y1z2)
      (esquerda lx3y2z2 lx3y1z2)
      (esquerda lx4y2z2 lx4y1z2)
      (esquerda lx1y3z2 lx1y2z2)
      (esquerda lx2y3z2 lx2y2z2)
      (esquerda lx3y3z2 lx3y2z2)
      (esquerda lx4y3z2 lx4y2z2)
      (esquerda lx1y4z2 lx1y3z2)
      (esquerda lx2y4z2 lx2y3z2)
      (esquerda lx3y4z2 lx3y3z2)
      (esquerda lx4y4z2 lx4y3z2)
      (esquerda lx1y2z3 lx1y1z3)
      (esquerda lx2y2z3 lx2y1z3)
      (esquerda lx3y2z3 lx3y1z3)
      (esquerda lx4y2z3 lx4y1z3)
      (esquerda lx1y3z3 lx1y2z3)
      (esquerda lx2y3z3 lx2y2z3)
      (esquerda lx3y3z3 lx3y2z3)
      (esquerda lx4y3z3 lx4y2z3)
      (esquerda lx1y4z3 lx1y3z3)
      (esquerda lx2y4z3 lx2y3z3)
      (esquerda lx3y4z3 lx3y3z3)
      (esquerda lx4y4z3 lx4y3z3)
      (esquerda lx1y2z4 lx1y1z4)
      (esquerda lx2y2z4 lx2y1z4)
      (esquerda lx3y2z4 lx3y1z4)
      (esquerda lx3y2z4 lx4y1z4)
      (esquerda lx1y3z4 lx1y2z4)
      (esquerda lx2y3z4 lx2y2z4)
      (esquerda lx3y3z4 lx3y2z4)
      (esquerda lx4y3z4 lx3y2z4)
      (esquerda lx1y4z4 lx1y3z4)
      (esquerda lx2y4z4 lx2y3z4)
      (esquerda lx3y4z4 lx3y3z4)
      (esquerda lx4y4z4 lx4y3z4)
      (acima lx1y1z2 lx1y1z1)
      (acima lx2y1z2 lx2y1z1)
      (acima lx3y1z2 lx3y1z1)
      (acima lx4y1z2 lx4y1z1)
      (acima lx1y2z2 lx1y2z1)
      (acima lx2y2z2 lx2y2z1)
      (acima lx3y2z2 lx3y2z1)
      (acima lx4y2z2 lx4y2z1)
      (acima lx1y3z2 lx1y3z1)
      (acima lx2y3z2 lx2y3z1)
      (acima lx3y3z2 lx3y3z1)
      (acima lx4y3z2 lx4y3z1)
      (acima lx1y4z2 lx1y4z1)
      (acima lx2y4z2 lx2y4z1)
      (acima lx3y4z2 lx3y4z1)
      (acima lx4y4z2 lx4y4z1)
      (acima lx1y1z3 lx1y1z2)
      (acima lx2y1z3 lx2y1z2)
      (acima lx3y1z3 lx3y1z2)
      (acima lx4y1z3 lx4y1z2)
      (acima lx1y2z3 lx1y2z2)
      (acima lx2y2z3 lx2y2z2)
      (acima lx3y2z3 lx3y2z2)
      (acima lx4y2z3 lx4y2z2)
      (acima lx1y3z3 lx1y3z2)
      (acima lx2y3z3 lx2y3z2)
      (acima lx3y3z3 lx3y3z2)
      (acima lx4y3z3 lx4y3z2)
      (acima lx1y4z3 lx1y4z2)
      (acima lx2y4z3 lx2y4z2)
      (acima lx3y4z3 lx3y4z2)
      (acima lx4y4z3 lx4y4z2)
      (acima lx1y1z4 lx1y1z3)
      (acima lx2y1z4 lx2y1z3)
      (acima lx3y1z4 lx3y1z3)
      (acima lx4y1z4 lx4y1z3)
      (acima lx1y2z4 lx1y2z3)
      (acima lx2y2z4 lx2y2z3)
      (acima lx3y2z4 lx3y2z3)
      (acima lx3y2z4 lx4y2z3)
      (acima lx1y3z4 lx1y3z3)
      (acima lx2y3z4 lx2y3z3)
      (acima lx3y3z4 lx3y3z3)
      (acima lx4y3z4 lx4y3z3)
      (acima lx1y4z4 lx1y4z3)
      (acima lx2y4z4 lx2y4z3)
      (acima lx3y4z4 lx3y4z3)
      (acima lx4y4z4 lx4y4z3)
      (plivre2 prod1)
      (plivre2 prod2)
      (plivre2 prod3)
      (plivre2 prod4)
      (plivre3 prod5)
      (plivre3 prod6)
      (plivre3 prod7)
      (plivre3 prod8)
      (plivre3 prod9)
      (plivre3 prod10)
      (plivre3 prod11)
      (plivre3 prod12)
      (plivre3 prod13)
      (plivre3 prod14)
      (plivre3 prod15)
      (plivre3 prod16)
      (plivre4 prod17)
      (plivre4 prod18)
      (plivre4 prod19)
      (plivre4 prod20)
      (plivre4 prod21)
      (plivre4 prod22)
      (plivre4 prod23)
      (plivre4 prod24)
      (plivre4 prod25)
      (plivre4 prod26)
      (plivre4 prod27)
      (plivre4 prod28)
      (plivre4 prod29)
      (plivre4 prod30)
      (plivre4 prod31)
      (plivre4 prod32)
    )
    (:goal
      (and
        (estaEm2 prod1 lx1y1z2)
        (estaEm2 prod2 lx1y4z2)
        (estaEm2 prod3 lx2y1z3)
        (estaEm2 prod4 lx2y1z4)
        (estaEm3 prod5 lx1y1z1)
        (estaEm3 prod6 lx2y1z1)
        (estaEm3 prod7 lx3y2z1)
        (estaEm3 prod8 lx1y3z1)
        (estaEm3 prod9 lx2y3z1)
        (estaEm3 prod10 lx2y2z2)
        (estaEm3 prod11 lx3y2z2)
        (estaEm3 prod12 lx3y2z3)
        (estaEm3 prod13 lx4y3z3)
        (estaEm3 prod14 lx1y2z4)
        (estaEm3 prod15 lx3y2z4)
        (estaEm3 prod16 lx4y3z4)
        (estaEm4 prod17 lx3y1z1)
        (estaEm4 prod18 lx4y1z1)
        (estaEm4 prod19 lx4y2z1)
        (estaEm4 prod20 lx4y3z1)
        (estaEm4 prod21 lx3y4z1)
        (estaEm4 prod22 lx4y4z1)
        (estaEm4 prod23 lx1y2z2)
        (estaEm4 prod24 lx1y3z2)
        (estaEm4 prod25 lx1y1z3)
        (estaEm4 prod26 lx4y1z3)
        (estaEm4 prod27 lx2y2z3)
        (estaEm4 prod28 lx4y2z3)
        (estaEm4 prod29 lx2y3z3)
        (estaEm4 prod30 lx1y4z3)
        (estaEm4 prod31 lx2y4z3)
        (estaEm4 prod32 lx3y4z3)
      )
    )
)
