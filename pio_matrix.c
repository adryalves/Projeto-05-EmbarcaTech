#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// arquivo .pio
#include "pio_matrix.pio.h"

// número de LEDs
#define NUM_PIXELS 25

// pino de saída
#define OUT_PIN 7

// botão de interupção
const uint button_A = 5;
const uint button_B = 6;

const uint ledA_pin = 13; // Red => GPIO13

static volatile uint numero_atual = 0;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)

static void gpio_irq_handler(uint gpio, uint32_t events);

// vetores pra criação dos numeros
double numero0[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero1[NUM_PIXELS] = {0.0, 0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 1.0, 0.0,
                              1.0, 0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero2[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              0.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero3[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero4[NUM_PIXELS] = {1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0, 1.0};

double numero5[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              0.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero6[NUM_PIXELS] = {1.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero7[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0, 1.0};

double numero8[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

double numero9[NUM_PIXELS] = {1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 1.0,
                              1.0, 1.0, 1.0, 1.0, 1.0,
                              1.0, 0.0, 0.0, 0.0, 0.0,
                              1.0, 1.0, 1.0, 1.0, 1.0};

// rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// rotina para acionar a matrix de leds - ws2812b
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{

    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (i % 2 == 0)
        {
            valor_led = matrix_rgb(desenho[24 - i], r = 0.0, g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        else
        {
            valor_led = matrix_rgb(b = 0.0, desenho[24 - i], g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

void desenharNumero(uint numero, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{

    switch (numero)
    {
    case 0:
        desenho_pio(numero0, valor_led, pio, sm, r, g, b);
        break;
    case 1:
        desenho_pio(numero1, valor_led, pio, sm, r, g, b);
        break;
    case 2:
        desenho_pio(numero2, valor_led, pio, sm, r, g, b);
        break;
    case 3:
        desenho_pio(numero3, valor_led, pio, sm, r, g, b);
        break;
        ;
    case 4:
        desenho_pio(numero4, valor_led, pio, sm, r, g, b);
        break;
    case 5:
        desenho_pio(numero5, valor_led, pio, sm, r, g, b);
        break;
    case 6:
        desenho_pio(numero6, valor_led, pio, sm, r, g, b);
        break;
    case 7:
        desenho_pio(numero7, valor_led, pio, sm, r, g, b);
        break;
    case 8:
        desenho_pio(numero8, valor_led, pio, sm, r, g, b);
        break;
    case 9:
        desenho_pio(numero9, valor_led, pio, sm, r, g, b);
        break;
    }
}

// função principal
int main()
{
    PIO pio = pio0;
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0, g = 0.0;

    // coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok)
        printf("clock set to %ld\n", clock_get_hz(clk_sys));

    // configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    // inicializar o botão de interrupção - GPIO5
    gpio_init(button_A);
    gpio_set_dir(button_A, GPIO_IN);
    gpio_pull_up(button_A);

    // inicializar o botão de interrupção - GPIO6
    gpio_init(button_B);
    gpio_set_dir(button_B, GPIO_IN);
    gpio_pull_up(button_B);

    // inicializar o LED vermelho - GPIO13
    gpio_init(ledA_pin);              // Inicializa o pino do LED
    gpio_set_dir(ledA_pin, GPIO_OUT); // Configura o pino como saída

    // interrupção da gpio habilitada
    gpio_set_irq_enabled_with_callback(button_A, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(button_B, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    while (true)
    {
        // Piscar o LED vermelho 5 vezes por segundo
        gpio_put(ledA_pin, 1);
        sleep_ms(100);
        gpio_put(ledA_pin, 0);
        sleep_ms(100);

        // Desenhar o número atual na matriz de LEDs
        desenharNumero(numero_atual, valor_led, pio, sm, r, g, b);

        // Verificar se o número atual está dentro do intervalo 0-9
        if (numero_atual < 0)
        {
            numero_atual = 9;
        }
        else if (numero_atual > 9)
        {
            numero_atual = 0;
        }

        printf("\nfrequência de clock %ld\r\n", clock_get_hz(clk_sys));
    }
}

// rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time > 200000) // 200 ms de debouncing
    {
        last_time = current_time;
        if (gpio == button_A) // Se for o primeiro botão
        {
            numero_atual = (numero_atual + 1) % 10; // Incrementa o número e mantém no intervalo 0-9
            printf("Botão A pressionado. Número atual: %d\n", numero_atual);
        }
        else if (gpio == button_B) // Se for o segundo botão
        {
            numero_atual = (numero_atual - 1 + 10) % 10; // Decrementa o número e mantém no intervalo 0-9
            printf("Botão B pressionado. Número atual: %d\n", numero_atual);
        }
    }
}
