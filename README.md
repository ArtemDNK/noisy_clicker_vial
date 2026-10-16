# Noisy Clicker — QMK + Vial

Прошивка [Vial](https://get.vial.today) (форк QMK) для самодельной 24-клавишной клавиатуры Noisy Clicker на **Waveshare RP2040-Zero**.

- Матрица 4×6, диоды ROW2COL. Строки — GP0–GP3, столбцы — GP4–GP9.
- Устройство определяется как Logitech "USB Keyboard" (VID/PID `046D:C228`).
- Хост видит только HID-клавиатуру: ни USB-диска, ни COM-порта.
- 4 слоя. Раскладка, макросы, tap-dance и комбо настраиваются в Vial на лету.

## Раскладка

Базовый слой. Под названием клавиши — её позиция в матрице `строка,столбец`.

```
┌───────┬───────┬───────┬───────┬───────┬───────┬───────┐
│  Esc  │   1   │   2   │   3   │   4   │   5   │   6   │
│  3,5  │  3,4  │  3,3  │  3,2  │  3,1  │  3,0  │  2,0  │
├───────┴───────┼───────┼───────┼───────┼───────┼───────┤
│      Tab      │   Q   │   W   │   E   │   R   │       │
│      2,5      │  2,4  │  2,3  │  2,2  │  2,1  │ Enter │
├───────────────┼───────┼───────┼───────┼───────┤  1,0  │
│     Shift     │   A   │   S   │   D   │   F   │       │
│      1,5      │  1,4  │  1,3  │  1,2  │  1,1  │       │
├───────┬───────┼───────┼───────┼───────┴───────┼───────┤
│ Ctrl  │  Win  │   C   │   V   │     Space     │  Alt  │
│  0,5  │  0,4  │  0,3  │  0,2  │      0,1      │  0,0  │
└───────┴───────┴───────┴───────┴───────────────┴───────┘
```

## Матрица

Диоды ROW2COL (анод — строка, катод — столбец).

|              | **C0** GP4 | **C1** GP5 | **C2** GP6 | **C3** GP7 | **C4** GP8 | **C5** GP9 |
|--------------|:----------:|:----------:|:----------:|:----------:|:----------:|:----------:|
| **R0** GP0   | Alt        | Space      | V          | C          | Win        | Ctrl       |
| **R1** GP1   | Enter      | F          | D          | S          | A          | Shift      |
| **R2** GP2   | 6          | R          | E          | W          | Q          | Tab        |
| **R3** GP3   | 5          | 4          | 3          | 2          | 1          | **Esc**    |

Esc (R3/C5) — клавиша Bootmagic; Esc + Enter — разблокировка Vial.

## Прошивка

Готовый файл: [`firmware/noisy_clicker_vial.uf2`](firmware/noisy_clicker_vial.uf2).

1. Переведи плату в загрузчик **одним из способов**:
   - зажми **ESC** и подключи кабель (Bootmagic);
   - дважды быстро нажми **RESET** на плате;
   - зажми **BOOT**, подключи кабель (или нажми RESET) и отпусти.
2. Появится диск **RPI-RP2** — скопируй на него `.uf2`.
3. Плата перезагрузится уже как клавиатура.

Вход в загрузчик через ESC **не стирает** настройки Vial: в `noisy_clicker.c` переопределён `bootmagic_scan`.

## Настройка

- Приложение: [get.vial.today](https://get.vial.today) или [vial.rocks](https://vial.rocks) (Chrome/Edge, нужен WebHID).
- Разблокировка Vial (для Matrix tester и т.п.): зажать **ESC + ENTER**.

## Сборка из исходников

```bash
git clone --depth 1 https://github.com/vial-kb/vial-qmk.git
cd vial-qmk
git submodule update --init --depth 1 --recursive

# сюда — содержимое этого репозитория
cp -r ../noisy_clicker_vial/keyboards/handwired/noisy_clicker keyboards/handwired/

# тулчейн (Ubuntu/Debian)
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi binutils-arm-none-eabi
python3 -m venv .venv && . .venv/bin/activate
pip install qmk -r requirements.txt

make handwired/noisy_clicker:vial
# -> handwired_noisy_clicker_vial.uf2
```

Готовая прошивка в `firmware/` собрана из vial-qmk `dd43959a`.

## Структура

```
keyboards/handwired/noisy_clicker/
├── keyboard.json          # матрица, пины, USB ID, раскладка, Bootmagic на ESC
├── config.h               # двойной RESET -> загрузчик
├── noisy_clicker.c        # Bootmagic без стирания EEPROM
└── keymaps/
    ├── default/keymap.c
    └── vial/
        ├── keymap.c       # базовый слой + 3 пустых
        ├── config.h       # VIAL_KEYBOARD_UID, комбо разблокировки
        ├── rules.mk
        └── vial.json      # раскладка для GUI Vial
```
