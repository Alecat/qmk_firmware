# pearls_palette

![Pearl's Palette](https://ale.chenonetta.com/blog/wp-content/uploads/2023/11/IMG_5556-scaled.jpg)

*A 4x3 macro pad with rotary encoder. Per key backlighting designed for maximum candy-colour appearance.*

* Keyboard Maintainer: [Alethea Lim](https://github.com/Alecat)
* Hardware Supported: Pro Micro
* Hardware Availability: None Yet

Make example for this keyboard (after setting up your build environment):

    make pearls_palette:default

Flashing example for this keyboard:

    make pearls_palette:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
