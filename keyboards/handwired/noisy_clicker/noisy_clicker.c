// Noisy Clicker (RP2040-Zero)
#include "quantum.h"

// ESC зажат при подключении -> UF2-загрузчик.
// В отличие от стандартного Bootmagic, EEPROM (настройки Vial) НЕ стирается.
void bootmagic_scan(void) {
    matrix_scan();
    wait_ms(DEBOUNCE * 2);
    matrix_scan();

    if (matrix_get_row(BOOTMAGIC_ROW) & (1 << BOOTMAGIC_COLUMN)) {
        bootloader_jump();
    }
}
