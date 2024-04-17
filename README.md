# Programação-Concorrente


# Propósito deste repositório

- Repositório para armazenar códigos ligados a disciplina de Programação Concorrente ICP361 - UFRJ


## lab1.c 
O programa deve ser executado com o seguinte comando: 
```
gcc -o helloC helloC.c -lpthread -Wall -lm
```



<br>

------------------------------------------------------------

<br>

## lab2.c

Porfavor, compile os dois programas (**random.c** e **lab2.c**) com o seguinte comando:

```
gcc -o helloC helloC.c -lpthread -Wall -lm
```
### Passo - a - Passo

Execute da seguinte maneira:

1 - Execute **random.c** da seguinte maneira:

```
./random.c 5 10 > numeros.txt

```
Dessa forma, iremos gerar 5 números que irão variar de 1 até 10 e serão escritos em um arquivo de texto chamado "numeros.txt"


2 - Execute **lab2.c** da seguinte forma:

```
./lab2.c 2 < numeros.txt

```
Nesse exemplo iremos criar apenas 2 threads. Porém cabe ao usuário decidir o número de threads a ser criado.

