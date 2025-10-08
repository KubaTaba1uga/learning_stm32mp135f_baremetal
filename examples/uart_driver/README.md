# Scope

Target: a memory-mapped UART peripheral (e.g., STM32MP13x USART).
Student must bring the UART from reset to reliable TX/RX using only the reference manual.

# Constraints

* No vendor HAL/CMSIS drivers; only volatile register access.
* No preconfigured clocks, pins, or UART state from U-Boot; student must reinit everything.
* C only; `-nostdlib -nostartfiles` allowed; no dynamic allocation.
* Provide a minimal linker script and startup (or use provided template).

# Functional Requirements (FR)

FR1. **Clocking & Reset**

* Enable peripheral clock in RCC.
* Assert/deassert peripheral reset if applicable.
* Derive UART kernel clock frequency; expose it via `uart_get_srcclk()`.

FR2. **GPIO & Pinmux**

* Configure TX/RX pins to correct AF, speed, type, pull.
* Verify mapping against datasheet; expose `uart_pin_init()`.

FR3. **Baud Rate**

* Compute BRR from srcclk with chosen oversampling (8/16).
* Error ≤ ±2% for common rates (9600, 115200). Provide `uart_set_baud(u32 baud)`.

FR4. **Frame Format**

* Configure word length (8/9), parity (none/even/odd), stop bits (1/2).
* API: `uart_set_format(u8 databits, uart_parity_t p, uart_stopbits_t s)`.

FR5. **Enable/Disable**

* Controlled sequence: UE=1→TE/RE enable, and clean disable path.
* API: `uart_enable(bool en)`; `uart_tx_enable(bool)`, `uart_rx_enable(bool)`.

FR6. **Transmit**

* Blocking: poll TXE; write TDR. `uart_write_byte(u8 b)`.
* Buffered non-blocking (interrupt-driven): ring buffer TX; handle TXE/TC IRQ.
* Optional: `uart_write(u8* buf, size_t n)`.

FR7. **Receive**

* Blocking: poll RXNE; read RDR. `uart_read_byte(u8* out, u32 timeout_ms)`.
* Interrupt-driven RX ring buffer with overrun protection.
* Optional: `uart_read(u8* buf, size_t n)`.

FR8. **Error Handling**

* Detect & clear ORE/FE/NE/PE.
* Report error flags via status API; counters for each error.

FR9. **Interrupts**

* Configure NVIC line; priority set; enable/disable IRQ safely.
* ISR must be non-blocking, move bytes between HW and ring buffers, clear flags.

FR10. **DMA (Stretch)**

* Optional DMA TX/RX paths with circular RX; API toggles.

FR11. **Power/Low-Power (Stretch)**

* Clean disable clocks; optional wake on RX.

# Non-Functional Requirements (NFR)

NFR1. **Deterministic timing** in blocking paths (bounded waits).
NFR2. **No data loss** under line-rate for given buffer sizes (document limits).
NFR3. **Reentrancy**: public APIs callable from task and ISR (where specified).
NFR4. **Portability**: all register defs isolated in a single header.
NFR5. **Documentation**: register map references, formulas, init order.
NFR6. **Testability**: compile-time config + self-tests.

# Deliverables (API & Files)

* `uart.h`: types, config struct, APIs:

  * `uart_init(const uart_cfg_t*)`
  * `uart_set_baud(...)`, `uart_set_format(...)`
  * `uart_enable(bool)`, `uart_tx_enable(bool)`, `uart_rx_enable(bool)`
  * `uart_write_byte(...)`, `uart_read_byte(...)`
  * `uart_write(...)`, `uart_read(...)`
  * `uart_tx_ready()`, `uart_rx_ready()`
  * `uart_get_errors(uart_err_t* out); uart_clear_errors();`
* `uart.c`: implementation (poll + IRQ paths).
* `uart_regs.h`: base address, offsets, bitfields (volatile).
* `startup.S`, `linker.ld`, `meson.build` (or Makefile).
* `uart_isr.c`: ISR (can be part of `uart.c`).
* `examples/echo_poll.c`, `examples/echo_irq.c`, `examples/throughput.c`.

# Initialization Order (must follow)

1. Enable GPIO clocks → configure TX/RX AF.
2. Enable UART kernel clock → deassert reset.
3. Disable UART (UE=0) → program CR1/CR2/CR3 (format, oversampling).
4. Program BRR (using srcclk & oversampling).
5. Clear status flags (read SR/DR per manual sequence).
6. Enable UE, then TE/RE.
7. If using IRQ: configure NVIC, enable RXNEIE/TXEIE as needed.

# Calculations Students Must Implement

* **BRR** for oversampling 16 and 8; show rounding method.
* **Baud error %**: `|actual−target|/target*100`.
* **Ring buffer sizing**: prove no overrun at baud X with ISR latency Y.

# Tests & Acceptance Criteria

T1. **Hello TX (polling)**: send “OK\r\n” reliably at 115200.
— Accept if logic analyzer shows correct frame timing ±2%.
T2. **Echo (polling)**: echoes any byte within 5 ms.
— Accept if loopback (TX→RX) passes 1000 bytes, 0 errors.
T3. **Echo (interrupt)**: RX IRQ fills ring buffer; TX IRQ drains.
— Accept if 10 KB burst at 115200 has 0 loss and ISR never spins >50 µs.
T4. **Error injection**: force framing error (wrong stop bits) → error counters increment and flags cleared without wedging RX.
T5. **Reconfigure on the fly**: switch 9600↔115200 safely (disable→reprog→enable) without lockup.
T6. **Power toggle**: disable clocks and re-enable; UART works again.

# Grading Rubric (example)

* Init & clocks: 15%
* GPIO AF & pin config: 10%
* Baud & format correctness: 15%
* TX/RX polling: 15%
* IRQ RX/TX with ring buffers: 25%
* Error handling: 10%
* Docs & tests: 10%

# Provided Scaffolding (teacher)

* Minimal linker script & startup.
* Board pin names for UART instance (TX/RX pins and AF number).
* RCC register addresses and bit fields (to reduce datasheet lookup time).
* NVIC vector number for the chosen UART.

# Forbidden Aids

* Vendor HAL/LL/CMSIS drivers.
* Copy-pasting full register defs from middleware; students must define only what they use.
* Using U-Boot/UART preinit; must cold-start peripheral.

# Hints (optional handout)

* Clear errors by reading ISR then RDR (or per manual sequence).
* TXE vs TC: TXE → TDR empty; TC → shift register empty.
* Use volatile and memory barriers around ISR-shared buffers.
* For oversampling=16: `BRR = srcclk/baud` (with rounding). For =8, follow manual’s mantissa/fraction format.
