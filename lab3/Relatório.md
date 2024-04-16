
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
<br>


## Análise de tempo de execução

- Todos os tempos abaixo são um média aritmética de três execuções dos programas.
<br>

### Sequencial

|        | Tempo de execução total (segundos) | Tempo de preparação (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.39629466  | 0.0015023 | 0.39225 |  0.0025393 |
| matriz1_1000x1000 . matriz2_1000x1000 | 3.4989293 | 0.0047546| 3.48200233|  0.012172333|
| matriz1_2000x2000 . matriz2_2000x2000 | 48.06427199 | 0.011933  | 47.99428366 | 0.05805466 |


### Concorrente 1 thread

|        | Tempo de execução total (segundos) | Tempo de preparação (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.39629466  | 0.0015023 | 0.39225 |  0.0025393 |
| matriz1_1000x1000 . matriz2_1000x1000 | 3.4989293 | 0.0047546 | 3.48200233|  0.012172333|
| matriz1_2000x2000 . matriz2_2000x2000 | 68.017932 |0.0094466666666 | 67.997206666 | 0.0112786666666 |


### Concorrente 2 thread

|        | Tempo de execução total (segundos) | Tempo de preparação (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.317127  | 0.00176033333 | 0.31394766666  |  0.001419000000 |
| matriz1_1000x1000 . matriz2_1000x1000 | 3.16676433 | 0.003401333 | 3.158213 |  0.005150 |
| matriz1_2000x2000 . matriz2_2000x2000 | 34.651016 | 0.0801966666 | 34.556617 | 0.01420233333333 |



### Concorrente 4 thread

|        | Tempo de execução total (segundos) | Tempo de preparação (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.2334376665  | 0.0009976666| 0.230909 | 0.001531 |
| matriz1_1000x1000 . matriz2_1000x1000 | 2.07622066666 | 0.002862999| 2.0680176666 | 0.00534 |
| matriz1_2000x2000 . matriz2_2000x2000 | 22.371884666 | 0.00992100 | 22.35016066 | 0.011803 |



### Concorrente 8 thread

|        | Tempo de execução total (segundos) | Tempo de preparação (segundos) | Tempo de processamento (segundos) | Tempo de finalização (segundos) |
|--------|------------------------------------|-----------------------------------|-----------------------------------|---------------------------------|
| matriz1_500x500 . matriz2_500x500 | 0.235331666666  | 0.00149233333333 | 0.231527999999| 0.0023113333333 |
| matriz1_1000x1000 . matriz2_1000x1000 | 2.17059233 | 0.0048623333333| 2.16176066 | 0.00396933 |
| matriz1_2000x2000 . matriz2_2000x2000 | 23.41714533 | 0.0111756 | 23.39367133  | 0.0122333 |


