# evalunidad4-team
evalunidad4-team created by GitHub Classroom

Para este trabajo se va a implementar un programa que simule el funcionamiento de un programa de analisis estadisticos y procesos estocrasticos.
para ello se plantea utilizar el sistema de productor y consumidor para generar datos aleatorios dentro de un rango e organizarlos en una tabla. 

Para ralizar el codigo en C se va a usar los hilos. Se va utilizar un buffer que sera compartido por todos los hilos, el productor va a generar numeros
aleatorios entre 1 - 30 y los almacena en el buffer. El consumidos va a leer el buffer y va a ir organizando los numeros de menor a mayor en otro buffer. 
Cuando alguno de los dos hilos este en la misma posicion del buffer, se va a dormir alguno de los dos hilos. Al final del programa se va a imprimr la lista
de numeros organizada. El usuario solo podra ingresar el numero de iteraciones que quiere que el programa realce e interactuar con su interfaz.
