
# Relatório

<br>

## Objetivo do laboratório:

- O objetivo desse lab3 é demonstrar como a capacidade de processamento de dados de forma paralela pode possuir um tempo de execução menor em comparação à execucação de atividades sequenciais em um programa CPU Bound.

<br>

## Lista de programas usados:

Esta secção mostra como executar de maneira correta os programas para observar os resultados.

- **geramatriz.c** -> Programa usado para gerar um arquivo binário com uma **matriz** de números aleatórios as dimensões desejadas pelo usuário.

  ``` gcc geramatriz.c -o geramatriz <numero_de_linhas> <numero_de_colunas> ```

  - **Execução**:

    ``` ./geramatriz 500 500 <nome_do_binario> ```





<br>

- **lematriz.c** -> Programa usado para ler um arquivo binário e apresentar seu conteúdo na tela.

  ``` gcc lematriz.c -o leamatriz ```

  - **Execução**:

     ``` ./lematriz <nome_do_binario> ```



<br>

- **sequencial.c** -> Programa usado para multiplicar duas matrizes (contidas em arquivos binários) com dimensões M por N de forma sequencial e escrever o resultado e um arquivo binário. O programa também impreme o tempo que 

  ``` gcc sequencial.c -o sequencial <nome_matriz1> <nome_matriz2> <nome_matriz_do_resultado> ```

  - **Execução**:

      ``` ./sequencial <matriz1> <matriz2> <matriz_do_resultado> ```



<br>

- **concorrente.c** -> Programa semelhante ao **sequencial.c** porém realiza a operação de multiplicação de matrizes de forma concorrente

  ``` gcc sequencial.c -o sequencial <nome_matriz1> <nome_matriz2> <nome_matriz2> ```

  - **Execução**:

      ``` ./concorrente <matriz1> <matriz2> <matriz3> <numero_de_threads>```

<br>

## Configuração da Máquina

- Todos os programas foram executados em uma máquina virtual com Kali Linux.

<br>
CPU: Intel Core i3 10105F CPU 3.70GHz (4 núcleos) <br>
GPU: NVIDIA GeForce GTX 1650<br>
Memory: 9500MiB 

<br>

## Análise de tempo de execução

## Sequencial
|        | Tempo de execução total (segundos) | Tempo de inicialização (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.337232 | 0.003446 | 0.332933 | 0.001186 |
| matriz1_1000x1000 . matriz2_1000x1000 | 2.663080 | 0.007834 | 2.651478 | 0.005435 |
| matriz1_2000x2000 . matriz2_2000x2000 | 22.201955 | 0.014359 | 22.174885 | 0.013379 |
