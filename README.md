# GodMode9 Link
A simple launcher to run GodMode9 from your homemenu

This is not GodMode9 itself, but rather a simple link (CIA) to it on the homemenu. Keep in mind this and especially the required inofficial boot9strap release is experimental.

## Requirements

GodMode9 Link checks for the GodMode9 FIRM payload in the following directories:
* sdcard:/luma/payloads/godmode9.firm
* sdcard:/luma/payloads/x_godmode9.firm
* sdcard:/luma/payloads/y_godmode9.firm
* sdcard:/gm9/godmode9.firm

For this to work you also need an inofficial release of boot9strap installed, get it [from here](https://github.com/d0k3/boot9strap/releases/tag/1.2%2Bbootonce).

## Developers / Customization

If you want to customize this for your own needs, edit the files in `/meta`, `Makefile` and `include/payload.h`. Compiling requires devKitARM and libctru.

## License

You may use this under the terms of the GNU General Public License GPL v2 or under the terms of any later revisions of the GPL. Refer to the provided `LICENSE.txt` file for further information.
