#include <stdint.h>

/* ===================== BASE ADDRESSES ===================== */
#define PERIPH_BASE        0x40000000UL

/* AHB2 (GPIO) */
#define AHB2_OFFSET        0x08000000UL
#define AHB2_BASE          (PERIPH_BASE + AHB2_OFFSET)

/* AHB1 (RCC) */
#define AHB1_OFFSET        0x00020000UL
#define AHB1_BASE          (PERIPH_BASE + AHB1_OFFSET)

/* ===================== GPIOA ===================== */
#define GPIOA_BASE         (AHB2_BASE + 0x0000UL)

#define GPIOA_MODER        (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL         (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

/* ===================== RCC ===================== */
#define RCC_BASE           (AHB1_BASE + 0x1000UL)

#define RCC_AHB2ENR        (*(volatile uint32_t *)(RCC_BASE + 0x4C))
#define RCC_APB1ENR1       (*(volatile uint32_t *)(RCC_BASE + 0x58))

#define RCC_AHB2ENR_GPIOAEN    (1U << 0)
#define RCC_APB1ENR1_USART2EN  (1U << 17)

/* ===================== USART2 ===================== */
#define USART2_BASE        (PERIPH_BASE + 0x4400UL)

#define USART2_CR1         (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_BRR         (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_ISR         (*(volatile uint32_t *)(USART2_BASE + 0x1C))
#define USART2_RDR         (*(volatile uint32_t *)(USART2_BASE + 0x24))
#define USART2_TDR         (*(volatile uint32_t *)(USART2_BASE + 0x28))

/* USART bits */
#define USART_CR1_UE       (1U << 0)
#define USART_CR1_RE       (1U << 2)
#define USART_CR1_TE       (1U << 3)

#define USART_ISR_RXNE     (1U << 5)
#define USART_ISR_TXE      (1U << 7)

/* ===================== CLOCK / BAUD ===================== */
#define PCLK1              16000000U   // APB1 clock
#define UART_BAUDRATE      115200U

/* ===================== FUNCTION PROTOTYPES ===================== */
void uart2_init(void);
void uart2_write(char ch);
char uart2_read(void);

/* ===================== MAIN ===================== */
int main(void)
{
    uart2_init();

    while (1)
    {
        char c = uart2_read();   // wait for received char
        uart2_write(c);          // echo it back
    }
}

/* ===================== UART INIT ===================== */
void uart2_init(void)
{
    /* 1. Enable GPIOA clock */
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    /* 2. PA2 (TX) & PA3 (RX) → Alternate Function */
    GPIOA_MODER &= ~((3U << 4) | (3U << 6));
    GPIOA_MODER |=  ((2U << 4) | (2U << 6));

    /* 3. AF7 for PA2 (TX) and PA3 (RX) */
    GPIOA_AFRL &= ~((0xFU << 8) | (0xFU << 12));
    GPIOA_AFRL |=  ((7U  << 8) | (7U  << 12));

    /* 4. Enable USART2 clock */
    RCC_APB1ENR1 |= RCC_APB1ENR1_USART2EN;

    /* 5. Disable USART before config */
    USART2_CR1 &= ~USART_CR1_UE;

    /* 6. Set baud rate */
    USART2_BRR = (PCLK1 + UART_BAUDRATE / 2U) / UART_BAUDRATE;

    /* 7. Enable TX and RX */
    USART2_CR1 |= USART_CR1_TE | USART_CR1_RE;

    /* 8. Enable USART */
    USART2_CR1 |= USART_CR1_UE;
}

/* ===================== UART WRITE ===================== */
void uart2_write(char ch)
{
    while (!(USART2_ISR & USART_ISR_TXE))
    {
        /* wait */
    }
    USART2_TDR = (uint8_t)ch;
}

/* ===================== UART READ ===================== */
char uart2_read(void)
{
    while (!(USART2_ISR & USART_ISR_RXNE))
    {
        /* wait */
    }
    return (char)USART2_RDR;
}
