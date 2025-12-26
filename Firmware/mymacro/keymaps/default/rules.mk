# Der Chip
MCU = RP2040
BOOTLOADER = rp2040

# Features aktivieren (Das ist das Wichtigste!)
ENCODER_ENABLE = yes       # Damit der Drehregler funktioniert
RGBLIGHT_ENABLE = yes      # Damit die LEDs und Animationen gehen
WS2812_DRIVER = vendor     # Der richtige LED-Treiber für den RP2040

# Optional, aber oft nützlich:
MOUSEKEY_ENABLE = yes      # Falls du mal Mausbewegungen auf Tasten legen willst
EXTRAKEY_ENABLE = yes      # Für Audio-Kontrolle (Vol+, Vol- etc.)
CONSOLE_ENABLE = no        # Spart Platz und macht es oft stabiler (auf 'yes' nur zum Debuggen)