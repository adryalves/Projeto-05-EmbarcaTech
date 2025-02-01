# Projeto-05-EmbarcaTech: Controle de LEDs e Botões com BitDogLab

## Link do vídeo de descrição do projeto
https://drive.google.com/file/d/1zBKsFCgehge7lWn2FylcSBcEa2ifkYd7/view?usp=sharing

## Descrição do Projeto

Este projeto utiliza a placa **BitDogLab** e os seguintes componentes:

- **Matriz 5x5 de LEDs WS2812** (endereçáveis), conectada à GPIO 7.
- **LED RGB**, com os pinos conectados às GPIOs 11, 12 e 13.
- **Botão A** conectado à GPIO 5.
- **Botão B** conectado à GPIO 6.

## Funcionalidades do Projeto

1. O LED vermelho do LED RGB deve piscar continuamente **5 vezes por segundo**.
2. O **Botão A** incrementa o número exibido na matriz de LEDs a cada pressionamento.
3. O **Botão B** decrementa o número exibido na matriz de LEDs a cada pressionamento.
4. Os **LEDs WS2812** devem exibir números de **0 a 9** com efeitos visuais.

## Requisitos do Projeto

### 1. Uso de Interrupções

- As funcionalidades dos botões são implementadas utilizando **rotinas de interrupção (IRQ)**.

### 2. Debouncing via Software

- O bouncing dos botões são tratados via software para garantir leituras corretas.

### 3. Controle de LEDs

- O projeto demonstra o uso de **LEDs comuns** e **LEDs WS2812**, explorando diferentes formas de controle.

## Como Executar

1.Compile o código

2. Execute o código a depender da infraestrutura.
 - 2.1 Se for no simulador, entre no diagram.json e aperte o botão de executar
 - 2.3 Se for na placa, Conecte a placa **BitDogLab** ao notebook pelo USB, faça o Bootsel e
  aperte o run
3. Utilize os botões para interagir com os números exibidos na matriz de LEDs.

## Tecnologias Utilizadas

- Microcontroladores BitDogLab
- Linguagem C/C++
- Biblioteca para controle de LEDs WS2812
