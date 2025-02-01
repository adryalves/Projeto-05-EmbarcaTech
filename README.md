# Projeto-05-EmbarcaTech: Controle de LEDs e Botões com BitDogLab

## Link do vídeo de descrição do projeto


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
   - **Formatação fixa:** Cada número será exibido na matriz em um formato predefinido, semelhante a caracteres digitais.
   - Alternativamente, um estilo criativo pode ser utilizado, desde que o número seja claramente identificável.

## Requisitos do Projeto
### 1. Uso de Interrupções
- As funcionalidades dos botões devem ser implementadas utilizando **rotinas de interrupção (IRQ)**.

### 2. Debouncing via Software
- O bouncing dos botões deve ser tratado via software para garantir leituras corretas.

### 3. Controle de LEDs
- O projeto deve demonstrar o uso de **LEDs comuns** e **LEDs WS2812**, explorando diferentes formas de controle.

### 4. Organização do Código
- O código deve ser modular, organizado e seguir boas práticas de desenvolvimento.

## Como Executar
1. Conecte os componentes conforme a descrição do projeto.
2. Compile e carregue o código na placa **BitDogLab**.
3. Utilize os botões para interagir com os números exibidos na matriz de LEDs.

## Tecnologias Utilizadas
- Microcontroladores BitDogLab
- Linguagem C/C++
- Biblioteca para controle de LEDs WS2812
