# Blackbox flight data recorder tools

![Rendered flight log frame](screenshots/blackbox-screenshot-1.jpg)

## Introduction

These tools allow you to convert flight data logs recorded by INAV's Blackbox feature into CSV files (comma-separated values) for analysis, or into a series of PNG files which you could turn into a video.

You can download the latest executable versions of `blackbox_decode` x86_64 on Linux, MacOS or Windows, aarch64 on Linux and MacOS, riscv64 on Linux from the "releases" tab. If you're running a different OS/Arch, or you need `blackbox_render`, you can build the tools from source (instructions are further down this page).

## Using the blackbox_decode tool

This is a *command line* tool. It should be run from a "shell" (e.g. "bash", "zsh", "cmd", "powershell" etc.)

In order to converts a flight log binary ".TXT" file into CSV format, a typical usage (from the command line) would be like:

```bash
blackbox_decode LOG00001.TXT
```

That'll decode the log to `LOG00001.01.csv` and print out some statistics about the log. If you're using Windows, you can drag and drop your log files onto `blackbox_decode` and they'll all be decoded, but this prevents using some of the more useful options listed below. Please note that you shouldn't discard the original ".TXT" file, because it is required as input for other tools like the PNG image renderer.

If your log file contains GPS data then a ".gpx" file will also be produced. This file can be opened in Google Earth or some other GPS mapping software for analysis. You can also include more comprehensive GPS data in the log file, for example:

* Add flight date / time to the CSV
* Include GPS information in the CSV

```
blackbox_decode --datetime --merge-gps LOG00042.TXT
```

Use the `--help` option to show more details and all the options, for example:

```text
INAV Blackbox flight log decoder by Nicholas Sherlock (v7.0.1 123714c, Jan 19 2024 21:36:10)

Usage:
     blackbox_decode [options] <input logs>

Options:
   --help                   This page
   --version                Show version, exit
   --index <num>            Choose the log from the file that should be decoded (or omit to decode all)
   --limits                 Print the limits and range of each field
   --stdout                 Write log to stdout instead of to a file
   --datetime               Add a dateTime column with UTC date time
   --unit-amperage <unit>   Current meter unit (raw|mA|A), default is A (amps)
   --unit-flags <unit>      State flags unit (raw|flags), default is flags
   --unit-frame-time <unit> Frame timestamp unit (us|s), default is us (microseconds)
   --unit-height <unit>     Height unit (m|cm|ft), default is cm (centimeters)
   --unit-rotation <unit>   Rate of rotation unit (raw|deg/s|rad/s), default is raw
   --unit-acceleration <u>  Acceleration unit (raw|g|m/s2), default is raw
   --unit-gps-speed <unit>  GPS speed unit (mps|kph|mph), default is mps (meters per second)
   --unit-vbat <unit>       Vbat unit (raw|mV|V), default is V (volts)
   --merge-gps              Merge GPS data into the main CSV log file instead of writing it separately
   --simulate-current-meter Simulate a virtual current meter using throttle data
   --sim-current-meter-scale   Override the FC's settings for the current meter simulation
   --sim-current-meter-offset  Override the FC's settings for the current meter simulation
   --simulate-imu           Compute tilt/roll/heading fields from gyro/accel/mag data
   --imu-ignore-mag         Ignore magnetometer data when computing heading
   --declination <val>      Set magnetic declination in degrees.minutes format (e.g. -12.58 for New York)
   --declination-dec <val>  Set magnetic declination in decimal degrees (e.g. -12.97 for New York)
   --debug                  Show extra debugging information
   --raw                    Don't apply predictions to fields (show raw field deltas)
   --apply-gframe <flag>    How to apply intermediate G-frames (0=ignore (default), 1=when not "late", 2=always (legacy, may cause backwards timestamps))
```

`blackbox_decode` will display some statistics about the log. It will warn you if it's missing essential metadata that effectively renders the log useless for analysis.

```
$ blackbox_decode corrupt-header.TXT
Decoding log 'corrupt-header.TXT' to 'corrupt-header.01.csv'...

Log 1 of 1, start 02:57.817, end 09:45.237, duration 06:47.419

Statistics
Looptime           1890 avg          460.0 std dev (24.3%)
I frames   12634  113.7 bytes avg  1437103 bytes total
P frames  169062   69.0 bytes avg 11660607 bytes total
H frames     100   10.0 bytes avg     1000 bytes total
G frames    2119   24.1 bytes avg    50991 bytes total
E frames       1    6.0 bytes avg        6 bytes total
S frames       3   45.3 bytes avg      136 bytes total
Frames    181696   72.1 bytes avg 13097710 bytes total
Data rate  445Hz  36121 bytes/s     361300 baud

3438 frames failed to decode, rendering 20444 loop iterations unreadable. 222863 iterations are missing in total (224438ms, 55.09%)

WARNING: Missing expected metadata - check for log corruption
	Warning: No VBAT reference
	Error: No Firmware type metadata
	Error: No Firmware revision metadata
	Error: No P Interval
	Error: No Acc.1G metadata

Generated by INAV blackbox_decode 7.0.1 123714c
```

Please note that `blackbox_decode` is not intended to insert "derived values" in the output CSV files. If this is desired, it can easily be done, perhaps as part of a pipeline, outside of `blacbox_decode`.

## Using the blackbox_render tool

This tool converts a flight log binary ".TXT" file into a series of transparent PNG images that you could overlay onto your flight video using a video editor (like [DaVinci Resolve][] ). Typical usage (from the command line) would be like:

```bash
blackbox_render LOG00001.TXT
```

This will create PNG files at 30 fps into a new directory called `LOG00001.01` next to the log file.

Use the `--help` option to show more details:

```text
Blackbox flight log renderer by Nicholas Sherlock (v7.0.1 for INAV, Jan 19 2024 21:36:12)

Usage:
     blackbox_render [options] <logfilename.txt>

Options:
   --help                 This page
   --index <num>          Choose which log from the file should be rendered
   --width <px>           Choose the width of the image (default 1920)
   --height <px>          Choose the height of the image (default 1080)
   --fps                  FPS of the resulting video (default 30)
   --mode <mode>          Stick Mode (1-4)
   --threads              Number of threads to use to render frames (default 3)
   --prefix <filename>    Set the prefix of the output frame filenames
   --start <x:xx>         Begin the log at this time offset (default 0:00)
   --end <x:xx>           End the log at this time offset
   --[no-]draw-pid-table  Show table with PIDs and gyros (default on)
   --[no-]draw-craft      Show craft drawing (default on)
   --[no-]draw-sticks     Show RC command sticks (default on)
   --[no-]draw-time       Show frame number and time in bottom right (default on)
   --[no-]plot-motor      Draw motors on the upper graph (default on)
   --[no-]plot-pid        Draw PIDs on the lower graph (default off)
   --[no-]plot-gyro       Draw gyroscopes on the lower graph (default on)
   --smoothing-pid <n>    Smoothing window for the PIDs (default 4)
   --smoothing-gyro <n>   Smoothing window for the gyroscopes (default 2)
   --smoothing-motor <n>  Smoothing window for the motors (default 2)
   --unit-gyro <raw|degree>  Unit for the gyro values in the table (default raw)
   --prop-style <name>    Style of propeller display (pie/blades, default pie)
   --gapless              Fill in gaps in the log with straight lines
   --raw-amperage         Print the current sensor ADC value along with computed amperage
```

(At least on Windows) if you just want to render a log file using the defaults, you can drag and drop a log onto the blackbox_render program and it'll start generating the PNGs immediately.

[DaVinci Resolve]: https://www.blackmagicdesign.com/products/davinciresolve

### Assembling video with DaVinci Resolve

![DaVinci Resolve screenshot](screenshots/davinci-resolve-screenshot.jpg)

[DaVinci Resolve][] is one free option for turning your PNGs into a video that is synced with your flight video.

In Resolve, create a new project. On the Media tab, find your flight video and drag it from the top pane to the bottom one to add it to your media library. When prompted, choose the option to change your framerate/resolution settings to match the video you added. Now add the PNG series that you rendered with `blackbox_render` (it'll be represented as a single file). If the PNGs don't appear in the media library, try right clicking on the folder that contains them and
selecting "Refresh".

Now over on the Edit tab, click File -> New Timeline and click Ok. At the top left, switch over to the Media Pool. Drag and drop your flight video onto the timeline, then drag and drop the Blackbox stream onto the video track above it. You'll need to play around with the alignment between the two tracks to sync things up (I usually sync up the audio from the initial throttle-up with the throttle-up shown on the motor graph).

If your Blackbox PNGs were rendered using the default settings (30 FPS) and your flight video is 60 FPS, you'll need to right-click on the Blackbox stream and click "change clip speed". Enter 30 FPS since this is the FPS that you rendered the Blackbox PNGs at.

Save your viewers' ears by dragging the midpoint of the audio track downwards to reduce its volume, or replace the audio with your own music track!

Now on the Deliver tab, choose something like the "video sharing export" Easy Setup preset. On the left pane, choose an output folder for the "render to:" setting. Then click the "add job to render queue" button on the left. Now click the "start render" button on the right to begin rendering the output.

## Building tools

If you just want to download some prebuilt versions of `blackbox_decode` head to the "releases" tab on the GitHub page. However, if you want to build your own binaries, or you're an unsupported platform where we haven't provided binaries, please read on.

The `blackbox_decode` tool for turning binary flight logs into CSV doesn't depend on any libraries, so can be built by running `make obj/blackbox_decode`. You can add the resulting `obj/blackbox_decode` program to your system path to make it easier to run.

The `blackbox_render` tool renders a binary flight log into a series of PNG images which you can overlay on your flight video. Please read the section below that most closely matches your operating system for instructions on getting the `libcairo` library required to build the `blackbox_render` tool.

### Version Information

The version is set in `src/version.h`. If you wish, you may override this with the environment variable `BLACKBOX_VERSION` (e.g. `make BLACKBOX_VERSION=x.y.z-local`).

The Makefile attempts to evince an environment variable `BLACKBOX_COMMIT`; this is set, the git commit id will also be shown as part of the version. You may override this:

```
$ blackbox_decode --version
7.0.1 INAV 123714c

$ BLACKBOX_COMMIT=uncommitted make
$ blackbox_decode --version
7.0.1 INAV uncommitted
```

#### Linux

You will need `gcc` (or `clang`), `make` and (for `blackbox_render`), `libcairo2` (development files).

For Debian (Ubuntu etc.), you can get the tools required for building by entering these commands into the terminal:

```bash
sudo apt-get update
sudo apt-get install make gcc libcairo2-dev
```
Otherwise, search the distro package manager and install equivalents.

Then, build blackbox_render by running `make obj/blackbox_render` (or build both tools by just running `make`).

#### FreeBSD

You will need `clang` (`cc`), `gmake` and `libcairo2`. Use `pkg` to install.

Then:

```
gmake
```

#### MacOSX

Note: These instructions need validating.

The easiest way to build is to install the [Xcode development tool][], then install an environment like [Homebrew][] or [MacPorts][] onto your system.

From MacPorts / Homebrew you need to install `cairo`.

Then you can run `make` to build.

MacOS `blacbox_decode` can also be cross-compiled on Linux using the supplied `Makefile`.

#### Windows

The tools can be cross-compiled on Linux (`blackbox_decode.exe` using the supplied `Makefile`, or built natively in MSys2 (Win32 and Win64), using the `Makefile`. You will need to install the required tools and libraries (`pacman -S  make gcc cairo`).

Historically, the tools could be built with Visual Studio Express 2013; open up the solution in the `visual-studio/` folder. You'll need to include the .DLL files from `lib/win32` in the same directory as your built executable. This is no longer supported and is unlikely to work.

#### Install from build

The `Makefile` includes an `install` stanza. This may be augmented by `prefix` to specify the installation directory prefix, which otherwise defaults to `/usr/local`.

For example, with `prefix` set to  `$HOME/.local`:

```
# Note "/bin" is appended by the Makefile
make install prefix=~/.local
```

Results in:
```
$HOME/.local/bin/blackbox_decode
$HOME/.local/bin/blackbox_render
```

## License

This project is licensed under GPLv3.

Both binary and source builds include IMU code from Baseflight https://github.com/multiwii/baseflight (GPLv3)
