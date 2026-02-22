/*
 * ESP8266 IR Remote Decoder with Web Interface
 * TSOP IR Sensor on GPIO2 (D4)
 * 
 * Libraries needed:
 *   - IRremoteESP8266
 *   - ESP8266WebServer
 *   - WebSocketsServer
 *   - ArduinoJson
 *   - LittleFS (built-in)
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

// ==================== CONFIGURATION ====================
const char* WIFI_SSID     = "Keralavision@1994";
const char* WIFI_PASSWORD = "babu7362";

const uint16_t IR_RECV_PIN = 2;  // GPIO2 = D4 on ESP8266
const uint16_t CAPTURE_BUFFER_SIZE = 1024;
const uint8_t  TIMEOUT = 50;
// =======================================================

IRrecv irrecv(IR_RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);
decode_results results;

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

// Store last decoded IR info
String lastProtocol = "";
String lastCode = "";
uint16_t lastBits = 0;
unsigned long lastTimestamp = 0;
bool newCodeAvailable = false;

// Saved buttons file
const char* SAVED_FILE = "/saved_buttons.json";

// ==================== WEBPAGE HTML ====================
const char MAIN_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IR Remote Decoder</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');
  
  * { margin: 0; padding: 0; box-sizing: border-box; }
  
  :root {
    --bg: #0f0f1a;
    --card: #1a1a2e;
    --card2: #16213e;
    --accent: #e94560;
    --accent2: #0f3460;
    --text: #eee;
    --text2: #aaa;
    --green: #00d68f;
    --blue: #3b82f6;
    --orange: #f59e0b;
    --border: rgba(255,255,255,0.08);
    --glow: rgba(233, 69, 96, 0.3);
  }

  body {
    font-family: 'Inter', sans-serif;
    background: var(--bg);
    color: var(--text);
    min-height: 100vh;
    overflow-x: hidden;
  }

  .bg-pattern {
    position: fixed; top: 0; left: 0; width: 100%; height: 100%;
    background: radial-gradient(ellipse at 20% 50%, rgba(233,69,96,0.08) 0%, transparent 50%),
                radial-gradient(ellipse at 80% 20%, rgba(15,52,96,0.15) 0%, transparent 50%),
                radial-gradient(ellipse at 50% 80%, rgba(0,214,143,0.05) 0%, transparent 50%);
    pointer-events: none; z-index: 0;
  }

  .container {
    max-width: 900px;
    margin: 0 auto;
    padding: 20px;
    position: relative;
    z-index: 1;
  }

  header {
    text-align: center;
    padding: 30px 0 20px;
  }

  header h1 {
    font-size: 2.2em;
    font-weight: 700;
    background: linear-gradient(135deg, var(--accent), #ff6b6b, var(--orange));
    -webkit-background-clip: text;
    -webkit-text-fill-color: transparent;
    margin-bottom: 8px;
  }

  header p {
    color: var(--text2);
    font-size: 0.95em;
  }

  .status-bar {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 10px;
    margin: 15px 0 25px;
    font-size: 0.85em;
  }

  .status-dot {
    width: 10px; height: 10px;
    border-radius: 50%;
    background: #ef4444;
    animation: none;
  }

  .status-dot.connected {
    background: var(--green);
    animation: pulse 2s infinite;
  }

  @keyframes pulse {
    0%, 100% { box-shadow: 0 0 0 0 rgba(0,214,143,0.5); }
    50% { box-shadow: 0 0 0 8px rgba(0,214,143,0); }
  }

  @keyframes slideIn {
    from { opacity: 0; transform: translateY(-10px); }
    to { opacity: 1; transform: translateY(0); }
  }

  @keyframes glowPulse {
    0%, 100% { box-shadow: 0 0 20px var(--glow), inset 0 0 20px rgba(233,69,96,0.05); }
    50% { box-shadow: 0 0 40px var(--glow), inset 0 0 30px rgba(233,69,96,0.1); }
  }

  .card {
    background: var(--card);
    border: 1px solid var(--border);
    border-radius: 16px;
    padding: 24px;
    margin-bottom: 20px;
    backdrop-filter: blur(10px);
    transition: all 0.3s ease;
  }

  .card:hover {
    border-color: rgba(233,69,96,0.2);
  }

  .card-title {
    font-size: 1.1em;
    font-weight: 600;
    margin-bottom: 16px;
    display: flex;
    align-items: center;
    gap: 10px;
  }

  .card-title .icon {
    font-size: 1.3em;
  }

  /* Live Decoder Section */
  .decoder-display {
    background: var(--card2);
    border-radius: 12px;
    padding: 20px;
    text-align: center;
    border: 1px solid var(--border);
    min-height: 120px;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    transition: all 0.3s ease;
    position: relative;
    overflow: hidden;
  }

  .decoder-display.active {
    animation: glowPulse 1.5s ease;
    border-color: var(--accent);
  }

  .decoder-display .waiting {
    color: var(--text2);
    font-size: 1.1em;
  }

  .decoder-display .waiting .remote-icon {
    font-size: 3em;
    display: block;
    margin-bottom: 10px;
    opacity: 0.4;
  }

  .ir-result {
    animation: slideIn 0.3s ease;
    width: 100%;
  }

  .ir-result .protocol {
    font-size: 0.85em;
    color: var(--green);
    font-weight: 500;
    text-transform: uppercase;
    letter-spacing: 1px;
    margin-bottom: 8px;
  }

  .ir-result .code {
    font-size: 1.8em;
    font-weight: 700;
    font-family: 'Courier New', monospace;
    color: #fff;
    word-break: break-all;
    text-shadow: 0 0 20px var(--glow);
  }

  .ir-result .bits {
    font-size: 0.8em;
    color: var(--text2);
    margin-top: 8px;
  }

  /* Save Section */
  .save-section {
    display: flex;
    gap: 12px;
    margin-top: 16px;
    flex-wrap: wrap;
  }

  .save-section input {
    flex: 1;
    min-width: 200px;
    padding: 12px 16px;
    border-radius: 10px;
    border: 1px solid var(--border);
    background: var(--card2);
    color: var(--text);
    font-size: 0.95em;
    font-family: 'Inter', sans-serif;
    outline: none;
    transition: all 0.3s ease;
  }

  .save-section input:focus {
    border-color: var(--accent);
    box-shadow: 0 0 0 3px rgba(233,69,96,0.15);
  }

  .save-section input::placeholder {
    color: #555;
  }

  .btn {
    padding: 12px 24px;
    border-radius: 10px;
    border: none;
    font-size: 0.95em;
    font-weight: 600;
    font-family: 'Inter', sans-serif;
    cursor: pointer;
    transition: all 0.3s ease;
    display: inline-flex;
    align-items: center;
    gap: 8px;
  }

  .btn-primary {
    background: linear-gradient(135deg, var(--accent), #c0392b);
    color: white;
  }

  .btn-primary:hover {
    transform: translateY(-2px);
    box-shadow: 0 5px 20px rgba(233,69,96,0.4);
  }

  .btn-primary:disabled {
    opacity: 0.5;
    cursor: not-allowed;
    transform: none;
    box-shadow: none;
  }

  .btn-danger {
    background: rgba(239,68,68,0.15);
    color: #ef4444;
    border: 1px solid rgba(239,68,68,0.2);
    padding: 8px 14px;
    font-size: 0.8em;
  }

  .btn-danger:hover {
    background: rgba(239,68,68,0.25);
  }

  .btn-clear {
    background: rgba(245,158,11,0.15);
    color: var(--orange);
    border: 1px solid rgba(245,158,11,0.2);
  }

  .btn-clear:hover {
    background: rgba(245,158,11,0.25);
  }

  /* Saved Buttons */
  .saved-list {
    display: grid;
    gap: 10px;
  }

  .saved-item {
    display: flex;
    align-items: center;
    justify-content: space-between;
    background: var(--card2);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 14px 18px;
    transition: all 0.3s ease;
    animation: slideIn 0.3s ease;
  }

  .saved-item:hover {
    border-color: rgba(59,130,246,0.3);
    background: rgba(22,33,62,0.8);
  }

  .saved-item .info {
    flex: 1;
  }

  .saved-item .name {
    font-weight: 600;
    font-size: 1em;
    margin-bottom: 4px;
    color: var(--blue);
  }

  .saved-item .detail {
    font-size: 0.8em;
    color: var(--text2);
    font-family: 'Courier New', monospace;
  }

  .saved-item .detail span {
    color: var(--green);
    font-weight: 500;
  }

  .empty-state {
    text-align: center;
    padding: 30px;
    color: var(--text2);
  }

  .empty-state .icon {
    font-size: 2.5em;
    margin-bottom: 10px;
    opacity: 0.3;
  }

  /* Log Section */
  .log-container {
    background: var(--card2);
    border-radius: 12px;
    border: 1px solid var(--border);
    max-height: 250px;
    overflow-y: auto;
    padding: 4px;
  }

  .log-container::-webkit-scrollbar { width: 6px; }
  .log-container::-webkit-scrollbar-track { background: transparent; }
  .log-container::-webkit-scrollbar-thumb { background: #333; border-radius: 3px; }

  .log-entry {
    padding: 8px 14px;
    border-bottom: 1px solid rgba(255,255,255,0.03);
    font-family: 'Courier New', monospace;
    font-size: 0.8em;
    display: flex;
    gap: 12px;
    align-items: baseline;
    animation: slideIn 0.2s ease;
  }

  .log-entry:last-child { border-bottom: none; }

  .log-entry .time {
    color: #555;
    white-space: nowrap;
    min-width: 70px;
  }

  .log-entry .proto {
    color: var(--green);
    min-width: 60px;
    font-weight: 500;
  }

  .log-entry .val {
    color: var(--text);
    word-break: break-all;
  }

  /* Header actions */
  .header-actions {
    display: flex;
    justify-content: space-between;
    align-items: center;
  }

  /* Toast */
  .toast {
    position: fixed;
    bottom: 30px;
    left: 50%;
    transform: translateX(-50%) translateY(100px);
    background: var(--green);
    color: #000;
    padding: 12px 24px;
    border-radius: 10px;
    font-weight: 600;
    font-size: 0.9em;
    z-index: 100;
    transition: transform 0.3s ease;
    box-shadow: 0 5px 30px rgba(0,214,143,0.3);
  }

  .toast.show {
    transform: translateX(-50%) translateY(0);
  }

  .toast.error {
    background: #ef4444;
    color: white;
    box-shadow: 0 5px 30px rgba(239,68,68,0.3);
  }

  /* Mode indicator */
  .mode-badge {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    padding: 6px 14px;
    border-radius: 20px;
    font-size: 0.8em;
    font-weight: 600;
    background: rgba(233,69,96,0.15);
    color: var(--accent);
    border: 1px solid rgba(233,69,96,0.2);
  }

  .mode-badge.learning {
    background: rgba(245,158,11,0.15);
    color: var(--orange);
    border-color: rgba(245,158,11,0.3);
    animation: pulse 1.5s infinite;
  }

  @media (max-width: 600px) {
    .container { padding: 12px; }
    header h1 { font-size: 1.6em; }
    .ir-result .code { font-size: 1.3em; }
    .save-section { flex-direction: column; }
    .save-section input { min-width: unset; }
  }
</style>
</head>
<body>
<div class="bg-pattern"></div>
<div class="container">
  <header>
    <h1>&#x1F4E1; IR Remote Decoder</h1>
    <p>Point your remote at the sensor and press any button</p>
    <div class="status-bar">
      <div class="status-dot" id="statusDot"></div>
      <span id="statusText">Connecting...</span>
    </div>
  </header>

  <!-- Live Decoder -->
  <div class="card">
    <div class="card-title">
      <span class="icon">&#x26A1;</span> Live Decoder
      <span class="mode-badge" id="modeBadge">MONITORING</span>
    </div>
    <div class="decoder-display" id="decoderDisplay">
      <div class="waiting" id="waitingMsg">
        <span class="remote-icon">&#x1F4F1;</span>
        Press any button on your remote...
      </div>
      <div class="ir-result" id="irResult" style="display:none">
        <div class="protocol" id="irProtocol"></div>
        <div class="code" id="irCode"></div>
        <div class="bits" id="irBits"></div>
      </div>
    </div>

    <!-- Save Control -->
    <div class="save-section">
      <input type="text" id="btnName" placeholder="&#x1F3F7;&#xFE0F; Enter button name (e.g., Power, Volume Up)" maxlength="30">
      <button class="btn btn-primary" id="saveBtn" disabled onclick="saveButton()">
        &#x1F4BE; Save Button
      </button>
    </div>
  </div>

  <!-- Saved Buttons -->
  <div class="card">
    <div class="header-actions">
      <div class="card-title" style="margin-bottom:0">
        <span class="icon">&#x1F4CB;</span> Saved Buttons
        <span id="savedCount" style="font-size:0.75em;color:var(--text2);font-weight:400"></span>
      </div>
      <button class="btn btn-clear" onclick="clearAll()" id="clearBtn" style="display:none">
        &#x1F5D1;&#xFE0F; Clear All
      </button>
    </div>
    <div style="margin-top:16px">
      <div class="saved-list" id="savedList">
        <div class="empty-state">
          <div class="icon">&#x1F4E6;</div>
          <p>No buttons saved yet.<br>Decode an IR signal and save it above!</p>
        </div>
      </div>
    </div>
  </div>

  <!-- Log -->
  <div class="card">
    <div class="header-actions">
      <div class="card-title" style="margin-bottom:0">
        <span class="icon">&#x1F4DC;</span> Signal Log
      </div>
      <button class="btn btn-danger" onclick="clearLog()">Clear</button>
    </div>
    <div style="margin-top:16px">
      <div class="log-container" id="logContainer">
        <div class="empty-state" id="logEmpty">
          <p>Waiting for signals...</p>
        </div>
      </div>
    </div>
  </div>
</div>

<div class="toast" id="toast"></div>

<script>
  let ws;
  let currentCode = null;
  let savedButtons = [];
  let logEntries = [];

  function connectWebSocket() {
    ws = new WebSocket('ws://' + location.hostname + ':81/');
    
    ws.onopen = () => {
      document.getElementById('statusDot').classList.add('connected');
      document.getElementById('statusText').textContent = 'Connected - Ready to decode';
      // Load saved buttons
      fetch('/api/buttons').then(r => r.json()).then(data => {
        savedButtons = data;
        renderSaved();
      }).catch(()=>{});
    };

    ws.onclose = () => {
      document.getElementById('statusDot').classList.remove('connected');
      document.getElementById('statusText').textContent = 'Disconnected - Reconnecting...';
      setTimeout(connectWebSocket, 2000);
    };

    ws.onerror = () => ws.close();

    ws.onmessage = (evt) => {
      try {
        const data = JSON.parse(evt.data);
        if (data.type === 'ir_code') {
          showDecodedSignal(data);
        }
      } catch(e) { console.error(e); }
    };
  }

  function showDecodedSignal(data) {
    currentCode = data;
    
    // Update display
    const display = document.getElementById('decoderDisplay');
    document.getElementById('waitingMsg').style.display = 'none';
    const result = document.getElementById('irResult');
    result.style.display = 'block';
    
    document.getElementById('irProtocol').textContent = data.protocol;
    document.getElementById('irCode').textContent = '0x' + data.code;
    document.getElementById('irBits').textContent = data.bits + ' bits';
    
    // Animate
    display.classList.remove('active');
    void display.offsetWidth;
    display.classList.add('active');

    // Enable save
    document.getElementById('saveBtn').disabled = false;
    document.getElementById('modeBadge').textContent = 'DECODED ✓';
    document.getElementById('modeBadge').className = 'mode-badge';

    // Add to log
    addLogEntry(data);
  }

  function addLogEntry(data) {
    const container = document.getElementById('logContainer');
    document.getElementById('logEmpty')?.remove();
    
    const now = new Date();
    const time = now.toLocaleTimeString('en-US', {hour12: false});
    
    const entry = document.createElement('div');
    entry.className = 'log-entry';
    entry.innerHTML = `
      <span class="time">${time}</span>
      <span class="proto">${data.protocol}</span>
      <span class="val">0x${data.code} (${data.bits}bit)</span>
    `;
    
    container.insertBefore(entry, container.firstChild);
    
    // Keep max 50 entries
    while (container.children.length > 50) {
      container.removeChild(container.lastChild);
    }
  }

  function saveButton() {
    const nameInput = document.getElementById('btnName');
    const name = nameInput.value.trim();
    
    if (!name) {
      showToast('Please enter a button name!', true);
      nameInput.focus();
      return;
    }
    
    if (!currentCode) {
      showToast('No IR code decoded yet!', true);
      return;
    }

    const payload = {
      name: name,
      protocol: currentCode.protocol,
      code: currentCode.code,
      bits: currentCode.bits
    };

    fetch('/api/save', {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify(payload)
    })
    .then(r => r.json())
    .then(data => {
      if (data.success) {
        showToast('Button "' + name + '" saved successfully!');
        nameInput.value = '';
        savedButtons = data.buttons;
        renderSaved();
        currentCode = null;
        document.getElementById('saveBtn').disabled = true;
        document.getElementById('modeBadge').textContent = 'MONITORING';
      } else {
        showToast(data.error || 'Save failed!', true);
      }
    })
    .catch(() => showToast('Network error!', true));
  }

  function renderSaved() {
    const list = document.getElementById('savedList');
    const countEl = document.getElementById('savedCount');
    const clearBtn = document.getElementById('clearBtn');
    
    if (savedButtons.length === 0) {
      list.innerHTML = '<div class="empty-state"><div class="icon">&#x1F4E6;</div><p>No buttons saved yet.<br>Decode an IR signal and save it above!</p></div>';
      countEl.textContent = '';
      clearBtn.style.display = 'none';
      return;
    }

    countEl.textContent = '(' + savedButtons.length + ')';
    clearBtn.style.display = 'inline-flex';
    
    list.innerHTML = savedButtons.map((btn, i) => `
      <div class="saved-item">
        <div class="info">
          <div class="name">&#x1F3AE; ${escHtml(btn.name)}</div>
          <div class="detail">
            <span>${btn.protocol}</span> &mdash; 0x${btn.code} &mdash; ${btn.bits} bits
          </div>
        </div>
        <button class="btn btn-danger" onclick="deleteButton(${i})">&#x1F5D1;&#xFE0F;</button>
      </div>
    `).join('');
  }

  function deleteButton(index) {
    fetch('/api/delete', {
      method: 'POST',
      headers: {'Content-Type': 'application/json'},
      body: JSON.stringify({index: index})
    })
    .then(r => r.json())
    .then(data => {
      if (data.success) {
        savedButtons = data.buttons;
        renderSaved();
        showToast('Button deleted');
      }
    })
    .catch(() => showToast('Delete failed!', true));
  }

  function clearAll() {
    if (!confirm('Delete all saved buttons?')) return;
    fetch('/api/clear', {method: 'POST'})
    .then(r => r.json())
    .then(data => {
      if (data.success) {
        savedButtons = [];
        renderSaved();
        showToast('All buttons cleared');
      }
    })
    .catch(() => showToast('Clear failed!', true));
  }

  function clearLog() {
    const container = document.getElementById('logContainer');
    container.innerHTML = '<div class="empty-state" id="logEmpty"><p>Waiting for signals...</p></div>';
  }

  function showToast(msg, isError) {
    const toast = document.getElementById('toast');
    toast.textContent = msg;
    toast.className = 'toast' + (isError ? ' error' : '') + ' show';
    setTimeout(() => toast.classList.remove('show'), 2500);
  }

  function escHtml(str) {
    const div = document.createElement('div');
    div.textContent = str;
    return div.innerHTML;
  }

  // Enter key saves
  document.getElementById('btnName').addEventListener('keypress', (e) => {
    if (e.key === 'Enter') saveButton();
  });

  connectWebSocket();
</script>
</body>
</html>
)rawliteral";

// ==================== FUNCTIONS ====================

void loadSavedButtons(String &output) {
  if (LittleFS.exists(SAVED_FILE)) {
    File f = LittleFS.open(SAVED_FILE, "r");
    if (f) {
      output = f.readString();
      f.close();
      return;
    }
  }
  output = "[]";
}

void saveToDisk(const String &json) {
  File f = LittleFS.open(SAVED_FILE, "w");
  if (f) {
    f.print(json);
    f.close();
  }
}

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WS] Client #%u disconnected\n", num);
      break;
    case WStype_CONNECTED:
      Serial.printf("[WS] Client #%u connected\n", num);
      break;
    default:
      break;
  }
}

// Send IR code to all WebSocket clients
void broadcastIRCode(const String &protocol, const String &code, uint16_t bits) {
  StaticJsonDocument<256> doc;
  doc["type"] = "ir_code";
  doc["protocol"] = protocol;
  doc["code"] = code;
  doc["bits"] = bits;

  String json;
  serializeJson(doc, json);
  webSocket.broadcastTXT(json);
}

// ==================== HTTP HANDLERS ====================

void handleRoot() {
  server.send_P(200, "text/html", MAIN_PAGE);
}

void handleGetButtons() {
  String json;
  loadSavedButtons(json);
  server.send(200, "application/json", json);
}

void handleSaveButton() {
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"success\":false,\"error\":\"No data\"}");
    return;
  }

  String body = server.arg("plain");
  StaticJsonDocument<512> newBtn;
  if (deserializeJson(newBtn, body)) {
    server.send(400, "application/json", "{\"success\":false,\"error\":\"Invalid JSON\"}");
    return;
  }

  // Load existing
  String existing;
  loadSavedButtons(existing);
  
  DynamicJsonDocument doc(4096);
  deserializeJson(doc, existing);
  JsonArray arr = doc.as<JsonArray>();

  // Add new button
  JsonObject obj = arr.createNestedObject();
  obj["name"] = newBtn["name"].as<String>();
  obj["protocol"] = newBtn["protocol"].as<String>();
  obj["code"] = newBtn["code"].as<String>();
  obj["bits"] = newBtn["bits"].as<uint16_t>();

  String output;
  serializeJson(doc, output);
  saveToDisk(output);

  Serial.printf("[SAVE] Button '%s' saved: %s 0x%s (%d bits)\n",
    newBtn["name"].as<const char*>(),
    newBtn["protocol"].as<const char*>(),
    newBtn["code"].as<const char*>(),
    newBtn["bits"].as<int>());

  String response = "{\"success\":true,\"buttons\":" + output + "}";
  server.send(200, "application/json", response);
}

void handleDeleteButton() {
  if (!server.hasArg("plain")) {
    server.send(400, "application/json", "{\"success\":false}");
    return;
  }

  StaticJsonDocument<128> reqDoc;
  deserializeJson(reqDoc, server.arg("plain"));
  int index = reqDoc["index"] | -1;

  String existing;
  loadSavedButtons(existing);
  
  DynamicJsonDocument doc(4096);
  deserializeJson(doc, existing);
  JsonArray arr = doc.as<JsonArray>();

  if (index >= 0 && index < (int)arr.size()) {
    arr.remove(index);
  }

  String output;
  serializeJson(doc, output);
  saveToDisk(output);

  String response = "{\"success\":true,\"buttons\":" + output + "}";
  server.send(200, "application/json", response);
}

void handleClearAll() {
  saveToDisk("[]");
  server.send(200, "application/json", "{\"success\":true,\"buttons\":[]}");
  Serial.println("[CLEAR] All saved buttons cleared");
}

// ==================== SETUP ====================

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=================================");
  Serial.println("  IR Remote Decoder - ESP8266");
  Serial.println("  Sensor: GPIO2 (D4)");
  Serial.println("=================================\n");

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("[FS] LittleFS mount failed, formatting...");
    LittleFS.format();
    LittleFS.begin();
  }
  Serial.println("[FS] LittleFS mounted");

  // Connect WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[WiFi] Connecting to ");
  Serial.print(WIFI_SSID);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Connected!");
    Serial.print("[WiFi] IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("\n>>> Open http://" + WiFi.localIP().toString() + " in your browser <<<\n");
  } else {
    Serial.println("\n[WiFi] Connection failed! Starting AP mode...");
    WiFi.softAP("IR_Decoder", "12345678");
    Serial.print("[WiFi] AP IP: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("\n>>> Connect to WiFi 'IR_Decoder' (pass: 12345678) <<<");
    Serial.println(">>> Then open http://" + WiFi.softAPIP().toString() + " <<<\n");
  }

  // Setup HTTP server
  server.on("/", handleRoot);
  server.on("/api/buttons", HTTP_GET, handleGetButtons);
  server.on("/api/save", HTTP_POST, handleSaveButton);
  server.on("/api/delete", HTTP_POST, handleDeleteButton);
  server.on("/api/clear", HTTP_POST, handleClearAll);
  server.begin();
  Serial.println("[HTTP] Web server started on port 80");

  // Setup WebSocket
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("[WS] WebSocket server started on port 81");

  // Start IR receiver
  irrecv.enableIRIn();
  Serial.println("[IR] Receiver started on GPIO2 (D4)");
  Serial.println("\n--- Ready! Point your remote at the sensor ---\n");
}

// ==================== LOOP ====================

void loop() {
  server.handleClient();
  webSocket.loop();

  if (irrecv.decode(&results)) {
    // Get protocol name
    String protocol = typeToString(results.decode_type, false);
    if (protocol == "UNKNOWN") protocol = "RAW";
    
    // Get hex code
    String code = resultToHexidecimal(&results);
    // Remove "0x" prefix if present
    if (code.startsWith("0x")) code = code.substring(2);
    
    uint16_t bits = results.bits;

    // Print to Serial
    Serial.println("┌──────────────────────────────────┐");
    Serial.printf("│ Protocol: %-22s │\n", protocol.c_str());
    Serial.printf("│ Code:     0x%-20s │\n", code.c_str());
    Serial.printf("│ Bits:     %-22d │\n", bits);
    Serial.println("└──────────────────────────────────┘");

    // Broadcast to web clients
    broadcastIRCode(protocol, code, bits);

    irrecv.resume();
  }

  delay(1);
}
