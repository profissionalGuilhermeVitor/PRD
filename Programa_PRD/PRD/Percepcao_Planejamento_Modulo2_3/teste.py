
import timeit


inicio = timeit.default_timer()
fim=timeit.default_timer()
while fim-inicio<3:
    

    fim = timeit.default_timer()
    print ('duracao: %f' % (fim - inicio))