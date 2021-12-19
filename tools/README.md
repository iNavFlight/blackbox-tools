# Consistency helper

## Function

The script `rcmodes.rb` parses inav firmware header files and builds text strings from `enum` in oder to keep the blackbox log text fields consistent with the firmware values.

If this tool is used at each release, this has the side effect that the decoder should not fall off the end of such text constant arrays when a new enum is added to the firmware.

## Usage

```
tools/rcmodes.rb <path-to-blackbox_fielddefs.c> <path-to-inav-source-tree>
```

The outout is written to standard output and should be manually merged with `src/blackbox_fielddefs.c`

## Example

```
./tools/rcmodes.rb src/blackbox_fielddefs.c  ~/Projects/fc/inav | tee /tmp/newdefs.c
# manually update blackbox_fielddefs.c  from /tmp/newdefs.c
```

## Dependencies

`src/blackbox_fielddefs.c` contains specially formatted comments such as:

```
// INAV HEADER: src/main/fc/rc_modes.h : boxId_e
```
i.e. a `// INAV HEADER:` followed by the inav source header and the enum name.

Please preserve these comments, even if you don't use the script. They save much grepping.
