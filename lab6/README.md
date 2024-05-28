
# Relatório

<br>

## Objetivo do laboratório:

- O objetivo desse lab6 é aplicar o padrão produtor x consumidor com semáforos.

<br>

## Lista de programas usados:

Esta secção mostra como executar de maneira correta os programas para observar os resultados.

- **geraNumeros.c** -> Programa usado para gerar um arquivo binário com uma **sequencia** de números.

  ``` gcc -o geranumeros geraNumeros.c -lpthread -Wall -lm ```

  - **Execução**:

    ``` ./geraNumeros <quantidade_numeros> <nome_do_binario> ```




<br>

- **lenumeros.c** -> Programa usado para ler um arquivo binário , apresentar seu conteúdo na tela e informar a quantidade de numeros primos.

  ``` gcc -o lenumeros lenumeros.c -lpthread -Wall -l ```

  - **Execução**:

     ``` ./lenumeros <nome_do_binario> ```



<br>

- **lab6.c** -> Programa que aplica 

  ``` gcc -o lab6 lab6.c -lpthread -Wall -lm ```

  - **Execução**:

      ``` ./lab6 <nome_do_binario> <numero_de_threads> ```

