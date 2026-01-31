# STM32 USART2 Bare-Metal TX/RX (Polling)

This project demonstrates a **bare-metal implementation of USART2 transmission and reception (TX/RX)** on an STM32 microcontroller using **direct register access**, without HAL or CMSIS drivers.

The code is written for learning purposes and focuses on understanding:
- Memory-mapped registers
- `volatile` and lvalues
- GPIO alternate functions
- USART configuration
- Polling-based UART communication

---

##  Features

- USART2 **TX and RX** using polling
- Echoes received characters back to the sender
- Uses **PA2 (TX)** and **PA3 (RX)**
- No HAL, no CMSIS abstractions
- Clean register-level configuration
- Suitable for learning and debugging fundamentals

---

##  Tools & Environment

- **IDE:** STM32CubeIDE  
- **Language:** C  
- **Compiler:** ARM GCC (via CubeIDE)  
- **Clock:** APB1 = 16 MHz  
- **Baud rate:** 115200  

---

##  Pin Configuration

| Signal | Pin |
|------|-----|
| USART2_TX | PA2 |
| USART2_RX | PA3 |
| GND | GND |

---

##  How It Works (High Level)

1. Enable GPIOA and USART2 clocks
2. Configure PA2 and PA3 as Alternate Function (AF7)
3. Disable USART before configuration
4. Configure baud rate
5. Enable transmitter (TE) and receiver (RE)
6. Enable USART
7. Poll TXE to transmit data
8. Poll RXNE to receive data

---

## Usage

1. Open the project in **STM32CubeIDE**
2. Build the project
3. Flash to the target board
4. Open a serial terminal:
   - Baud rate: `115200`
   - Data bits: `8`
   - Parity: `None`
   - Stop bits: `1`
5. Type any character — it will be **echoed back**

---

##  Project Structure



##  Ignored Files

The following are intentionally excluded via `.gitignore`:
- Build directories (`Debug/`, `Release/`)
- Compiled binaries (`.elf`, `.hex`, `.bin`)
- IDE-specific files
- OS-generated files

This keeps the repository clean and portable.

---

##  Learning Goals

This project is intended to help understand:
- How peripherals are controlled at the register level
- Why `volatile` is required for hardware registers
- The difference between registers and values
- Polling vs interrupt-based communication

---

##  Possible Extensions

- Non-blocking RX
- Interrupt-based USART
- DMA-based RX/TX
- String transmission functions
- Migration to CMSIS or HAL for comparison

---

##  License

This project is provided for educational purposes.  
Feel free to use, modify, and share.

---

##  Author

Emmanuel Odongo
