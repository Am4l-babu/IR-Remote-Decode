<p align="center">
  <img src="https://img.shields.io/badge/ESP8266-NodeMCU-blue?style=for-the-badge&logo=espressif&logoColor=white" />
  <img src="https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/PlatformIO-Build-orange?style=for-the-badge&logo=platformio&logoColor=white" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" />
</p>

<h1 align="center">📡 IR Remote Decoder & Learning System</h1>

<p align="center">
  <strong>A full-featured IR remote decoder with a beautiful web dashboard, remote photo mapping, edge-detection blueprint rendering, 3× verified signal learning, and CSV/JSON export — all running on an ESP8266.</strong>
</p>

<p align="center">
  <a href="#-features">Features</a> •
  <a href="#-hardware">Hardware</a> •
  <a href="#-getting-started">Getting Started</a> •
  <a href="#-web-interface">Web Interface</a> •
  <a href="#-learning-mode">Learning Mode</a> •
  <a href="#-api-reference">API</a> •
  <a href="#-project-structure">Structure</a>
</p>

---

## ✨ Features

### 🔴 Live IR Decoder Dashboard
- **Real-time decoding** of any IR remote signal via WebSocket
- Displays protocol, hex code, and bit count instantly
- Beautiful animated signal log with timestamps
- Save decoded buttons with custom names
- Persistent storage using LittleFS on the ESP8266
- Delete individual buttons or clear all

### 🎯 Remote Learning Mode *(New!)*
- **Upload a photo** of your physical remote (drag & drop or browse)
- **Edge-detection blueprint** — Sobel edge detection transforms your photo into a futuristic cyan-on-dark schematic
- **Interactive button mapping** — Click directly on the remote image to mark each button's position
- **3× verification learning** — Each button requires 3 identical IR readings to confirm the signal, ensuring accuracy
- **Skip & retry** — Skip buttons you don't need, retry mismatched readings
- **Progress tracking** — Animated progress bar, per-button status, and visual markers on the remote image
- **Export results** — Download verified signals as **CSV** or **JSON** spreadsheets

### 🌐 Connectivity
- **Station mode** — Connects to your home WiFi
- **AP fallback** — Creates its own hotspot (`IR_Decoder` / `12345678`) if WiFi fails
- Works on any device with a browser — phone, tablet, or PC

---

## 🔧 Hardware

### Components Required

| Component | Description | Pin |
|-----------|-------------|-----|
| **ESP8266** | NodeMCU v2 (ESP-12E) | — |
| **TSOP IR Receiver** | TSOP1738 / VS1838B | GPIO2 (D4) |
| **USB Cable** | Micro USB for power & programming | — |

### Wiring Diagram

```
TSOP IR Sensor          ESP8266 (NodeMCU)
┌──────────┐            ┌──────────────┐
│          │            │              │
│  VCC  ───┼────────────┤  3.3V        │
│          │            │              │
│  GND  ───┼────────────┤  GND         │
│          │            │              │
│  OUT  ───┼────────────┤  D4 (GPIO2)  │
│          │            │              │
└──────────┘            └──────────────┘
```

> **Note:** The TSOP sensor's pinout varies by model. Verify your sensor's datasheet before wiring.

---

## 🚀 Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) (VS Code extension or CLI)
- USB driver for your ESP8266 board (CH340 / CP2102)

### 1. Clone the Repository

```bash
git clone https://github.com/Am4l-babu/IR-Remote-Decode.git
cd IR-Remote-Decode
```

### 2. Configure WiFi Credentials

Edit `src/main.cpp` and update these lines with your network details:

```cpp
const char* WIFI_SSID     = "YourWiFiName";
const char* WIFI_PASSWORD = "YourWiFiPassword";
```

### 3. Build & Upload

```bash
# Using PlatformIO CLI
pio run --target upload

# Or use the PlatformIO toolbar in VS Code:
#   Click ➤ (Upload) button
```

### 4. Find the IP Address

Open the Serial Monitor at **115200 baud**:

```
=================================
  IR Remote Decoder - ESP8266
  Sensor: GPIO2 (D4)
=================================

[WiFi] Connected!
[WiFi] IP Address: 192.168.1.42

>>> Open http://192.168.1.42 in your browser <<<
```

### 5. Open the Dashboard

Navigate to the IP address shown in Serial Monitor. That's it! 🎉

---

## 🖥 Web Interface

### Main Dashboard (`/`)

The main page provides a live IR signal decoder with a dark, modern UI:

| Section | Description |
|---------|-------------|
| **Live Decoder** | Shows decoded protocol, hex code, and bit count in real-time with glow animations |
| **Save Button** | Name and save any decoded signal for future reference |
| **Saved Buttons** | View all saved buttons with protocol details; delete individually or clear all |
| **Signal Log** | Chronological log of all received IR signals with timestamps |
| **Learning Mode Link** | Quick navigation to the Remote Learning Mode |

### Key Interactions
- **WebSocket connection** — Status dot turns green when connected; auto-reconnects on disconnect
- **Signal animation** — Display pulses with a red glow each time a signal is received
- **Toast notifications** — Success/error messages slide up from the bottom

---

## 🎯 Learning Mode

Access via the **"🎯 Remote Learning Mode"** button on the main dashboard, or navigate to `/learn`.

### Step-by-Step Workflow

#### Step 1 — 📷 Upload Remote Photo
- Drag & drop or click to upload a JPG/PNG/WEBP photo of your remote
- Preview is shown before proceeding

#### Step 2 — 🗺️ Map Buttons
- Your photo is processed through a **Sobel edge detection** pipeline:
  - Grayscale conversion → Gaussian blur → Sobel gradient → Threshold
  - Result: a dark blueprint with cyan edge lines and a subtle grid overlay
- **Click on each button** in the remote image to place a numbered marker
- **Name each button** in the side panel (e.g., "Power", "Vol Up", "CH 1")
- Undo, delete individual markers, or clear all
- Minimum 1 button required to proceed

#### Step 3 — 📡 Learn IR Signals
- Buttons are highlighted **one by one** with a pulsing red glow on the blueprint
- For each button, you must press the physical remote button **3 times**
- The system checks if all 3 readings match:
  - ✅ **All match** → Button is verified, auto-advances to the next
  - ⚠️ **Mismatch** → Warning shown, option to retry or skip
- Controls available:
  - **⏭ Skip** — Skip this button and move to the next
  - **🔄 Retry** — Clear attempts and try again
  - **⏹ Stop** — End early (remaining buttons marked as skipped)
- Progress bar updates in real-time

#### Step 4 — 📥 Export Results
- Summary statistics: Total / Learned / Skipped counts
- Full results table with button name, protocol, IR code, bits, and verification status
- **Download CSV** — Spreadsheet with all data including individual attempt codes
- **Download JSON** — Clean JSON array of verified buttons only
- Option to start over with a new remote

---

## 📡 API Reference

All API endpoints are served by the ESP8266 web server on port 80.

| Method | Endpoint | Description |
|--------|----------|-------------|
| `GET` | `/` | Main decoder dashboard |
| `GET` | `/learn` | Remote Learning Mode page |
| `GET` | `/api/buttons` | Get all saved buttons (JSON array) |
| `POST` | `/api/save` | Save a new button |
| `POST` | `/api/delete` | Delete a button by index |
| `POST` | `/api/clear` | Delete all saved buttons |

### WebSocket (Port 81)

Real-time IR signals are broadcast via WebSocket:

```json
{
  "type": "ir_code",
  "protocol": "NEC",
  "code": "FF30CF",
  "bits": 32
}
```

### Save Button Payload

```json
{
  "name": "Power",
  "protocol": "NEC",
  "code": "FF30CF",
  "bits": 32
}
```

---

## 📁 Project Structure

```
IR-Remote-Decode/
├── platformio.ini          # PlatformIO configuration & dependencies
├── README.md               # This file
├── include/
│   └── learn_page.h        # Learning Mode HTML/CSS/JS (PROGMEM)
├── src/
│   └── main.cpp            # Main firmware: WiFi, IR, web server, decoder UI
├── lib/                    # Custom libraries (empty)
└── .gitignore
```

### Dependencies

| Library | Version | Purpose |
|---------|---------|---------|
| [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) | ^2.8.6 | IR signal decoding (supports 100+ protocols) |
| [ArduinoJson](https://github.com/bblanchon/ArduinoJson) | ^6.21.5 | JSON serialization for API & WebSocket |
| [WebSockets](https://github.com/Links2004/arduinoWebSockets) | ^2.4.1 | Real-time browser communication |
| LittleFS | built-in | Persistent file storage on flash |
| ESP8266WebServer | built-in | HTTP server |
| ESP8266WiFi | built-in | WiFi connectivity |

---

## 🔀 Branches

| Branch | Description |
|--------|-------------|
| `master` | Base IR decoder with live dashboard |
| `feature/remote-learning` | Adds photo upload, edge detection, button mapping, 3× learning & export |

---

## 📊 Resource Usage

```
RAM:   [====      ]  40.3%  (33,012 / 81,920 bytes)
Flash: [====      ]  44.2%  (461,203 / 1,044,464 bytes)
```

Plenty of headroom for additional features.

---

## 🛠 Supported IR Protocols

Thanks to the IRremoteESP8266 library, the decoder supports **100+ protocols** including:

NEC • Sony • Samsung • LG • Panasonic • RC5 • RC6 • JVC • Sharp • Whynter • Coolix • Daikin • Mitsubishi • Toshiba • Fujitsu • Haier • Hitachi • Gree • Midea • TCL • Vestel • and many more...

---

## 📜 License

This project is open source and available under the [MIT License](LICENSE).

---

<p align="center">
  Built with ❤️ using ESP8266 + Arduino + PlatformIO
</p>
