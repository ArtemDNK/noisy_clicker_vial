# Noisy Clicker — QMK + Vial

Прошивка [Vial](https://get.vial.today) (форк QMK) для самодельной 24-клавишной клавиатуры Noisy Clicker на **Waveshare RP2040-Zero**.

- Матрица 4×6, диоды ROW2COL. Строки — GP0–GP3, столбцы — GP4–GP9.
- Устройство определяется как Logitech "USB Keyboard" (VID/PID `046D:C228`).
- Хост видит только HID-клавиатуру: ни USB-диска, ни COM-порта.
- 4 слоя. Раскладка, макросы, tap-dance и комбо настраиваются в Vial на лету.

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

## Возврат на CircuitPython / Pog

Через BOOT залить `.uf2` CircuitPython 9.x для Waveshare RP2040-Zero и скопировать файлы Pog/KMK обратно.
