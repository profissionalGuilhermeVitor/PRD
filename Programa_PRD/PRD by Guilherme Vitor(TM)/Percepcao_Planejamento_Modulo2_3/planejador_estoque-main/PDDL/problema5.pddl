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
      lx4y2z4 - lugar
      lx1y3z4 - lugar
      lx2y3z4 - lugar
      lx3y3z4 - lugar
      lx4y3z4 - lugar
      lx1y4z4 - lugar
      lx2y4z4 - lugar
      lx3y4z4 - lugar
      lx4y4z4 - lugar
      prod1 - produto1
      prod2 - produto1
      prod3 - produto1
      prod4 - produto1
      prod5 - produto1
      prod6 - produto1
      prod7 - produto1
      prod8 - produto1
      prod9 - produto1
      prod10 - produto1
      prod11 - produto1
      prod12 - produto1
      prod13 - produto1
      prod14 - produto1
      prod15 - produto1
      prod16 - produto1
      prod17 - produto1
      prod18 - produto1
      prod19 - produto1
      prod20 - produto1
      prod21 - produto1
      prod22 - produto1
      prod23 - produto1
      prod24 - produto1
      prod25 - produto1
      prod26 - produto1
      prod27 - produto1
      prod28 - produto1
      prod29 - produto1
      prod30 - produto1
      prod31 - produto1
      prod32 - produto1
      prod33 - produto1
      prod34 - produto1
      prod35 - produto1
      prod36 - produto1
      prod37 - produto1
      prod38 - produto1
      prod39 - produto1
      prod40 - produto1
      prod41 - produto1
      prod42 - produto1
      prod43 - produto1
      prod44 - produto1
      prod45 - produto1
      prod46 - produto1
      prod47 - produto1
      prod48 - produto1
      prod49 - produto1
      prod50 - produto1
      prod51 - produto1
      prod52 - produto1
      prod53 - produto1
      prod54 - produto1
      prod55 - produto1
      prod56 - produto1
      prod57 - produto1
      prod58 - produto1
      prod59 - produto1
      prod60 - produto1
      prod61 - produto1
      prod62 - produto1
      prod63 - produto1
      prod64 - produto1
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
      (livre lx4y2z4)
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
      (atras lx4y2z4 lx3y2z4)
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
      (esquerda lx4y2z4 lx4y1z4)
      (esquerda lx1y3z4 lx1y2z4)
      (esquerda lx2y3z4 lx2y2z4)
      (esquerda lx3y3z4 lx3y2z4)
      (esquerda lx4y3z4 lx4y2z4)
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
      (acima lx4y2z4 lx4y2z3)
      (acima lx1y3z4 lx1y3z3)
      (acima lx2y3z4 lx2y3z3)
      (acima lx3y3z4 lx3y3z3)
      (acima lx4y3z4 lx4y3z3)
      (acima lx1y4z4 lx1y4z3)
      (acima lx2y4z4 lx2y4z3)
      (acima lx3y4z4 lx3y4z3)
      (acima lx4y4z4 lx4y4z3)
      (plivre1 prod1)
      (plivre1 prod2)
      (plivre1 prod3)
      (plivre1 prod4)
      (plivre1 prod5)
      (plivre1 prod6)
      (plivre1 prod7)
      (plivre1 prod8)
      (plivre1 prod9)
      (plivre1 prod10)
      (plivre1 prod11)
      (plivre1 prod12)
      (plivre1 prod13)
      (plivre1 prod14)
      (plivre1 prod15)
      (plivre1 prod16)
      (plivre1 prod17)
      (plivre1 prod18)
      (plivre1 prod19)
      (plivre1 prod20)
      (plivre1 prod21)
      (plivre1 prod22)
      (plivre1 prod23)
      (plivre1 prod24)
      (plivre1 prod25)
      (plivre1 prod26)
      (plivre1 prod27)
      (plivre1 prod28)
      (plivre1 prod29)
      (plivre1 prod30)
      (plivre1 prod31)
      (plivre1 prod32)
      (plivre1 prod33)
      (plivre1 prod34)
      (plivre1 prod35)
      (plivre1 prod36)
      (plivre1 prod37)
      (plivre1 prod38)
      (plivre1 prod39)
      (plivre1 prod40)
      (plivre1 prod41)
      (plivre1 prod42)
      (plivre1 prod43)
      (plivre1 prod44)
      (plivre1 prod45)
      (plivre1 prod46)
      (plivre1 prod47)
      (plivre1 prod48)
      (plivre1 prod49)
      (plivre1 prod50)
      (plivre1 prod51)
      (plivre1 prod52)
      (plivre1 prod53)
      (plivre1 prod54)
      (plivre1 prod55)
      (plivre1 prod56)
      (plivre1 prod57)
      (plivre1 prod58)
      (plivre1 prod59)
      (plivre1 prod60)
      (plivre1 prod61)
      (plivre1 prod62)
      (plivre1 prod63)
      (plivre1 prod64)
    )
    (:goal
      (and
        (estaEm1 prod1 lx1y1z1)
        (estaEm1 prod2 lx2y1z1)
        (estaEm1 prod3 lx3y1z1)
        (estaEm1 prod4 lx4y1z1)
        (estaEm1 prod5 lx1y2z1)
        (estaEm1 prod6 lx2y2z1)
        (estaEm1 prod7 lx3y2z1)
        (estaEm1 prod8 lx4y2z1)
        (estaEm1 prod9 lx1y3z1)
        (estaEm1 prod10 lx2y3z1)
        (estaEm1 prod11 lx3y3z1)
        (estaEm1 prod12 lx4y3z1)
        (estaEm1 prod13 lx1y4z1)
        (estaEm1 prod14 lx2y4z1)
        (estaEm1 prod15 lx3y4z1)
        (estaEm1 prod16 lx4y4z1)
        (estaEm1 prod17 lx1y1z2)
        (estaEm1 prod18 lx2y1z2)
        (estaEm1 prod19 lx3y1z2)
        (estaEm1 prod20 lx4y1z2)
        (estaEm1 prod21 lx1y2z2)
        (estaEm1 prod22 lx2y2z2)
        (estaEm1 prod23 lx3y2z2)
        (estaEm1 prod24 lx4y2z2)
        (estaEm1 prod25 lx1y3z2)
        (estaEm1 prod26 lx2y3z2)
        (estaEm1 prod27 lx3y3z2)
        (estaEm1 prod28 lx4y3z2)
        (estaEm1 prod29 lx1y4z2)
        (estaEm1 prod30 lx2y4z2)
        (estaEm1 prod31 lx3y4z2)
        (estaEm1 prod32 lx4y4z2)
        (estaEm1 prod33 lx1y1z3)
        (estaEm1 prod34 lx2y1z3)
        (estaEm1 prod35 lx3y1z3)
        (estaEm1 prod36 lx4y1z3)
        (estaEm1 prod37 lx1y2z3)
        (estaEm1 prod38 lx2y2z3)
        (estaEm1 prod39 lx3y2z3)
        (estaEm1 prod40 lx4y2z3)
        (estaEm1 prod41 lx1y3z3)
        (estaEm1 prod42 lx2y3z3)
        (estaEm1 prod43 lx3y3z3)
        (estaEm1 prod44 lx4y3z3)
        (estaEm1 prod45 lx1y4z3)
        (estaEm1 prod46 lx2y4z3)
        (estaEm1 prod47 lx3y4z3)
        (estaEm1 prod48 lx4y4z3)
        (estaEm1 prod49 lx1y1z4)
        (estaEm1 prod50 lx2y1z4)
        (estaEm1 prod51 lx3y1z4)
        (estaEm1 prod52 lx4y1z4)
        (estaEm1 prod53 lx1y2z4)
        (estaEm1 prod54 lx2y2z4)
        (estaEm1 prod55 lx3y2z4)
        (estaEm1 prod56 lx4y2z4)
        (estaEm1 prod57 lx1y3z4)
        (estaEm1 prod58 lx2y3z4)
        (estaEm1 prod59 lx3y3z4)
        (estaEm1 prod60 lx4y3z4)
        (estaEm1 prod61 lx1y4z4)
        (estaEm1 prod62 lx2y4z4)
        (estaEm1 prod63 lx3y4z4)
        (estaEm1 prod64 lx4y4z4)
      )
    )
)
