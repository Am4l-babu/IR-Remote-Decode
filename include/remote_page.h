#ifndef REMOTE_PAGE_H
#define REMOTE_PAGE_H

#include <Arduino.h>

const char REMOTE_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IR Remote Control</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');
*{margin:0;padding:0;box-sizing:border-box;}
:root{
  --bg:#0a0a16;--card:#141428;--card2:#1a1a35;
  --accent:#a855f7;--accent2:#7c3aed;
  --text:#eee;--text2:#888;
  --green:#00d68f;--blue:#3b82f6;--orange:#f59e0b;--red:#ef4444;
  --cyan:#00deff;--pink:#ec4899;--purple:#a855f7;
  --border:rgba(255,255,255,0.06);
  --glow:rgba(168,85,247,0.35);
}
body{font-family:'Inter',sans-serif;background:var(--bg);color:var(--text);min-height:100vh;overflow-x:hidden;}
.bg-pattern{position:fixed;top:0;left:0;width:100%;height:100%;
  background:radial-gradient(ellipse at 30% 30%,rgba(168,85,247,0.07) 0%,transparent 50%),
  radial-gradient(ellipse at 70% 70%,rgba(236,72,153,0.06) 0%,transparent 50%),
  radial-gradient(ellipse at 50% 50%,rgba(0,222,255,0.04) 0%,transparent 60%);
  pointer-events:none;z-index:0;}
.container{max-width:900px;margin:0 auto;padding:20px;position:relative;z-index:1;}

/* Header */
header{text-align:center;padding:20px 0 10px;}
.back-link{display:inline-flex;align-items:center;gap:6px;color:var(--text2);text-decoration:none;font-size:0.85em;
  padding:6px 14px;border-radius:8px;border:1px solid var(--border);transition:all 0.3s;margin-bottom:12px;}
.back-link:hover{color:var(--accent);border-color:var(--accent);}
header h1{font-size:2em;font-weight:700;
  background:linear-gradient(135deg,var(--purple),var(--pink),var(--orange));
  -webkit-background-clip:text;-webkit-text-fill-color:transparent;margin-bottom:6px;}
header p{color:var(--text2);font-size:0.9em;}
.status-bar{display:flex;align-items:center;justify-content:center;gap:10px;margin:12px 0 20px;font-size:0.85em;}
.status-dot{width:10px;height:10px;border-radius:50%;background:var(--red);}
.status-dot.connected{background:var(--green);animation:pulse 2s infinite;}
@keyframes pulse{0%,100%{box-shadow:0 0 0 0 rgba(0,214,143,0.5);}50%{box-shadow:0 0 0 8px rgba(0,214,143,0);}}
@keyframes slideIn{from{opacity:0;transform:translateY(-10px);}to{opacity:1;transform:translateY(0);}}
@keyframes pressAnim{
  0%{transform:scale(1);}
  30%{transform:scale(0.92);}
  60%{transform:scale(1.04);}
  100%{transform:scale(1);}
}
@keyframes ripple{
  0%{transform:scale(0);opacity:0.6;}
  100%{transform:scale(4);opacity:0;}
}
@keyframes sendPulse{
  0%{box-shadow:0 0 0 0 rgba(168,85,247,0.6);}
  50%{box-shadow:0 0 0 15px rgba(168,85,247,0);}
  100%{box-shadow:0 0 0 0 rgba(168,85,247,0);}
}
@keyframes irBeam{
  0%{opacity:1;transform:translateY(0) scaleX(1);}
  100%{opacity:0;transform:translateY(-60px) scaleX(0.3);}
}
@keyframes spin{0%{transform:rotate(0deg);}100%{transform:rotate(360deg);}}
@keyframes glow{0%,100%{filter:brightness(1);}50%{filter:brightness(1.3);}}

/* Cards */
.card{background:var(--card);border:1px solid var(--border);border-radius:16px;padding:24px;
  margin-bottom:20px;backdrop-filter:blur(10px);transition:all 0.3s;}
.card:hover{border-color:rgba(168,85,247,0.15);}
.card-title{font-size:1.05em;font-weight:600;margin-bottom:16px;display:flex;align-items:center;gap:10px;}

/* Buttons */
.btn{padding:12px 24px;border-radius:10px;border:none;font-size:0.95em;font-weight:600;
  font-family:'Inter',sans-serif;cursor:pointer;transition:all 0.3s;display:inline-flex;align-items:center;gap:8px;}
.btn-primary{background:linear-gradient(135deg,var(--accent),var(--accent2));color:#fff;}
.btn-primary:hover{transform:translateY(-2px);box-shadow:0 5px 20px var(--glow);}
.btn-ghost{background:transparent;color:var(--text2);border:1px solid var(--border);padding:10px 20px;}
.btn-ghost:hover{color:var(--text);border-color:var(--text2);}
.btn-sm{padding:8px 14px;font-size:0.8em;border-radius:8px;}

/* Empty State */
.empty-state{text-align:center;padding:50px 20px;color:var(--text2);}
.empty-state .big-icon{font-size:4em;margin-bottom:16px;opacity:0.3;}
.empty-state h3{font-size:1.1em;margin-bottom:8px;color:var(--text);}
.empty-state p{font-size:0.9em;max-width:400px;margin:0 auto;}
.empty-state .actions{margin-top:20px;display:flex;gap:10px;justify-content:center;flex-wrap:wrap;}

/* View Toggle */
.view-toggle{display:flex;background:var(--card2);border-radius:10px;padding:3px;border:1px solid var(--border);margin-bottom:20px;}
.view-btn{flex:1;padding:10px;text-align:center;border-radius:8px;font-size:0.85em;font-weight:600;
  cursor:pointer;transition:all 0.3s;color:var(--text2);border:none;background:none;font-family:'Inter',sans-serif;}
.view-btn.active{background:var(--accent);color:#fff;box-shadow:0 2px 12px var(--glow);}
.view-btn:hover:not(.active){color:var(--text);}

/* Remote Grid */
.remote-grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(130px,1fr));gap:14px;}
.remote-btn{position:relative;background:var(--card2);border:1px solid var(--border);border-radius:14px;
  padding:20px 14px;text-align:center;cursor:pointer;transition:all 0.3s;overflow:hidden;
  display:flex;flex-direction:column;align-items:center;justify-content:center;gap:8px;min-height:100px;
  user-select:none;-webkit-user-select:none;}
.remote-btn:hover{border-color:rgba(168,85,247,0.3);background:rgba(26,26,53,0.9);transform:translateY(-3px);
  box-shadow:0 8px 25px rgba(0,0,0,0.3);}
.remote-btn:active{transform:scale(0.95);transition:transform 0.1s;}
.remote-btn.sending{animation:sendPulse 0.6s ease;border-color:var(--accent);}
.remote-btn.sent{border-color:var(--green);}
.remote-btn .btn-icon{font-size:1.8em;transition:transform 0.3s;}
.remote-btn:hover .btn-icon{transform:scale(1.1);}
.remote-btn .btn-name{font-size:0.85em;font-weight:600;color:var(--text);word-break:break-word;}
.remote-btn .btn-proto{font-size:0.65em;color:var(--text2);font-family:'Courier New',monospace;margin-top:2px;}
.remote-btn .ripple{position:absolute;border-radius:50%;background:rgba(168,85,247,0.3);
  width:20px;height:20px;animation:ripple 0.6s ease-out forwards;pointer-events:none;}

/* Remote List */
.remote-list{display:flex;flex-direction:column;gap:8px;}
.list-item{display:flex;align-items:center;gap:14px;padding:14px 18px;border-radius:12px;
  background:var(--card2);border:1px solid var(--border);cursor:pointer;transition:all 0.3s;user-select:none;}
.list-item:hover{border-color:rgba(168,85,247,0.3);background:rgba(26,26,53,0.9);}
.list-item:active{transform:scale(0.98);}
.list-item.sending{animation:sendPulse 0.6s ease;border-color:var(--accent);}
.list-item.sent{border-color:var(--green);}
.list-item .li-icon{font-size:1.5em;width:44px;height:44px;display:flex;align-items:center;justify-content:center;
  background:rgba(168,85,247,0.1);border-radius:10px;flex-shrink:0;}
.list-item .li-info{flex:1;min-width:0;}
.list-item .li-name{font-weight:600;font-size:0.95em;margin-bottom:3px;}
.list-item .li-detail{font-size:0.75em;color:var(--text2);font-family:'Courier New',monospace;}
.list-item .li-send{width:40px;height:40px;border-radius:10px;border:none;cursor:pointer;
  background:linear-gradient(135deg,var(--accent),var(--accent2));color:#fff;font-size:1.1em;
  display:flex;align-items:center;justify-content:center;transition:all 0.3s;flex-shrink:0;}
.list-item .li-send:hover{transform:scale(1.1);box-shadow:0 4px 15px var(--glow);}

/* Quick Send Panel */
.quick-panel{background:var(--card2);border-radius:14px;border:1px solid var(--border);padding:20px;margin-bottom:20px;}
.quick-panel h3{font-size:0.9em;font-weight:600;margin-bottom:14px;color:var(--text2);}
.recent-sends{display:flex;gap:8px;flex-wrap:wrap;}
.recent-chip{padding:8px 14px;border-radius:20px;font-size:0.8em;font-weight:600;cursor:pointer;
  background:rgba(168,85,247,0.1);color:var(--accent);border:1px solid rgba(168,85,247,0.15);transition:all 0.3s;}
.recent-chip:hover{background:rgba(168,85,247,0.2);transform:translateY(-1px);}
.recent-chip.sending{background:var(--accent);color:#fff;}

/* Send Feedback Overlay */
.send-overlay{position:fixed;top:0;left:0;right:0;bottom:0;display:flex;align-items:center;justify-content:center;
  background:rgba(10,10,22,0.6);z-index:50;opacity:0;pointer-events:none;transition:opacity 0.2s;}
.send-overlay.active{opacity:1;pointer-events:auto;}
.send-card{background:var(--card);border:2px solid var(--accent);border-radius:20px;padding:40px;text-align:center;
  max-width:320px;width:90%;animation:slideIn 0.3s ease;}
.send-icon-big{font-size:3em;margin-bottom:16px;}
.send-name{font-size:1.3em;font-weight:700;margin-bottom:8px;
  background:linear-gradient(135deg,var(--accent),var(--pink));-webkit-background-clip:text;-webkit-text-fill-color:transparent;}
.send-status{font-size:0.9em;color:var(--text2);margin-bottom:4px;}
.send-code{font-family:'Courier New',monospace;font-size:0.8em;color:var(--cyan);margin-bottom:16px;}
.ir-beam{width:4px;height:20px;background:var(--accent);border-radius:4px;margin:0 auto 20px;
  animation:irBeam 0.6s ease-out infinite;}
.send-check{color:var(--green);font-size:2.5em;}

/* Repeat Controls */
.repeat-section{margin-top:20px;background:var(--card2);border-radius:14px;border:1px solid var(--border);padding:20px;}
.repeat-controls{display:flex;align-items:center;gap:16px;flex-wrap:wrap;}
.repeat-label{font-size:0.85em;color:var(--text2);font-weight:500;}
.repeat-input{width:70px;padding:8px 12px;border-radius:8px;border:1px solid var(--border);
  background:var(--bg);color:var(--text);font-family:'Inter',sans-serif;font-size:0.9em;text-align:center;outline:none;}
.repeat-input:focus{border-color:var(--accent);}
.delay-input{width:90px;}
.repeat-btn{padding:10px 24px;border-radius:10px;border:none;font-weight:600;font-size:0.9em;cursor:pointer;
  background:linear-gradient(135deg,var(--pink),var(--accent));color:#fff;transition:all 0.3s;font-family:'Inter',sans-serif;}
.repeat-btn:hover{transform:translateY(-2px);box-shadow:0 5px 20px rgba(236,72,153,0.3);}
.repeat-btn:disabled{opacity:0.4;cursor:not-allowed;transform:none;box-shadow:none;}
.repeat-progress{margin-top:14px;}
.repeat-bar{width:100%;height:6px;background:var(--bg);border-radius:3px;overflow:hidden;}
.repeat-bar-fill{height:100%;background:linear-gradient(90deg,var(--accent),var(--pink),var(--green));
  border-radius:3px;transition:width 0.3s;width:0%;}
.repeat-text{text-align:center;margin-top:6px;font-size:0.8em;color:var(--text2);}

/* Log */
.log-container{background:var(--card2);border-radius:12px;border:1px solid var(--border);
  max-height:220px;overflow-y:auto;padding:4px;}
.log-container::-webkit-scrollbar{width:5px;}
.log-container::-webkit-scrollbar-thumb{background:#333;border-radius:3px;}
.log-entry{padding:8px 14px;border-bottom:1px solid rgba(255,255,255,0.03);font-family:'Courier New',monospace;
  font-size:0.8em;display:flex;gap:12px;align-items:baseline;animation:slideIn 0.2s ease;}
.log-entry:last-child{border-bottom:none;}
.log-entry .time{color:#444;white-space:nowrap;min-width:70px;}
.log-entry .action{color:var(--accent);min-width:50px;font-weight:500;}
.log-entry .detail{color:var(--text);word-break:break-all;}
.log-entry.success .action{color:var(--green);}
.log-entry.error .action{color:var(--red);}

/* Stat bar */
.stat-bar{display:flex;gap:12px;margin-bottom:20px;flex-wrap:wrap;}
.stat-pill{display:flex;align-items:center;gap:8px;padding:10px 16px;border-radius:12px;
  background:var(--card);border:1px solid var(--border);flex:1;min-width:120px;}
.stat-pill .sp-val{font-size:1.4em;font-weight:700;}
.stat-pill .sp-val.purple{color:var(--accent);}
.stat-pill .sp-val.green{color:var(--green);}
.stat-pill .sp-val.pink{color:var(--pink);}
.stat-pill .sp-label{font-size:0.7em;color:var(--text2);text-transform:uppercase;letter-spacing:0.5px;}

/* Toast */
.toast{position:fixed;bottom:30px;left:50%;transform:translateX(-50%) translateY(100px);
  background:var(--green);color:#000;padding:12px 24px;border-radius:10px;font-weight:600;
  font-size:0.9em;z-index:100;transition:transform 0.3s ease;box-shadow:0 5px 30px rgba(0,214,143,0.3);}
.toast.show{transform:translateX(-50%) translateY(0);}
.toast.error{background:var(--red);color:#fff;box-shadow:0 5px 30px rgba(239,68,68,0.3);}
.toast.purple{background:var(--accent);color:#fff;box-shadow:0 5px 30px var(--glow);}

/* Responsive */
@media(max-width:600px){
  .container{padding:12px;}
  header h1{font-size:1.5em;}
  .remote-grid{grid-template-columns:repeat(auto-fill,minmax(100px,1fr));gap:10px;}
  .remote-btn{padding:14px 10px;min-height:80px;}
  .remote-btn .btn-icon{font-size:1.5em;}
  .repeat-controls{flex-direction:column;align-items:stretch;}
  .stat-bar{flex-direction:column;}
}
</style>
</head>
<body>
<div class="bg-pattern"></div>
<div class="container">
  <header>
    <a href="/" class="back-link">&#x2190; Back to Decoder</a>
    <h1>&#x1F399;&#xFE0F; IR Remote Control</h1>
    <p>Transmit saved IR signals with your ESP8266</p>
    <div class="status-bar">
      <div class="status-dot" id="statusDot"></div>
      <span id="statusText">Connecting...</span>
    </div>
  </header>

  <!-- Stats -->
  <div class="stat-bar">
    <div class="stat-pill"><div><div class="sp-val purple" id="totalBtns">0</div><div class="sp-label">Saved Buttons</div></div></div>
    <div class="stat-pill"><div><div class="sp-val green" id="totalSent">0</div><div class="sp-label">Signals Sent</div></div></div>
    <div class="stat-pill"><div><div class="sp-val pink" id="lastSentName">-</div><div class="sp-label">Last Sent</div></div></div>
  </div>

  <!-- Quick Recents -->
  <div class="quick-panel" id="quickPanel" style="display:none">
    <h3>&#x26A1; Recent</h3>
    <div class="recent-sends" id="recentSends"></div>
  </div>

  <!-- Main Remote Card -->
  <div class="card">
    <div style="display:flex;align-items:center;justify-content:space-between;flex-wrap:wrap;gap:10px;margin-bottom:16px;">
      <div class="card-title" style="margin-bottom:0;">
        <span>&#x1F3AE;</span> My Remote
      </div>
      <div class="view-toggle" style="margin-bottom:0;width:auto;">
        <button class="view-btn active" id="gridViewBtn" onclick="setView('grid')">&#x25A6; Grid</button>
        <button class="view-btn" id="listViewBtn" onclick="setView('list')">&#x2630; List</button>
      </div>
    </div>
    <div id="remoteContainer"></div>
  </div>

  <!-- Send with Repeat -->
  <div class="card">
    <div class="card-title"><span>&#x1F504;</span> Repeat Send</div>
    <p style="font-size:0.85em;color:var(--text2);margin-bottom:14px;">Select a button above, then configure repeat send below.</p>
    <div style="padding:12px 16px;border-radius:10px;background:var(--card2);border:1px solid var(--border);margin-bottom:16px;display:flex;align-items:center;gap:12px;">
      <span style="font-size:1.3em;" id="repeatIcon">&#x1F4A4;</span>
      <div>
        <div style="font-weight:600;font-size:0.95em;" id="selectedBtnName">No button selected</div>
        <div style="font-size:0.75em;color:var(--text2);font-family:'Courier New',monospace;" id="selectedBtnCode">-</div>
      </div>
    </div>
    <div class="repeat-controls">
      <div>
        <div class="repeat-label">Repeat Count</div>
        <input type="number" class="repeat-input" id="repeatCount" value="3" min="1" max="100">
      </div>
      <div>
        <div class="repeat-label">Delay (ms)</div>
        <input type="number" class="repeat-input delay-input" id="repeatDelay" value="500" min="50" max="10000" step="50">
      </div>
      <button class="repeat-btn" id="repeatBtn" onclick="startRepeatSend()" disabled>&#x1F680; Start Repeat</button>
      <button class="btn-ghost btn-sm" id="stopRepeatBtn" onclick="stopRepeatSend()" style="display:none;">&#x23F9; Stop</button>
    </div>
    <div class="repeat-progress" id="repeatProgress" style="display:none;">
      <div class="repeat-bar"><div class="repeat-bar-fill" id="repeatFill"></div></div>
      <div class="repeat-text" id="repeatText">0 / 0</div>
    </div>
  </div>

  <!-- Send Log -->
  <div class="card">
    <div style="display:flex;align-items:center;justify-content:space-between;">
      <div class="card-title" style="margin-bottom:0"><span>&#x1F4DC;</span> Send Log</div>
      <button class="btn-ghost btn-sm" onclick="clearLog()">Clear</button>
    </div>
    <div style="margin-top:14px;">
      <div class="log-container" id="logContainer">
        <div class="empty-state" id="logEmpty" style="padding:20px;"><p>No signals sent yet</p></div>
      </div>
    </div>
  </div>
</div>

<!-- Send Overlay -->
<div class="send-overlay" id="sendOverlay">
  <div class="send-card">
    <div class="send-icon-big" id="sendFbIcon">&#x1F4E1;</div>
    <div id="sendFbBeam"><div class="ir-beam"></div></div>
    <div class="send-name" id="sendFbName">Sending...</div>
    <div class="send-status" id="sendFbStatus">Transmitting IR signal</div>
    <div class="send-code" id="sendFbCode"></div>
    <div class="send-check" id="sendFbCheck" style="display:none;">&#x2705;</div>
  </div>
</div>

<div class="toast" id="toast"></div>

<script>
// ===== STATE =====
let ws;
let buttons = [];
let view = 'grid';
let totalSent = 0;
let recentList = [];
let selectedBtn = null;
let repeating = false;
let repeatTimer = null;

const ICON_MAP = {
  'power': '&#x23FB;', 'on': '&#x23FB;', 'off': '&#x23FB;',
  'vol': '&#x1F50A;', 'volume': '&#x1F50A;', 'mute': '&#x1F507;',
  'ch': '&#x1F4FA;', 'channel': '&#x1F4FA;',
  'up': '&#x25B2;', 'down': '&#x25BC;', 'left': '&#x25C0;', 'right': '&#x25B6;',
  'ok': '&#x2713;', 'enter': '&#x2713;', 'select': '&#x2713;',
  'menu': '&#x2630;', 'home': '&#x1F3E0;', 'back': '&#x21A9;', 'exit': '&#x2716;',
  'play': '&#x25B6;&#xFE0F;', 'pause': '&#x23F8;', 'stop': '&#x23F9;', 'rec': '&#x23FA;',
  'next': '&#x23ED;', 'prev': '&#x23EE;', 'forward': '&#x23E9;', 'rewind': '&#x23EA;',
  'input': '&#x1F504;', 'source': '&#x1F504;', 'mode': '&#x1F504;',
  'info': '&#x2139;&#xFE0F;', 'guide': '&#x1F4D6;', 'subtitle': '&#x1F4DD;',
  'red': '&#x1F534;', 'green': '&#x1F7E2;', 'blue': '&#x1F535;', 'yellow': '&#x1F7E1;',
  '1': '1&#xFE0F;&#x20E3;', '2': '2&#xFE0F;&#x20E3;', '3': '3&#xFE0F;&#x20E3;',
  '4': '4&#xFE0F;&#x20E3;', '5': '5&#xFE0F;&#x20E3;', '6': '6&#xFE0F;&#x20E3;',
  '7': '7&#xFE0F;&#x20E3;', '8': '8&#xFE0F;&#x20E3;', '9': '9&#xFE0F;&#x20E3;',
  '0': '0&#xFE0F;&#x20E3;',
  'temp': '&#x1F321;', 'fan': '&#x1F4A8;', 'swing': '&#x1F300;', 'sleep': '&#x1F319;',
  'timer': '&#x23F0;', 'light': '&#x1F4A1;', 'cool': '&#x2744;', 'heat': '&#x1F525;',
  'auto': '&#x1F300;', 'turbo': '&#x26A1;',
};

function getIcon(name) {
  const n = name.toLowerCase();
  for (const [key, icon] of Object.entries(ICON_MAP)) {
    if (n.includes(key)) return icon;
  }
  return '&#x1F4E1;';
}

// ===== WEBSOCKET =====
function connectWS() {
  ws = new WebSocket('ws://' + location.hostname + ':81/');
  ws.onopen = () => {
    document.getElementById('statusDot').classList.add('connected');
    document.getElementById('statusText').textContent = 'Connected - IR LED Ready (GPIO5)';
    loadButtons();
  };
  ws.onclose = () => {
    document.getElementById('statusDot').classList.remove('connected');
    document.getElementById('statusText').textContent = 'Disconnected - Reconnecting...';
    setTimeout(connectWS, 2000);
  };
  ws.onerror = () => ws.close();
}

// ===== DATA =====
function loadButtons() {
  fetch('/api/buttons').then(r=>r.json()).then(data => {
    buttons = data;
    document.getElementById('totalBtns').textContent = buttons.length;
    renderRemote();
  }).catch(()=>{});
}

// ===== VIEW =====
function setView(v) {
  view = v;
  document.getElementById('gridViewBtn').classList.toggle('active', v==='grid');
  document.getElementById('listViewBtn').classList.toggle('active', v==='list');
  renderRemote();
}

function renderRemote() {
  const c = document.getElementById('remoteContainer');
  if (buttons.length === 0) {
    c.innerHTML = `<div class="empty-state">
      <div class="big-icon">&#x1F3AE;</div>
      <h3>No Buttons Saved Yet</h3>
      <p>Go to the decoder page and save some IR buttons, or use Learning Mode to map your remote.</p>
      <div class="actions">
        <a href="/" class="btn btn-primary" style="text-decoration:none;">&#x1F4E1; Go to Decoder</a>
        <a href="/learn" class="btn btn-ghost" style="text-decoration:none;">&#x1F3AF; Learning Mode</a>
      </div>
    </div>`;
    return;
  }
  if (view === 'grid') renderGrid(c);
  else renderList(c);
}

function renderGrid(c) {
  c.innerHTML = '<div class="remote-grid">' + buttons.map((b, i) =>
    `<div class="remote-btn" id="rbtn${i}" onclick="sendSignal(${i})" oncontextmenu="selectForRepeat(${i});return false;">
      <div class="btn-icon">${getIcon(b.name)}</div>
      <div class="btn-name">${escHtml(b.name)}</div>
      <div class="btn-proto">${b.protocol} 0x${b.code}</div>
    </div>`
  ).join('') + '</div>';
}

function renderList(c) {
  c.innerHTML = '<div class="remote-list">' + buttons.map((b, i) =>
    `<div class="list-item" id="lbtn${i}" onclick="selectForRepeat(${i})">
      <div class="li-icon">${getIcon(b.name)}</div>
      <div class="li-info">
        <div class="li-name">${escHtml(b.name)}</div>
        <div class="li-detail">${b.protocol} &mdash; 0x${b.code} &mdash; ${b.bits}bit</div>
      </div>
      <button class="li-send" onclick="event.stopPropagation();sendSignal(${i})">&#x1F4E1;</button>
    </div>`
  ).join('') + '</div>';
}

// ===== SEND =====
function sendSignal(idx) {
  const b = buttons[idx];
  showSendFeedback(b);
  const el = document.getElementById((view==='grid'?'rbtn':'lbtn') + idx);
  if (el) { el.classList.add('sending'); setTimeout(()=>{ el.classList.remove('sending'); el.classList.add('sent'); setTimeout(()=>el.classList.remove('sent'),1500); }, 600); }

  fetch('/api/send', {
    method: 'POST',
    headers: {'Content-Type':'application/json'},
    body: JSON.stringify({ protocol: b.protocol, code: b.code, bits: b.bits })
  }).then(r=>r.json()).then(data => {
    if (data.success) {
      completeSendFeedback(b);
      totalSent++;
      document.getElementById('totalSent').textContent = totalSent;
      document.getElementById('lastSentName').textContent = b.name;
      addRecent(b.name, idx);
      addLog(b, true);
    } else {
      showToast('Send failed: ' + (data.error||'Unknown'), true);
      addLog(b, false);
    }
  }).catch(() => { showToast('Network error!', true); addLog(b, false); });
}

function showSendFeedback(b) {
  const o = document.getElementById('sendOverlay');
  document.getElementById('sendFbIcon').innerHTML = getIcon(b.name);
  document.getElementById('sendFbName').textContent = b.name;
  document.getElementById('sendFbStatus').textContent = 'Transmitting IR signal...';
  document.getElementById('sendFbCode').textContent = b.protocol + ' 0x' + b.code + ' (' + b.bits + ' bits)';
  document.getElementById('sendFbBeam').style.display = 'block';
  document.getElementById('sendFbCheck').style.display = 'none';
  o.classList.add('active');
}

function completeSendFeedback(b) {
  document.getElementById('sendFbStatus').textContent = 'Signal sent successfully!';
  document.getElementById('sendFbBeam').style.display = 'none';
  document.getElementById('sendFbCheck').style.display = 'block';
  setTimeout(() => document.getElementById('sendOverlay').classList.remove('active'), 800);
}

// ===== REPEAT =====
function selectForRepeat(idx) {
  selectedBtn = idx;
  const b = buttons[idx];
  document.getElementById('repeatIcon').innerHTML = getIcon(b.name);
  document.getElementById('selectedBtnName').textContent = b.name;
  document.getElementById('selectedBtnCode').textContent = b.protocol + ' 0x' + b.code + ' (' + b.bits + ' bits)';
  document.getElementById('repeatBtn').disabled = false;
  showToast(b.name + ' selected for repeat', false, true);
}

let repeatDone = 0, repeatTotal = 0;

function startRepeatSend() {
  if (selectedBtn === null) return;
  const count = parseInt(document.getElementById('repeatCount').value) || 3;
  const delay = parseInt(document.getElementById('repeatDelay').value) || 500;
  repeatTotal = count;
  repeatDone = 0;
  repeating = true;
  document.getElementById('repeatBtn').disabled = true;
  document.getElementById('stopRepeatBtn').style.display = 'inline-flex';
  document.getElementById('repeatProgress').style.display = 'block';
  updateRepeatProgress();
  doRepeatStep(delay);
}

function doRepeatStep(delay) {
  if (!repeating || repeatDone >= repeatTotal) {
    finishRepeat();
    return;
  }
  sendSignal(selectedBtn);
  repeatDone++;
  updateRepeatProgress();
  if (repeatDone < repeatTotal) {
    repeatTimer = setTimeout(() => doRepeatStep(delay), delay);
  } else {
    setTimeout(finishRepeat, 600);
  }
}

function updateRepeatProgress() {
  const pct = repeatTotal > 0 ? Math.round((repeatDone / repeatTotal) * 100) : 0;
  document.getElementById('repeatFill').style.width = pct + '%';
  document.getElementById('repeatText').textContent = repeatDone + ' / ' + repeatTotal + ' sent';
}

function stopRepeatSend() {
  repeating = false;
  if (repeatTimer) clearTimeout(repeatTimer);
  finishRepeat();
  showToast('Repeat stopped', true);
}

function finishRepeat() {
  repeating = false;
  document.getElementById('repeatBtn').disabled = false;
  document.getElementById('stopRepeatBtn').style.display = 'none';
  if (repeatDone >= repeatTotal && repeatTotal > 0) {
    showToast('Repeat complete! ' + repeatTotal + ' signals sent', false, true);
  }
}

// ===== RECENT =====
function addRecent(name, idx) {
  recentList = recentList.filter(r => r.idx !== idx);
  recentList.unshift({ name, idx });
  if (recentList.length > 8) recentList.pop();
  renderRecent();
}

function renderRecent() {
  const p = document.getElementById('quickPanel');
  const c = document.getElementById('recentSends');
  if (recentList.length === 0) { p.style.display = 'none'; return; }
  p.style.display = 'block';
  c.innerHTML = recentList.map(r =>
    `<div class="recent-chip" onclick="sendSignal(${r.idx})">${getIcon(r.name)} ${escHtml(r.name)}</div>`
  ).join('');
}

// ===== LOG =====
function addLog(b, success) {
  const c = document.getElementById('logContainer');
  const emp = document.getElementById('logEmpty');
  if (emp) emp.remove();
  const now = new Date().toLocaleTimeString('en-US',{hour12:false});
  const e = document.createElement('div');
  e.className = 'log-entry' + (success ? ' success' : ' error');
  e.innerHTML = `<span class="time">${now}</span><span class="action">${success?'SENT':'FAIL'}</span><span class="detail">${escHtml(b.name)} &mdash; ${b.protocol} 0x${b.code}</span>`;
  c.insertBefore(e, c.firstChild);
  while (c.children.length > 50) c.removeChild(c.lastChild);
}

function clearLog() {
  document.getElementById('logContainer').innerHTML = '<div class="empty-state" id="logEmpty" style="padding:20px;"><p>No signals sent yet</p></div>';
}

// ===== UTILS =====
function showToast(msg, isError, isPurple) {
  const t = document.getElementById('toast');
  t.textContent = msg;
  t.className = 'toast' + (isError ? ' error' : isPurple ? ' purple' : '') + ' show';
  setTimeout(() => t.classList.remove('show'), 2000);
}

function escHtml(s) { const d = document.createElement('div'); d.textContent = s; return d.innerHTML; }

connectWS();
</script>
</body>
</html>
)rawliteral";

#endif
