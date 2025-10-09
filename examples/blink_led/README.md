## ⚙️ **Phase 1 — Core Hardware Mastery**

### **1. GPIO Register Mirror**

Write your own `struct gpio_regs` mapping the full GPIO register set (MODER → AFRH).
Then:

1. Implement a `GPIO(port)` macro returning `(volatile struct gpio_regs*)`.
2. Use it to read `GPIOH->MODER` and print it via UART.
3. Compare against the value in the reference manual’s *reset state table*.

> 💡 *Goal:* confirm you understand register spacing and the AHB4 mapping.

---

### **2. Safe Bit Manipulation**

Implement `gpio_write_bits(GPIO_TypeDef* port, uint32_t mask, bool state)`
which writes *only* those bits using BSRR.
Then test by writing a pattern to PH0–PH3 and reading back ODR.

> 💡 *Goal:* master atomic set/reset and confirm no unintended bits flip.

---

### **3. Glitch-Free Output Reconfiguration**

Code a routine `gpio_safe_output_init(GPIOH,6)` that:

1. Enables clock.
2. Sets the pin’s **initial level** before changing its mode.
3. Configures OTYPER, OSPEEDR, and MODER last.

Use a scope or LED to verify no short pulse appears during configuration.

> 💡 *Goal:* understand how write order prevents visible glitches.

---

### **4. Input Voltage Characterization**

Program PH7 as input with:

* no pull,
* pull-up,
* pull-down.

Measure voltage with a multimeter each time and record approximate values.
Write a short C function that prints the PUPDR bits and explains expected logic level.

> 💡 *Goal:* learn how internal pull resistors bias floating inputs.

---

### **5. Cross-Bank Toggle Benchmark**

Toggle PH6 using your driver; then switch to PA0 and repeat.
Measure frequency on both pins.
Explain differences in delay considering AHB4 bus arbitration and address region.

> 💡 *Goal:* connect register writes to physical bus timing.

---

## 🔌 **Phase 2 — Functional Abstraction**

### **6. Generic Pin Object**

Define:

```c
typedef struct {
  volatile struct gpio_regs *port;
  uint8_t pin;
} gpio_t;
```

and implement:

```c
void gpio_config(gpio_t p, gpio_mode_t m, gpio_pull_t pull);
void gpio_write(gpio_t p, bool v);
bool gpio_read(gpio_t p);
```

Make sure all work across any bank A–K.

> 💡 *Goal:* encapsulate per-pin logic without sacrificing register transparency.

---

### **7. Alternate Function Routing**

Write `gpio_set_af(gpio_t p, uint8_t af)`.
Then:

* Route PH6 to its alternate function (check datasheet table).
* Dump AFRH register before/after.
* Decode the 4-bit field manually to confirm correctness.

> 💡 *Goal:* internalize how pin multiplexing works.

---

### **8. Dynamic LED Pattern**

Using your generic driver, blink four LEDs (PH6, PH7, PH8, PH9) in a rotating pattern.
All configuration must go through your driver API.
Optional: drive pattern from a lookup table in flash.

> 💡 *Goal:* apply your abstraction repeatedly, confirm consistency across pins.

---

## ⚡ **Phase 3 — System Understanding**

### **9. Fault Experiment**

Disable the GPIOH clock in RCC, then attempt to write to GPIOH_BSRR.
Catch and print any fault via your exception handler (Data Abort).
Record what happens to PC and fault status registers.

> 💡 *Goal:* observe how bus faults signal unclocked peripheral access.

---

### **10. External Event Trigger**

Configure one pin as input (button) and one as output (LED).
Use EXTI to toggle the LED when the button changes state.
No STM32 HAL — only direct SYSCFG/EXTI/NVIC register writes.

> 💡 *Goal:* see complete signal path: pin → EXTI → NVIC → ISR → GPIO.*

---

### **11. Write Integrity Check**

Implement a debug routine:

```c
void gpio_verify_write(gpio_t p, bool level);
```

that writes a value, reads IDR back, and reports mismatch.
Use it to test timing hazards at different `-O` levels and add a data-memory barrier if needed.

> 💡 *Goal:* learn when CPU reordering breaks MMIO assumptions.*

---

### **12. Self-Diagnostic Mode**

Create a “GPIO self-test” that:

* Iterates over all valid pins in one bank,
* Toggles each one,
* Verifies read-back logic,
* Reports any stuck or invalid bits via UART.

> 💡 *Goal:* end-to-end understanding: configuration, control, read-back, reporting.*
