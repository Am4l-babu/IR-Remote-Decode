# IR Remote Decoder

An ESP8266-powered IR remote decoder with a live web dashboard. Point any remote at a TSOP1738 sensor and watch the protocol, hex code, and bit count decode in real time in your browser — no serial monitor needed.

## Try it without any hardware

**[Launch the Interactive Simulator &#x2192;](https://htmlpreview.github.io/?https://github.com/Am4l-babu/IR-Remote-Decode/blob/master/docs/simulator.html)**

Click buttons on a virtual remote to fire simulated IR frames at a virtual sensor. Watch the decoder panel, pulse waveform, save list, and signal log react exactly like the real firmware — all running client-side in your browser, no ESP8266 required.

## Features

- **Live IR decoding** — TSOP1738 sensor on GPIO2 (D4) decodes signals via [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266), streamed to the browser over WebSockets
- **Save & manage buttons** — name and persist decoded codes to LittleFS, with delete/clear support
- **Signal log** — rolling history of every decoded frame
- **Remote Learning Mode** (`/learn`) — upload a photo of a remote, map its buttons on an edge-detected blueprint, and walk through 3x-verified IR capture for every button, then export to CSV/JSON

## Hardware

| Part | Notes |
|---|---|
| ESP8266 dev board | NodeMCU / Wemos D1 mini |
| TSOP1738 (38 kHz) | IR receiver module |
| 3x jumper wires | OUT, GND, VCC |

Wiring: `TSOP1738 OUT → D4 (GPIO2)`, `GND → GND`, `VCC → 3V3`. See the wiring diagram in the [simulator](https://htmlpreview.github.io/?https://github.com/Am4l-babu/IR-Remote-Decode/blob/master/docs/simulator.html) for a visual reference.

## Building & flashing

This project uses [PlatformIO](https://platformio.org/).

```bash
pio run -t upload      # build + flash
pio run -t uploadfs    # upload LittleFS filesystem (for saved buttons)
pio device monitor      # serial monitor at 115200 baud
```

On boot the device connects to Wi-Fi (or falls back to AP mode `IR_Decoder` / `12345678`) and prints its IP address to serial. Open that address in a browser to reach the dashboard, or `/learn` for Remote Learning Mode.

> **Note:** `src/main.cpp` currently has Wi-Fi credentials hardcoded at the top of the file. Move these to a `secrets.h` (gitignored) or build flags before pushing your own changes to a public fork.

## Project structure

```
src/main.cpp          # firmware: IR decode loop, web server, WebSocket, live dashboard HTML
include/learn_page.h  # Remote Learning Mode page (upload, map, learn, export)
docs/simulator.html   # standalone browser simulator — no hardware required
```
