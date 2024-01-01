(define (problem Planning_Problem)
    (:domain New_Project_1)
    (:objects
      lx1y1z1 - lugar
      lx2y1z1 - lugar
      lx3y1z1 - lugar
      lx4y1z1 - lugar
      lx5y1z1 - lugar
      lx1y2z1 - lugar
      lx2y2z1 - lugar
      lx3y2z1 - lugar
      lx4y2z1 - lugar
      lx5y2z1 - lugar
      lx1y3z1 - lugar
      lx2y3z1 - lugar
      lx3y3z1 - lugar
      lx4y3z1 - lugar
      lx5y3z1 - lugar
      lx1y4z1 - lugar
      lx2y4z1 - lugar
      lx3y4z1 - lugar
      lx4y4z1 - lugar
      lx5y4z1 - lugar
      lx1y5z1 - lugar
      lx2y5z1 - lugar
      lx3y5z1 - lugar
      lx4y5z1 - lugar
      lx5y5z1 - lugar
      lx1y1z2 - lugar
      lx2y1z2 - lugar
      lx3y1z2 - lugar
      lx4y1z2 - lugar
      lx5y1z2 - lugar
      lx1y2z2 - lugar
      lx2y2z2 - lugar
      lx3y2z2 - lugar
      lx4y2z2 - lugar
      lx5y2z2 - lugar
      lx1y3z2 - lugar
      lx2y3z2 - lugar
      lx3y3z2 - lugar
      lx4y3z2 - lugar
      lx5y3z2 - lugar
      lx1y4z2 - lugar
      lx2y4z2 - lugar
      lx3y4z2 - lugar
      lx4y4z2 - lugar
      lx5y4z2 - lugar
      lx1y5z2 - lugar
      lx2y5z2 - lugar
      lx3y5z2 - lugar
      lx4y5z2 - lugar
      lx5y5z2 - lugar
      lx1y1z3 - lugar
      lx2y1z3 - lugar
      lx3y1z3 - lugar
      lx4y1z3 - lugar
      lx5y1z3 - lugar
      lx1y2z3 - lugar
      lx2y2z3 - lugar
      lx3y2z3 - lugar
      lx4y2z3 - lugar
      lx5y2z3 - lugar
      lx1y3z3 - lugar
      lx2y3z3 - lugar
      lx3y3z3 - lugar
      lx4y3z3 - lugar
      lx5y3z3 - lugar
      lx1y4z3 - lugar
      lx2y4z3 - lugar
      lx3y4z3 - lugar
      lx4y4z3 - lugar
      lx5y4z3 - lugar
      lx1y5z3 - lugar
      lx2y5z3 - lugar
      lx3y5z3 - lugar
      lx4y5z3 - lugar
      lx5y5z3 - lugar
      lx1y1z4 - lugar
      lx2y1z4 - lugar
      lx3y1z4 - lugar
      lx4y1z4 - lugar
      lx5y1z4 - lugar
      lx1y2z4 - lugar
      lx2y2z4 - lugar
      lx3y2z4 - lugar
      lx4y2z4 - lugar
      lx5y2z4 - lugar
      lx1y3z4 - lugar
      lx2y3z4 - lugar
      lx3y3z4 - lugar
      lx4y3z4 - lugar
      lx5y3z4 - lugar
      lx1y4z4 - lugar
      lx2y4z4 - lugar
      lx3y4z4 - lugar
      lx4y4z4 - lugar
      lx5y4z4 - lugar
      lx1y5z4 - lugar
      lx2y5z4 - lugar
      lx3y5z4 - lugar
      lx4y5z4 - lugar
      lx5y5z4 - lugar
      lx1y1z5 - lugar
      lx2y1z5 - lugar
      lx3y1z5 - lugar
      lx4y1z5 - lugar
      lx5y1z5 - lugar
      lx1y2z5 - lugar
      lx2y2z5 - lugar
      lx3y2z5 - lugar
      lx4y2z5 - lugar
      lx5y2z5 - lugar
      lx1y3z5 - lugar
      lx2y3z5 - lugar
      lx3y3z5 - lugar
      lx4y3z5 - lugar
      lx5y3z5 - lugar
      lx1y4z5 - lugar
      lx2y4z5 - lugar
      lx3y4z5 - lugar
      lx4y4z5 - lugar
      lx5y4z5 - lugar
      lx1y5z5 - lugar
      lx2y5z5 - lugar
      lx3y5z5 - lugar
      lx4y5z5 - lugar
      lx5y5z5 - lugar
      prod1 - produto1
      prod2 - produto3
      prod3 - produto4
      prod4 - produto4
      prod5 - produto4
      prod6 - produto4
      prod7 - produto5
      prod8 - produto5
      prod9 - produto5
      prod10 - produto5
      prod11 - produto5
      prod12 - produto5
      prod13 - produto5
      prod14 - produto5
      prod15 - produto5
      prod16 - produto5
      prod17 - produto6
      prod18 - produto6
      prod19 - produto6
      prod20 - produto7
      prod21 - produto7
      prod22 - produto7
      prod23 - produto7
      prod24 - produto7
      prod25 - produto7
      prod26 - produto7
      prod27 - produto7
      prod28 - produto7
      prod29 - produto7
      prod30 - produto7
      prod31 - produto7
      prod32 - produto7
      prod33 - produto7
      prod34 - produto7
      prod35 - produto7
      prod36 - produto7
      prod37 - produto7
      prod38 - produto7
      prod39 - produto7
      prod40 - produto7
      prod41 - produto7
      prod42 - produto7
      prod43 - produto7
      prod44 - produto7
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
      (livre lx5y1z1)
      (piso lx5y1z1)
      (livre lx1y2z1)
      (piso lx1y2z1)
      (livre lx2y2z1)
      (piso lx2y2z1)
      (livre lx3y2z1)
      (piso lx3y2z1)
      (livre lx4y2z1)
      (piso lx4y2z1)
      (livre lx5y2z1)
      (piso lx5y2z1)
      (livre lx1y3z1)
      (piso lx1y3z1)
      (livre lx2y3z1)
      (piso lx2y3z1)
      (livre lx3y3z1)
      (piso lx3y3z1)
      (livre lx4y3z1)
      (piso lx4y3z1)
      (livre lx5y3z1)
      (piso lx5y3z1)
      (livre lx1y4z1)
      (piso lx1y4z1)
      (livre lx2y4z1)
      (piso lx2y4z1)
      (livre lx3y4z1)
      (piso lx3y4z1)
      (livre lx4y4z1)
      (piso lx4y4z1)
      (livre lx5y4z1)
      (piso lx5y4z1)
      (livre lx1y5z1)
      (piso lx1y5z1)
      (livre lx2y5z1)
      (piso lx2y5z1)
      (livre lx3y5z1)
      (piso lx3y5z1)
      (livre lx4y5z1)
      (piso lx4y5z1)
      (livre lx5y5z1)
      (piso lx5y5z1)
      (livre lx1y1z2)
      (livre lx2y1z2)
      (livre lx3y1z2)
      (livre lx4y1z2)
      (livre lx5y1z2)
      (livre lx1y2z2)
      (livre lx2y2z2)
      (livre lx3y2z2)
      (livre lx4y2z2)
      (livre lx5y2z2)
      (livre lx1y3z2)
      (livre lx2y3z2)
      (livre lx3y3z2)
      (livre lx4y3z2)
      (livre lx5y3z2)
      (livre lx1y4z2)
      (livre lx2y4z2)
      (livre lx3y4z2)
      (livre lx4y4z2)
      (livre lx5y4z2)
      (livre lx1y5z2)
      (livre lx2y5z2)
      (livre lx3y5z2)
      (livre lx4y5z2)
      (livre lx5y5z2)
      (livre lx1y1z3)
      (livre lx2y1z3)
      (livre lx3y1z3)
      (livre lx4y1z3)
      (livre lx5y1z3)
      (livre lx1y2z3)
      (livre lx2y2z3)
      (livre lx3y2z3)
      (livre lx4y2z3)
      (livre lx5y2z3)
      (livre lx1y3z3)
      (livre lx2y3z3)
      (livre lx3y3z3)
      (livre lx4y3z3)
      (livre lx5y3z3)
      (livre lx1y4z3)
      (livre lx2y4z3)
      (livre lx3y4z3)
      (livre lx4y4z3)
      (livre lx5y4z3)
      (livre lx1y5z3)
      (livre lx2y5z3)
      (livre lx3y5z3)
      (livre lx4y5z3)
      (livre lx5y5z3)
      (livre lx1y1z4)
      (livre lx2y1z4)
      (livre lx3y1z4)
      (livre lx4y1z4)
      (livre lx5y1z4)
      (livre lx1y2z4)
      (livre lx2y2z4)
      (livre lx3y2z4)
      (livre lx4y2z4)
      (livre lx5y2z4)
      (livre lx1y3z4)
      (livre lx2y3z4)
      (livre lx3y3z4)
      (livre lx4y3z4)
      (livre lx5y3z4)
      (livre lx1y4z4)
      (livre lx2y4z4)
      (livre lx3y4z4)
      (livre lx4y4z4)
      (livre lx5y4z4)
      (livre lx1y5z4)
      (livre lx2y5z4)
      (livre lx3y5z4)
      (livre lx4y5z4)
      (livre lx5y5z4)
      (livre lx1y1z5)
      (livre lx2y1z5)
      (livre lx3y1z5)
      (livre lx4y1z5)
      (livre lx5y1z5)
      (livre lx1y2z5)
      (livre lx2y2z5)
      (livre lx3y2z5)
      (livre lx4y2z5)
      (livre lx5y2z5)
      (livre lx1y3z5)
      (livre lx2y3z5)
      (livre lx3y3z5)
      (livre lx4y3z5)
      (livre lx5y3z5)
      (livre lx1y4z5)
      (livre lx2y4z5)
      (livre lx3y4z5)
      (livre lx4y4z5)
      (livre lx5y4z5)
      (livre lx1y5z5)
      (livre lx2y5z5)
      (livre lx3y5z5)
      (livre lx4y5z5)
      (livre lx5y5z5)
      (atras lx2y1z1 lx1y1z1)
      (atras lx3y1z1 lx2y1z1)
      (atras lx4y1z1 lx3y1z1)
      (atras lx5y1z1 lx4y1z1)
      (atras lx2y2z1 lx1y2z1)
      (atras lx3y2z1 lx2y2z1)
      (atras lx4y2z1 lx3y2z1)
      (atras lx5y2z1 lx4y2z1)
      (atras lx2y3z1 lx1y3z1)
      (atras lx3y3z1 lx2y3z1)
      (atras lx4y3z1 lx3y3z1)
      (atras lx5y3z1 lx4y3z1)
      (atras lx2y4z1 lx1y4z1)
      (atras lx3y4z1 lx2y4z1)
      (atras lx4y4z1 lx3y4z1)
      (atras lx5y4z1 lx4y4z1)
      (atras lx2y5z1 lx1y5z1)
      (atras lx3y5z1 lx2y5z1)
      (atras lx4y5z1 lx3y5z1)
      (atras lx5y5z1 lx4y5z1)
      (atras lx2y1z2 lx1y1z2)
      (atras lx3y1z2 lx2y1z2)
      (atras lx4y1z2 lx3y1z2)
      (atras lx5y1z2 lx4y1z2)
      (atras lx2y2z2 lx1y2z2)
      (atras lx3y2z2 lx2y2z2)
      (atras lx4y2z2 lx3y2z2)
      (atras lx5y2z2 lx4y2z2)
      (atras lx2y3z2 lx1y3z2)
      (atras lx3y3z2 lx2y3z2)
      (atras lx4y3z2 lx3y3z2)
      (atras lx5y3z2 lx4y3z2)
      (atras lx2y4z2 lx1y4z2)
      (atras lx3y4z2 lx2y4z2)
      (atras lx4y4z2 lx3y4z2)
      (atras lx5y4z2 lx4y4z2)
      (atras lx2y5z2 lx1y5z2)
      (atras lx3y5z2 lx2y5z2)
      (atras lx4y5z2 lx3y5z2)
      (atras lx5y5z2 lx4y5z2)
      (atras lx2y1z3 lx1y1z3)
      (atras lx3y1z3 lx2y1z3)
      (atras lx4y1z3 lx3y1z3)
      (atras lx5y1z3 lx4y1z3)
      (atras lx2y2z3 lx1y2z3)
      (atras lx3y2z3 lx2y2z3)
      (atras lx4y2z3 lx3y2z3)
      (atras lx5y2z3 lx4y2z3)
      (atras lx2y3z3 lx1y3z3)
      (atras lx3y3z3 lx2y3z3)
      (atras lx4y3z3 lx3y3z3)
      (atras lx5y3z3 lx4y3z3)
      (atras lx2y4z3 lx1y4z3)
      (atras lx3y4z3 lx2y4z3)
      (atras lx4y4z3 lx3y4z3)
      (atras lx5y4z3 lx4y4z3)
      (atras lx2y5z3 lx1y5z3)
      (atras lx3y5z3 lx2y5z3)
      (atras lx4y5z3 lx3y5z3)
      (atras lx5y5z3 lx4y5z3)
      (atras lx2y1z4 lx1y1z4)
      (atras lx3y1z4 lx2y1z4)
      (atras lx4y1z4 lx3y1z4)
      (atras lx5y1z4 lx4y1z4)
      (atras lx2y2z4 lx1y2z4)
      (atras lx3y2z4 lx2y2z4)
      (atras lx4y2z4 lx3y2z4)
      (atras lx5y2z4 lx4y2z4)
      (atras lx2y3z4 lx1y3z4)
      (atras lx3y3z4 lx2y3z4)
      (atras lx4y3z4 lx3y3z4)
      (atras lx5y3z4 lx4y3z4)
      (atras lx2y4z4 lx1y4z4)
      (atras lx3y4z4 lx2y4z4)
      (atras lx4y4z4 lx3y4z4)
      (atras lx5y4z4 lx4y4z4)
      (atras lx2y5z4 lx1y5z4)
      (atras lx3y5z4 lx2y5z4)
      (atras lx4y5z4 lx3y5z4)
      (atras lx5y5z4 lx4y5z4)
      (atras lx2y1z5 lx1y1z5)
      (atras lx3y1z5 lx2y1z5)
      (atras lx4y1z5 lx3y1z5)
      (atras lx5y1z5 lx4y1z5)
      (atras lx2y2z5 lx1y2z5)
      (atras lx3y2z5 lx2y2z5)
      (atras lx4y2z5 lx3y2z5)
      (atras lx5y2z5 lx4y2z5)
      (atras lx2y3z5 lx1y3z5)
      (atras lx3y3z5 lx2y3z5)
      (atras lx4y3z5 lx3y3z5)
      (atras lx5y3z5 lx4y3z5)
      (atras lx2y4z5 lx1y4z5)
      (atras lx3y4z5 lx2y4z5)
      (atras lx4y4z5 lx3y4z5)
      (atras lx5y4z5 lx4y4z5)
      (atras lx2y5z5 lx1y5z5)
      (atras lx3y5z5 lx2y5z5)
      (atras lx4y5z5 lx3y5z5)
      (atras lx5y5z5 lx4y5z5)
      (esquerda lx1y2z1 lx1y1z1)
      (esquerda lx2y2z1 lx2y1z1)
      (esquerda lx3y2z1 lx3y1z1)
      (esquerda lx4y2z1 lx4y1z1)
      (esquerda lx5y2z1 lx5y1z1)
      (esquerda lx1y3z1 lx1y2z1)
      (esquerda lx2y3z1 lx2y2z1)
      (esquerda lx3y3z1 lx3y2z1)
      (esquerda lx4y3z1 lx4y2z1)
      (esquerda lx5y3z1 lx5y2z1)
      (esquerda lx1y4z1 lx1y3z1)
      (esquerda lx2y4z1 lx2y3z1)
      (esquerda lx3y4z1 lx3y3z1)
      (esquerda lx4y4z1 lx4y3z1)
      (esquerda lx5y4z1 lx5y3z1)
      (esquerda lx1y5z1 lx1y4z1)
      (esquerda lx2y5z1 lx2y4z1)
      (esquerda lx3y5z1 lx3y4z1)
      (esquerda lx4y5z1 lx4y4z1)
      (esquerda lx5y5z1 lx5y4z1)
      (esquerda lx1y2z2 lx1y1z2)
      (esquerda lx2y2z2 lx2y1z2)
      (esquerda lx3y2z2 lx3y1z2)
      (esquerda lx4y2z2 lx4y1z2)
      (esquerda lx5y2z2 lx5y1z2)
      (esquerda lx1y3z2 lx1y2z2)
      (esquerda lx2y3z2 lx2y2z2)
      (esquerda lx3y3z2 lx3y2z2)
      (esquerda lx4y3z2 lx4y2z2)
      (esquerda lx5y3z2 lx5y2z2)
      (esquerda lx1y4z2 lx1y3z2)
      (esquerda lx2y4z2 lx2y3z2)
      (esquerda lx3y4z2 lx3y3z2)
      (esquerda lx4y4z2 lx4y3z2)
      (esquerda lx5y4z2 lx5y3z2)
      (esquerda lx1y5z2 lx1y4z2)
      (esquerda lx2y5z2 lx2y4z2)
      (esquerda lx3y5z2 lx3y4z2)
      (esquerda lx4y5z2 lx4y4z2)
      (esquerda lx5y5z2 lx5y4z2)
      (esquerda lx1y2z3 lx1y1z3)
      (esquerda lx2y2z3 lx2y1z3)
      (esquerda lx3y2z3 lx3y1z3)
      (esquerda lx4y2z3 lx4y1z3)
      (esquerda lx5y2z3 lx5y1z3)
      (esquerda lx1y3z3 lx1y2z3)
      (esquerda lx2y3z3 lx2y2z3)
      (esquerda lx3y3z3 lx3y2z3)
      (esquerda lx4y3z3 lx4y2z3)
      (esquerda lx5y3z3 lx5y2z3)
      (esquerda lx1y4z3 lx1y3z3)
      (esquerda lx2y4z3 lx2y3z3)
      (esquerda lx3y4z3 lx3y3z3)
      (esquerda lx4y4z3 lx4y3z3)
      (esquerda lx5y4z3 lx5y3z3)
      (esquerda lx1y5z3 lx1y4z3)
      (esquerda lx2y5z3 lx2y4z3)
      (esquerda lx3y5z3 lx3y4z3)
      (esquerda lx4y5z3 lx4y4z3)
      (esquerda lx5y5z3 lx5y4z3)
      (esquerda lx1y2z4 lx1y1z4)
      (esquerda lx2y2z4 lx2y1z4)
      (esquerda lx3y2z4 lx3y1z4)
      (esquerda lx4y2z4 lx4y1z4)
      (esquerda lx5y2z4 lx5y1z4)
      (esquerda lx1y3z4 lx1y2z4)
      (esquerda lx2y3z4 lx2y2z4)
      (esquerda lx3y3z4 lx3y2z4)
      (esquerda lx4y3z4 lx4y2z4)
      (esquerda lx5y3z4 lx5y2z4)
      (esquerda lx1y4z4 lx1y3z4)
      (esquerda lx2y4z4 lx2y3z4)
      (esquerda lx3y4z4 lx3y3z4)
      (esquerda lx4y4z4 lx4y3z4)
      (esquerda lx5y4z4 lx5y3z4)
      (esquerda lx1y5z4 lx1y4z4)
      (esquerda lx2y5z4 lx2y4z4)
      (esquerda lx3y5z4 lx3y4z4)
      (esquerda lx4y5z4 lx4y4z4)
      (esquerda lx5y5z4 lx5y4z4)
      (esquerda lx1y2z5 lx1y1z5)
      (esquerda lx2y2z5 lx2y1z5)
      (esquerda lx3y2z5 lx3y1z5)
      (esquerda lx4y2z5 lx4y1z5)
      (esquerda lx5y2z5 lx5y1z5)
      (esquerda lx1y3z5 lx1y2z5)
      (esquerda lx2y3z5 lx2y2z5)
      (esquerda lx3y3z5 lx3y2z5)
      (esquerda lx4y3z5 lx4y2z5)
      (esquerda lx5y3z5 lx5y2z5)
      (esquerda lx1y4z5 lx1y3z5)
      (esquerda lx2y4z5 lx2y3z5)
      (esquerda lx3y4z5 lx3y3z5)
      (esquerda lx4y4z5 lx4y3z5)
      (esquerda lx5y4z5 lx5y3z5)
      (esquerda lx1y5z5 lx1y4z5)
      (esquerda lx2y5z5 lx2y4z5)
      (esquerda lx3y5z5 lx3y4z5)
      (esquerda lx4y5z5 lx4y4z5)
      (esquerda lx5y5z5 lx5y4z5)
      (acima lx1y1z2 lx1y1z1)
      (acima lx2y1z2 lx2y1z1)
      (acima lx3y1z2 lx3y1z1)
      (acima lx4y1z2 lx4y1z1)
      (acima lx5y1z2 lx5y1z1)
      (acima lx1y2z2 lx1y2z1)
      (acima lx2y2z2 lx2y2z1)
      (acima lx3y2z2 lx3y2z1)
      (acima lx4y2z2 lx4y2z1)
      (acima lx5y2z2 lx5y2z1)
      (acima lx1y3z2 lx1y3z1)
      (acima lx2y3z2 lx2y3z1)
      (acima lx3y3z2 lx3y3z1)
      (acima lx4y3z2 lx4y3z1)
      (acima lx5y3z2 lx5y3z1)
      (acima lx1y4z2 lx1y4z1)
      (acima lx2y4z2 lx2y4z1)
      (acima lx3y4z2 lx3y4z1)
      (acima lx4y4z2 lx4y4z1)
      (acima lx5y4z2 lx5y4z1)
      (acima lx1y5z2 lx1y5z1)
      (acima lx2y5z2 lx2y5z1)
      (acima lx3y5z2 lx3y5z1)
      (acima lx4y5z2 lx4y5z1)
      (acima lx5y5z2 lx5y5z1)
      (acima lx1y1z3 lx1y1z2)
      (acima lx2y1z3 lx2y1z2)
      (acima lx3y1z3 lx3y1z2)
      (acima lx4y1z3 lx4y1z2)
      (acima lx5y1z3 lx5y1z2)
      (acima lx1y2z3 lx1y2z2)
      (acima lx2y2z3 lx2y2z2)
      (acima lx3y2z3 lx3y2z2)
      (acima lx4y2z3 lx4y2z2)
      (acima lx5y2z3 lx5y2z2)
      (acima lx1y3z3 lx1y3z2)
      (acima lx2y3z3 lx2y3z2)
      (acima lx3y3z3 lx3y3z2)
      (acima lx4y3z3 lx4y3z2)
      (acima lx5y3z3 lx5y3z2)
      (acima lx1y4z3 lx1y4z2)
      (acima lx2y4z3 lx2y4z2)
      (acima lx3y4z3 lx3y4z2)
      (acima lx4y4z3 lx4y4z2)
      (acima lx5y4z3 lx5y4z2)
      (acima lx1y5z3 lx1y5z2)
      (acima lx2y5z3 lx2y5z2)
      (acima lx3y5z3 lx3y5z2)
      (acima lx4y5z3 lx4y5z2)
      (acima lx5y5z3 lx5y5z2)
      (acima lx1y1z4 lx1y1z3)
      (acima lx2y1z4 lx2y1z3)
      (acima lx3y1z4 lx3y1z3)
      (acima lx4y1z4 lx4y1z3)
      (acima lx5y1z4 lx5y1z3)
      (acima lx1y2z4 lx1y2z3)
      (acima lx2y2z4 lx2y2z3)
      (acima lx3y2z4 lx3y2z3)
      (acima lx4y2z4 lx4y2z3)
      (acima lx5y2z4 lx5y2z3)
      (acima lx1y3z4 lx1y3z3)
      (acima lx2y3z4 lx2y3z3)
      (acima lx3y3z4 lx3y3z3)
      (acima lx4y3z4 lx4y3z3)
      (acima lx5y3z4 lx5y3z3)
      (acima lx1y4z4 lx1y4z3)
      (acima lx2y4z4 lx2y4z3)
      (acima lx3y4z4 lx3y4z3)
      (acima lx4y4z4 lx4y4z3)
      (acima lx5y4z4 lx5y4z3)
      (acima lx1y5z4 lx1y5z3)
      (acima lx2y5z4 lx2y5z3)
      (acima lx3y5z4 lx3y5z3)
      (acima lx4y5z4 lx4y5z3)
      (acima lx5y5z4 lx5y5z3)
      (acima lx1y1z5 lx1y1z4)
      (acima lx2y1z5 lx2y1z4)
      (acima lx3y1z5 lx3y1z4)
      (acima lx4y1z5 lx4y1z4)
      (acima lx5y1z5 lx5y1z4)
      (acima lx1y2z5 lx1y2z4)
      (acima lx2y2z5 lx2y2z4)
      (acima lx3y2z5 lx3y2z4)
      (acima lx4y2z5 lx4y2z4)
      (acima lx5y2z5 lx5y2z4)
      (acima lx1y3z5 lx1y3z4)
      (acima lx2y3z5 lx2y3z4)
      (acima lx3y3z5 lx3y3z4)
      (acima lx4y3z5 lx4y3z4)
      (acima lx5y3z5 lx5y3z4)
      (acima lx1y4z5 lx1y4z4)
      (acima lx2y4z5 lx2y4z4)
      (acima lx3y4z5 lx3y4z4)
      (acima lx4y4z5 lx4y4z4)
      (acima lx5y4z5 lx5y4z4)
      (acima lx1y5z5 lx1y5z4)
      (acima lx2y5z5 lx2y5z4)
      (acima lx3y5z5 lx3y5z4)
      (acima lx4y5z5 lx4y5z4)
      (acima lx5y5z5 lx5y5z4)
      (plivre1 prod1)
      (plivre3 prod2)
      (plivre4 prod3)
      (plivre4 prod4)
      (plivre4 prod5)
      (plivre4 prod6)
      (plivre5 prod7)
      (plivre5 prod8)
      (plivre5 prod9)
      (plivre5 prod10)
      (plivre5 prod11)
      (plivre5 prod12)
      (plivre5 prod13)
      (plivre5 prod14)
      (plivre5 prod15)
      (plivre5 prod16)
      (plivre6 prod17)
      (plivre6 prod18)
      (plivre6 prod19)
      (plivre7 prod20)
      (plivre7 prod21)
      (plivre7 prod22)
      (plivre7 prod23)
      (plivre7 prod24)
      (plivre7 prod25)
      (plivre7 prod26)
      (plivre7 prod27)
      (plivre7 prod28)
      (plivre7 prod29)
      (plivre7 prod30)
      (plivre7 prod31)
      (plivre7 prod32)
      (plivre7 prod33)
      (plivre7 prod34)
      (plivre7 prod35)
      (plivre7 prod36)
      (plivre7 prod37)
      (plivre7 prod38)
      (plivre7 prod39)
      (plivre7 prod40)
      (plivre7 prod41)
      (plivre7 prod42)
      (plivre7 prod43)
      (plivre7 prod44)
    )
    (:goal
      (and
        (estaEm1 prod1 lx4y3z5)
        (estaEm3 prod2 lx1y1z5)
        (estaEm4 prod3 lx5y1z4)
        (estaEm4 prod4 lx4y4z4)
        (estaEm4 prod5 lx1y5z4)
        (estaEm4 prod6 lx5y5z4)
        (estaEm5 prod7 lx1y1z1)
        (estaEm5 prod8 lx1y3z1)
        (estaEm5 prod9 lx2y5z1)
        (estaEm5 prod10 lx1y2z4)
        (estaEm5 prod11 lx1y4z4)
        (estaEm5 prod12 lx2y1z5)
        (estaEm5 prod13 lx2y2z5)
        (estaEm5 prod14 lx1y3z5)
        (estaEm5 prod15 lx1y4z5)
        (estaEm5 prod16 lx2y5z5)
        (estaEm6 prod17 lx4y1z1)
        (estaEm6 prod18 lx5y2z4)
        (estaEm6 prod19 lx5y2z5)
        (estaEm7 prod20 lx5y1z1)
        (estaEm7 prod21 lx1y2z1)
        (estaEm7 prod22 lx2y2z1)
        (estaEm7 prod23 lx3y2z1)
        (estaEm7 prod24 lx5y2z1)
        (estaEm7 prod25 lx5y3z1)
        (estaEm7 prod26 lx1y4z1)
        (estaEm7 prod27 lx2y4z1)
        (estaEm7 prod28 lx3y4z1)
        (estaEm7 prod29 lx4y4z1)
        (estaEm7 prod30 lx5y4z1)
        (estaEm7 prod31 lx1y5z1)
        (estaEm7 prod32 lx5y5z1)
        (estaEm7 prod33 lx1y1z2)
        (estaEm7 prod34 lx2y1z2)
        (estaEm7 prod35 lx3y1z2)
        (estaEm7 prod36 lx4y1z2)
        (estaEm7 prod37 lx4y2z2)
        (estaEm7 prod38 lx1y3z2)
        (estaEm7 prod39 lx2y3z2)
        (estaEm7 prod40 lx3y3z2)
        (estaEm7 prod41 lx4y3z2)
        (estaEm7 prod42 lx2y5z2)
        (estaEm7 prod43 lx3y5z2)
        (estaEm7 prod44 lx4y5z2)
      )
    )
)
