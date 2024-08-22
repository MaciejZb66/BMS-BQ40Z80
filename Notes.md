## Structure

* `main` testspace
* `bq40z80` Work directly with the board, basic read/write commands
* `bq40z80_parser` splitting read bytes from register to bits (flags)
* `bq40z80_validator` helper commands to check anything from the received flags
* `bq40z80_action` Various commands for the board
* `i2c_helper` Common Commands
* `bq40z80_mfa` Manufacturer Access address defines
* `bq40z80_sbs` SMBus commands defines
* `bq40z80_registers` some structs (not yet used)

## Future notes 
bat status and bat mode possible little-big endian error

## Idiot notes
Open preview of markdown file by using ctrl + k and v 