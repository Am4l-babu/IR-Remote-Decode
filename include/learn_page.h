#ifndef LEARN_PAGE_H
#define LEARN_PAGE_H

#include <Arduino.h>

const char LEARN_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IR Remote - Learning Mode</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');
*{margin:0;padding:0;box-sizing:border-box;}
:root{
  --bg:#0f0f1a;--card:#1a1a2e;--card2:#16213e;
  --accent:#e94560;--accent2:#0f3460;
  --text:#eee;--text2:#aaa;
  --green:#00d68f;--blue:#3b82f6;--orange:#f59e0b;
  --border:rgba(255,255,255,0.08);
  --glow:rgba(233,69,96,0.3);
  --cyan:#00deff;
}
body{font-family:'Inter',sans-serif;background:var(--bg);color:var(--text);min-height:100vh;overflow-x:hidden;}
.bg-pattern{position:fixed;top:0;left:0;width:100%;height:100%;
  background:radial-gradient(ellipse at 20% 50%,rgba(233,69,96,0.08) 0%,transparent 50%),
  radial-gradient(ellipse at 80% 20%,rgba(15,52,96,0.15) 0%,transparent 50%),
  radial-gradient(ellipse at 50% 80%,rgba(0,222,255,0.05) 0%,transparent 50%);
  pointer-events:none;z-index:0;}
.container{max-width:960px;margin:0 auto;padding:20px;position:relative;z-index:1;}

/* Header */
header{text-align:center;padding:20px 0 10px;}
.back-link{display:inline-flex;align-items:center;gap:6px;color:var(--text2);text-decoration:none;font-size:0.85em;
  padding:6px 14px;border-radius:8px;border:1px solid var(--border);transition:all 0.3s;margin-bottom:12px;}
.back-link:hover{color:var(--accent);border-color:var(--accent);}
header h1{font-size:2em;font-weight:700;
  background:linear-gradient(135deg,var(--cyan),var(--blue),var(--accent));
  -webkit-background-clip:text;-webkit-text-fill-color:transparent;margin-bottom:6px;}
header p{color:var(--text2);font-size:0.9em;}
.status-bar{display:flex;align-items:center;justify-content:center;gap:10px;margin:12px 0 20px;font-size:0.85em;}
.status-dot{width:10px;height:10px;border-radius:50%;background:#ef4444;}
.status-dot.connected{background:var(--green);animation:pulse 2s infinite;}
@keyframes pulse{0%,100%{box-shadow:0 0 0 0 rgba(0,214,143,0.5);}50%{box-shadow:0 0 0 8px rgba(0,214,143,0);}}

/* Steps */
.steps-bar{display:flex;align-items:center;justify-content:center;margin:0 0 28px;gap:0;flex-wrap:wrap;}
.step-item{display:flex;flex-direction:column;align-items:center;gap:4px;cursor:default;position:relative;}
.step-num{width:38px;height:38px;border-radius:50%;display:flex;align-items:center;justify-content:center;
  font-weight:700;font-size:0.95em;border:2px solid var(--border);color:var(--text2);background:var(--card);transition:all 0.4s;}
.step-label{font-size:0.7em;color:var(--text2);font-weight:500;transition:color 0.3s;}
.step-item.active .step-num{border-color:var(--accent);background:var(--accent);color:#fff;
  box-shadow:0 0 20px rgba(233,69,96,0.4);}
.step-item.active .step-label{color:var(--accent);}
.step-item.done .step-num{border-color:var(--green);background:var(--green);color:#fff;}
.step-item.done .step-label{color:var(--green);}
.step-line{width:60px;height:2px;background:var(--border);margin:0 6px;margin-bottom:18px;transition:background 0.4s;}
.step-line.done{background:var(--green);}

/* Cards */
.card{background:var(--card);border:1px solid var(--border);border-radius:16px;padding:24px;
  margin-bottom:20px;backdrop-filter:blur(10px);transition:all 0.3s;}
.card:hover{border-color:rgba(0,222,255,0.15);}
.card-title{font-size:1.1em;font-weight:600;margin-bottom:16px;display:flex;align-items:center;gap:10px;}
.step-content{display:none;animation:fadeIn 0.4s ease;}
.step-content.active{display:block;}
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}
@keyframes slideIn{from{opacity:0;transform:translateY(-10px);}to{opacity:1;transform:translateY(0);}}
@keyframes glowPulse{
  0%,100%{box-shadow:0 0 20px var(--glow),inset 0 0 20px rgba(233,69,96,0.05);}
  50%{box-shadow:0 0 40px var(--glow),inset 0 0 30px rgba(233,69,96,0.1);}}

/* Buttons */
.btn{padding:12px 24px;border-radius:10px;border:none;font-size:0.95em;font-weight:600;
  font-family:'Inter',sans-serif;cursor:pointer;transition:all 0.3s;display:inline-flex;align-items:center;gap:8px;}
.btn-primary{background:linear-gradient(135deg,var(--accent),#c0392b);color:#fff;}
.btn-primary:hover{transform:translateY(-2px);box-shadow:0 5px 20px rgba(233,69,96,0.4);}
.btn-primary:disabled{opacity:0.4;cursor:not-allowed;transform:none;box-shadow:none;}
.btn-secondary{background:rgba(59,130,246,0.15);color:var(--blue);border:1px solid rgba(59,130,246,0.2);}
.btn-secondary:hover{background:rgba(59,130,246,0.25);}
.btn-skip{background:rgba(245,158,11,0.15);color:var(--orange);border:1px solid rgba(245,158,11,0.25);padding:10px 20px;}
.btn-skip:hover{background:rgba(245,158,11,0.3);}
.btn-danger{background:rgba(239,68,68,0.15);color:#ef4444;border:1px solid rgba(239,68,68,0.2);padding:10px 20px;}
.btn-danger:hover{background:rgba(239,68,68,0.25);}
.btn-success{background:linear-gradient(135deg,var(--green),#00b377);color:#fff;}
.btn-success:hover{transform:translateY(-2px);box-shadow:0 5px 20px rgba(0,214,143,0.4);}
.btn-sm{padding:8px 14px;font-size:0.8em;border-radius:8px;}
.btn-ghost{background:transparent;color:var(--text2);border:1px solid var(--border);padding:10px 20px;}
.btn-ghost:hover{color:var(--text);border-color:var(--text2);}

/* Upload Zone */
.upload-zone{border:2px dashed rgba(0,222,255,0.25);border-radius:16px;padding:60px 30px;text-align:center;
  cursor:pointer;transition:all 0.3s;position:relative;overflow:hidden;}
.upload-zone:hover,.upload-zone.dragover{border-color:var(--cyan);background:rgba(0,222,255,0.03);}
.upload-zone .upload-icon{font-size:4em;margin-bottom:16px;opacity:0.6;}
.upload-zone h3{font-size:1.2em;margin-bottom:8px;color:var(--text);}
.upload-zone p{color:var(--text2);font-size:0.9em;}
.upload-zone .formats{color:var(--text2);font-size:0.75em;margin-top:8px;opacity:0.6;}

/* Preview */
.preview-area{text-align:center;margin-top:20px;}
.preview-area canvas{max-width:100%;border-radius:12px;border:2px solid var(--border);}
.preview-actions{display:flex;gap:12px;justify-content:center;margin-top:16px;flex-wrap:wrap;}

/* Split Layout */
.split-view{display:flex;gap:24px;align-items:flex-start;}
.split-left{flex:1;min-width:0;}
.split-right{width:280px;flex-shrink:0;}

/* Canvas Container */
.canvas-wrap{position:relative;display:inline-block;border-radius:12px;overflow:hidden;
  border:2px solid rgba(0,222,255,0.15);cursor:crosshair;background:#0a0a15;transition:border-color 0.3s;}
.canvas-wrap:hover{border-color:rgba(0,222,255,0.3);}
.canvas-wrap canvas{display:block;max-width:100%;height:auto;}
.canvas-hint{position:absolute;bottom:0;left:0;right:0;padding:10px;text-align:center;
  background:linear-gradient(transparent,rgba(0,0,0,0.8));color:var(--text2);font-size:0.8em;pointer-events:none;}

/* Button List Panel */
.btn-list-panel{background:var(--card2);border-radius:12px;border:1px solid var(--border);padding:16px;max-height:500px;overflow-y:auto;}
.btn-list-panel h3{font-size:0.95em;margin-bottom:12px;color:var(--text2);font-weight:500;}
.btn-list-panel::-webkit-scrollbar{width:5px;}
.btn-list-panel::-webkit-scrollbar-thumb{background:#333;border-radius:3px;}
.mapped-btn{display:flex;align-items:center;gap:10px;padding:10px 12px;border-radius:8px;
  background:rgba(255,255,255,0.03);border:1px solid var(--border);margin-bottom:8px;transition:all 0.3s;animation:slideIn 0.2s ease;}
.mapped-btn:hover{border-color:rgba(59,130,246,0.3);}
.mapped-btn .num{width:28px;height:28px;border-radius:50%;background:var(--blue);color:#fff;
  display:flex;align-items:center;justify-content:center;font-weight:700;font-size:0.8em;flex-shrink:0;}
.mapped-btn input{flex:1;background:transparent;border:none;color:var(--text);font-family:'Inter',sans-serif;
  font-size:0.9em;outline:none;padding:4px 0;border-bottom:1px solid transparent;transition:border-color 0.3s;}
.mapped-btn input:focus{border-bottom-color:var(--blue);}
.mapped-btn .del-btn{background:none;border:none;color:#555;cursor:pointer;font-size:1.1em;
  padding:4px;transition:color 0.3s;}
.mapped-btn .del-btn:hover{color:#ef4444;}
.panel-actions{display:flex;gap:8px;margin-top:12px;flex-wrap:wrap;}
.btn-count{font-size:0.75em;color:var(--text2);margin-bottom:8px;}

/* Learning Mode */
.progress-container{margin-bottom:20px;}
.progress-bar{width:100%;height:8px;background:var(--card2);border-radius:4px;overflow:hidden;border:1px solid var(--border);}
.progress-fill{height:100%;background:linear-gradient(90deg,var(--accent),var(--orange),var(--green));
  border-radius:4px;transition:width 0.5s ease;width:0%;}
.progress-text{text-align:center;margin-top:8px;font-size:0.8em;color:var(--text2);}

.learn-canvas-wrap{border-radius:12px;overflow:hidden;border:2px solid rgba(233,69,96,0.2);
  background:#0a0a15;cursor:default;transition:border-color 0.3s;}
.learn-canvas-wrap canvas{display:block;max-width:100%;height:auto;}

.learn-panel{background:var(--card2);border-radius:12px;border:1px solid var(--border);padding:20px;}
.current-btn-name{font-size:1.3em;font-weight:700;color:var(--accent);margin-bottom:4px;}
.current-btn-progress{font-size:0.85em;color:var(--text2);margin-bottom:20px;}

/* Attempts */
.attempts-list{display:flex;flex-direction:column;gap:8px;margin-bottom:20px;}
.attempt-row{display:flex;align-items:center;gap:10px;padding:10px 14px;border-radius:10px;
  background:rgba(255,255,255,0.03);border:1px solid var(--border);transition:all 0.3s;}
.attempt-row.waiting{opacity:0.4;}
.attempt-row.active{border-color:var(--accent);opacity:1;animation:glowPulse 1.5s ease infinite;}
.attempt-row.success{border-color:var(--green);opacity:1;background:rgba(0,214,143,0.05);}
.attempt-row.fail{border-color:#ef4444;opacity:1;background:rgba(239,68,68,0.05);}
.attempt-num{width:26px;height:26px;border-radius:50%;display:flex;align-items:center;justify-content:center;
  font-weight:700;font-size:0.75em;flex-shrink:0;border:2px solid var(--border);color:var(--text2);}
.attempt-row.success .attempt-num{border-color:var(--green);color:var(--green);}
.attempt-row.fail .attempt-num{border-color:#ef4444;color:#ef4444;}
.attempt-row.active .attempt-num{border-color:var(--accent);color:var(--accent);}
.attempt-info{flex:1;font-size:0.85em;color:var(--text2);}
.attempt-info .code-val{font-family:'Courier New',monospace;color:var(--text);font-weight:600;}
.attempt-icon{font-size:1.2em;}

.verify-status{padding:12px;border-radius:10px;text-align:center;font-weight:600;font-size:0.9em;margin-bottom:16px;
  border:1px solid var(--border);background:rgba(255,255,255,0.02);}
.verify-status.verified{color:var(--green);border-color:rgba(0,214,143,0.3);background:rgba(0,214,143,0.05);}
.verify-status.mismatch{color:#ef4444;border-color:rgba(239,68,68,0.3);background:rgba(239,68,68,0.05);}
.verify-status.pending{color:var(--orange);border-color:rgba(245,158,11,0.2);}

.learn-actions{display:flex;gap:10px;flex-wrap:wrap;}

/* Signal Flash */
.signal-flash{position:fixed;top:0;left:0;right:0;bottom:0;pointer-events:none;z-index:50;
  background:radial-gradient(circle,rgba(233,69,96,0.15),transparent 70%);opacity:0;transition:opacity 0.15s;}
.signal-flash.active{opacity:1;}

/* Results */
.results-header{text-align:center;margin-bottom:24px;}
.results-header h2{font-size:1.8em;margin-bottom:8px;
  background:linear-gradient(135deg,var(--green),var(--cyan));
  -webkit-background-clip:text;-webkit-text-fill-color:transparent;}
.stats-row{display:flex;gap:16px;justify-content:center;margin-bottom:24px;flex-wrap:wrap;}
.stat-card{background:var(--card2);border-radius:12px;padding:16px 24px;text-align:center;
  border:1px solid var(--border);min-width:120px;}
.stat-val{font-size:1.8em;font-weight:700;margin-bottom:4px;}
.stat-val.green{color:var(--green);}
.stat-val.orange{color:var(--orange);}
.stat-val.blue{color:var(--blue);}
.stat-label{font-size:0.75em;color:var(--text2);text-transform:uppercase;letter-spacing:1px;}

.results-table{width:100%;border-collapse:collapse;margin-bottom:20px;}
.results-table th{text-align:left;padding:10px 14px;font-size:0.75em;text-transform:uppercase;
  letter-spacing:1px;color:var(--text2);border-bottom:1px solid var(--border);}
.results-table td{padding:10px 14px;border-bottom:1px solid rgba(255,255,255,0.03);font-size:0.85em;}
.results-table tr:hover td{background:rgba(255,255,255,0.02);}
.results-table .code-cell{font-family:'Courier New',monospace;color:var(--cyan);}
.badge{display:inline-block;padding:3px 10px;border-radius:12px;font-size:0.75em;font-weight:600;}
.badge-green{background:rgba(0,214,143,0.15);color:var(--green);}
.badge-orange{background:rgba(245,158,11,0.15);color:var(--orange);}
.badge-red{background:rgba(239,68,68,0.15);color:#ef4444;}
.export-actions{display:flex;gap:12px;justify-content:center;flex-wrap:wrap;}

/* Toast */
.toast{position:fixed;bottom:30px;left:50%;transform:translateX(-50%) translateY(100px);
  background:var(--green);color:#000;padding:12px 24px;border-radius:10px;font-weight:600;
  font-size:0.9em;z-index:100;transition:transform 0.3s ease;box-shadow:0 5px 30px rgba(0,214,143,0.3);}
.toast.show{transform:translateX(-50%) translateY(0);}
.toast.error{background:#ef4444;color:#fff;box-shadow:0 5px 30px rgba(239,68,68,0.3);}

/* Responsive */
@media(max-width:768px){
  .split-view{flex-direction:column;}
  .split-right{width:100%;}
  .container{padding:12px;}
  header h1{font-size:1.5em;}
  .step-line{width:30px;}
  .stats-row{gap:8px;}
  .stat-card{min-width:90px;padding:12px 16px;}
  .results-table{font-size:0.8em;}
  .results-table th,.results-table td{padding:8px 10px;}
}
</style>
</head>
<body>
<div class="bg-pattern"></div>
<div class="signal-flash" id="signalFlash"></div>
<div class="container">
  <header>
    <a href="/" class="back-link">&#x2190; Back to Decoder</a>
    <h1>&#x1F3AF; Remote Learning Mode</h1>
    <p>Upload, map, and learn your remote's IR signals</p>
    <div class="status-bar">
      <div class="status-dot" id="statusDot"></div>
      <span id="statusText">Connecting...</span>
    </div>
  </header>

  <!-- Steps Bar -->
  <div class="steps-bar">
    <div class="step-item active" id="si1"><div class="step-num">1</div><div class="step-label">Upload</div></div>
    <div class="step-line" id="sl1"></div>
    <div class="step-item" id="si2"><div class="step-num">2</div><div class="step-label">Map</div></div>
    <div class="step-line" id="sl2"></div>
    <div class="step-item" id="si3"><div class="step-num">3</div><div class="step-label">Learn</div></div>
    <div class="step-line" id="sl3"></div>
    <div class="step-item" id="si4"><div class="step-num">4</div><div class="step-label">Export</div></div>
  </div>

  <!-- ===== STEP 1: UPLOAD ===== -->
  <div class="step-content active" id="step1">
    <div class="card">
      <div class="card-title"><span>&#x1F4F7;</span> Upload Remote Photo</div>
      <div class="upload-zone" id="uploadZone">
        <div class="upload-icon">&#x1F4F1;</div>
        <h3>Drop your remote photo here</h3>
        <p>or click to browse files</p>
        <div class="formats">Supports JPG, PNG, WEBP</div>
        <input type="file" id="fileInput" accept="image/*" hidden>
      </div>
      <div class="preview-area" id="previewArea" style="display:none">
        <canvas id="previewCanvas"></canvas>
        <div class="preview-actions">
          <button class="btn btn-ghost" onclick="resetUpload()">&#x1F504; Change Photo</button>
          <button class="btn btn-primary" onclick="processAndContinue()">&#x1F50D; Process &amp; Continue &#x2192;</button>
        </div>
      </div>
    </div>
  </div>

  <!-- ===== STEP 2: MAP BUTTONS ===== -->
  <div class="step-content" id="step2">
    <div class="card">
      <div class="card-title"><span>&#x1F5FA;&#xFE0F;</span> Map Remote Buttons</div>
      <p style="color:var(--text2);font-size:0.85em;margin-bottom:16px;">Click on each button in the remote image to mark it. Name each button in the panel.</p>
      <div class="split-view">
        <div class="split-left">
          <div class="canvas-wrap" id="mapCanvasWrap">
            <canvas id="mapCanvas"></canvas>
            <div class="canvas-hint" id="canvasHint">&#x1F446; Click on buttons to mark them</div>
          </div>
        </div>
        <div class="split-right">
          <div class="btn-list-panel">
            <h3>&#x1F4CC; Mapped Buttons</h3>
            <div class="btn-count" id="btnCount">0 buttons mapped</div>
            <div id="buttonList"></div>
            <div class="panel-actions">
              <button class="btn btn-sm btn-ghost" onclick="undoButton()">&#x21A9; Undo</button>
              <button class="btn btn-sm btn-danger" onclick="clearAllButtons()">&#x1F5D1; Clear</button>
            </div>
            <div style="margin-top:16px;">
              <button class="btn btn-primary" style="width:100%;" id="startLearnBtn" onclick="goToStep(3)" disabled>
                &#x25B6;&#xFE0F; Start Learning
              </button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- ===== STEP 3: LEARN SIGNALS ===== -->
  <div class="step-content" id="step3">
    <div class="card">
      <div class="card-title"><span>&#x1F4E1;</span> Learning IR Signals</div>
      <div class="progress-container">
        <div class="progress-bar"><div class="progress-fill" id="progressFill"></div></div>
        <div class="progress-text" id="progressText">0 / 0 buttons completed</div>
      </div>
      <div class="split-view">
        <div class="split-left">
          <div class="learn-canvas-wrap">
            <canvas id="learnCanvas"></canvas>
          </div>
        </div>
        <div class="split-right">
          <div class="learn-panel">
            <div class="current-btn-name" id="curBtnName">Button Name</div>
            <div class="current-btn-progress" id="curBtnProg">Button 1 of X</div>
            <div class="attempts-list" id="attemptsList">
              <div class="attempt-row active" id="att0">
                <div class="attempt-num">1</div>
                <div class="attempt-info">Point remote at sensor and press the button...</div>
                <div class="attempt-icon"></div>
              </div>
              <div class="attempt-row waiting" id="att1">
                <div class="attempt-num">2</div>
                <div class="attempt-info">Waiting...</div>
                <div class="attempt-icon"></div>
              </div>
              <div class="attempt-row waiting" id="att2">
                <div class="attempt-num">3</div>
                <div class="attempt-info">Waiting...</div>
                <div class="attempt-icon"></div>
              </div>
            </div>
            <div class="verify-status pending" id="verifyStatus">Awaiting 3 readings to verify...</div>
            <div class="learn-actions">
              <button class="btn btn-skip" onclick="skipCurrentButton()">&#x23ED; Skip</button>
              <button class="btn btn-ghost" onclick="retryCurrentButton()">&#x1F504; Retry</button>
              <button class="btn btn-danger" onclick="stopLearning()">&#x23F9; Stop</button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- ===== STEP 4: EXPORT ===== -->
  <div class="step-content" id="step4">
    <div class="card">
      <div class="results-header">
        <h2>&#x1F389; Learning Complete!</h2>
        <p style="color:var(--text2);">Your remote's IR signals have been captured and verified.</p>
      </div>
      <div class="stats-row" id="statsRow"></div>
      <div style="overflow-x:auto;">
        <table class="results-table" id="resultsTable">
          <thead><tr><th>#</th><th>Button Name</th><th>Protocol</th><th>IR Code</th><th>Bits</th><th>Status</th></tr></thead>
          <tbody id="resultsBody"></tbody>
        </table>
      </div>
      <div class="export-actions">
        <button class="btn btn-success" onclick="downloadCSV()">&#x1F4E5; Download CSV</button>
        <button class="btn btn-primary" onclick="downloadJSON()">&#x1F4C4; Download JSON</button>
        <button class="btn btn-ghost" onclick="startOver()">&#x1F504; Start Over</button>
      </div>
    </div>
  </div>
</div>

<div class="toast" id="toast"></div>

<script>
// ===== STATE =====
let ws;
let uploadedImg = null;
let blueprintData = null;
let originalImgData = null;
let buttons = [];
let currentStep = 1;
let isLearning = false;
let curBtnIdx = 0;
let attempts = [];
let results = [];
const MAX_ATT = 3;
const CW = 480;
let canvasW = CW, canvasH = 400;
let animId = null;

// ===== WEBSOCKET =====
function connectWS() {
  ws = new WebSocket('ws://' + location.hostname + ':81/');
  ws.onopen = () => {
    document.getElementById('statusDot').classList.add('connected');
    document.getElementById('statusText').textContent = 'Connected - Sensor Ready';
  };
  ws.onclose = () => {
    document.getElementById('statusDot').classList.remove('connected');
    document.getElementById('statusText').textContent = 'Disconnected - Reconnecting...';
    setTimeout(connectWS, 2000);
  };
  ws.onerror = () => ws.close();
  ws.onmessage = (evt) => {
    try {
      const d = JSON.parse(evt.data);
      if (d.type === 'ir_code' && isLearning) {
        onIRSignal(d);
      }
    } catch(e) {}
  };
}

// ===== STEP NAVIGATION =====
function goToStep(s) {
  if (s === 3 && buttons.length === 0) { showToast('Map at least one button first!', true); return; }
  currentStep = s;
  document.querySelectorAll('.step-content').forEach(el => el.classList.remove('active'));
  document.getElementById('step' + s).classList.add('active');
  // Update step indicators
  for (let i = 1; i <= 4; i++) {
    const si = document.getElementById('si' + i);
    si.classList.remove('active', 'done');
    if (i < s) si.classList.add('done');
    else if (i === s) si.classList.add('active');
    if (i < 4) {
      const sl = document.getElementById('sl' + i);
      sl.classList.toggle('done', i < s);
    }
  }
  if (s === 3) beginLearning();
  if (s === 4) showResults();
}

// ===== STEP 1: UPLOAD =====
const uploadZone = document.getElementById('uploadZone');
const fileInput = document.getElementById('fileInput');

uploadZone.addEventListener('click', () => fileInput.click());
uploadZone.addEventListener('dragover', (e) => { e.preventDefault(); uploadZone.classList.add('dragover'); });
uploadZone.addEventListener('dragleave', () => uploadZone.classList.remove('dragover'));
uploadZone.addEventListener('drop', (e) => {
  e.preventDefault(); uploadZone.classList.remove('dragover');
  if (e.dataTransfer.files.length > 0) handleFile(e.dataTransfer.files[0]);
});
fileInput.addEventListener('change', (e) => { if (e.target.files.length > 0) handleFile(e.target.files[0]); });

function handleFile(file) {
  if (!file.type.startsWith('image/')) { showToast('Please upload an image file!', true); return; }
  const reader = new FileReader();
  reader.onload = (e) => {
    const img = new Image();
    img.onload = () => {
      uploadedImg = img;
      showPreview(img);
    };
    img.src = e.target.result;
  };
  reader.readAsDataURL(file);
}

function showPreview(img) {
  uploadZone.style.display = 'none';
  const area = document.getElementById('previewArea');
  area.style.display = 'block';
  const c = document.getElementById('previewCanvas');
  const scale = Math.min(CW / img.width, 600 / img.height, 1);
  c.width = img.width * scale;
  c.height = img.height * scale;
  const ctx = c.getContext('2d');
  ctx.drawImage(img, 0, 0, c.width, c.height);
}

function resetUpload() {
  uploadedImg = null;
  uploadZone.style.display = '';
  document.getElementById('previewArea').style.display = 'none';
  fileInput.value = '';
}

function processAndContinue() {
  if (!uploadedImg) return;
  processImage();
  goToStep(2);
}

// ===== EDGE DETECTION =====
function toGray(data) {
  const g = new Float32Array(data.length / 4);
  for (let i = 0; i < g.length; i++) {
    g[i] = 0.299 * data[i*4] + 0.587 * data[i*4+1] + 0.114 * data[i*4+2];
  }
  return g;
}

function gaussBlur(gray, w, h) {
  const k = [1,2,1,2,4,2,1,2,1];
  const out = new Float32Array(w * h);
  for (let y = 1; y < h-1; y++) {
    for (let x = 1; x < w-1; x++) {
      let s = 0;
      for (let ky = -1; ky <= 1; ky++)
        for (let kx = -1; kx <= 1; kx++)
          s += gray[(y+ky)*w+(x+kx)] * k[(ky+1)*3+(kx+1)];
      out[y*w+x] = s / 16;
    }
  }
  return out;
}

function sobelDetect(gray, w, h) {
  const sx = [-1,0,1,-2,0,2,-1,0,1];
  const sy = [-1,-2,-1,0,0,0,1,2,1];
  const out = new Float32Array(w * h);
  for (let y = 1; y < h-1; y++) {
    for (let x = 1; x < w-1; x++) {
      let gx = 0, gy = 0;
      for (let ky = -1; ky <= 1; ky++)
        for (let kx = -1; kx <= 1; kx++) {
          const v = gray[(y+ky)*w+(x+kx)];
          const ki = (ky+1)*3+(kx+1);
          gx += v * sx[ki];
          gy += v * sy[ki];
        }
      out[y*w+x] = Math.sqrt(gx*gx + gy*gy);
    }
  }
  return out;
}

function processImage() {
  if (!uploadedImg) return;
  const mc = document.getElementById('mapCanvas');
  const scale = Math.min(CW / uploadedImg.width, 600 / uploadedImg.height, 1);
  canvasW = Math.round(uploadedImg.width * scale);
  canvasH = Math.round(uploadedImg.height * scale);
  mc.width = canvasW;
  mc.height = canvasH;
  const ctx = mc.getContext('2d');
  ctx.drawImage(uploadedImg, 0, 0, canvasW, canvasH);
  originalImgData = ctx.getImageData(0, 0, canvasW, canvasH);

  // Edge detection
  const gray = toGray(originalImgData.data);
  const blurred = gaussBlur(gray, canvasW, canvasH);
  const edges = sobelDetect(blurred, canvasW, canvasH);

  // Create blueprint: darkened original + cyan edges
  const bp = ctx.createImageData(canvasW, canvasH);
  const d = bp.data;
  const od = originalImgData.data;
  // Find max edge value for normalization
  let maxE = 0;
  for (let i = 0; i < edges.length; i++) if (edges[i] > maxE) maxE = edges[i];
  const thr = maxE * 0.12;

  for (let i = 0; i < canvasW * canvasH; i++) {
    const p = i * 4;
    const e = edges[i];
    if (e > thr) {
      const intensity = Math.min(e / (maxE * 0.4), 1);
      d[p]   = Math.round(0 + od[p] * 0.15);
      d[p+1] = Math.round(200 * intensity + od[p+1] * 0.1);
      d[p+2] = Math.round(255 * intensity + od[p+2] * 0.1);
      d[p+3] = 255;
    } else {
      d[p]   = Math.round(od[p] * 0.18);
      d[p+1] = Math.round(od[p+1] * 0.18);
      d[p+2] = Math.round(od[p+2] * 0.22);
      d[p+3] = 255;
    }
  }
  blueprintData = bp;
  renderMapCanvas();
}

// ===== STEP 2: MAPPING =====
const mapCanvas = document.getElementById('mapCanvas');
mapCanvas.addEventListener('click', onMapClick);
mapCanvas.addEventListener('touchend', (e) => {
  e.preventDefault();
  const t = e.changedTouches[0];
  const rect = mapCanvas.getBoundingClientRect();
  const sx = mapCanvas.width / rect.width;
  const sy = mapCanvas.height / rect.height;
  const x = (t.clientX - rect.left) * sx;
  const y = (t.clientY - rect.top) * sy;
  addButton(x, y);
});

function onMapClick(e) {
  const rect = mapCanvas.getBoundingClientRect();
  const sx = mapCanvas.width / rect.width;
  const sy = mapCanvas.height / rect.height;
  const x = (e.clientX - rect.left) * sx;
  const y = (e.clientY - rect.top) * sy;
  addButton(x, y);
}

function addButton(x, y) {
  const name = 'Button ' + (buttons.length + 1);
  buttons.push({ x, y, name });
  renderMapCanvas();
  renderButtonList();
  document.getElementById('startLearnBtn').disabled = false;
}

function undoButton() {
  if (buttons.length === 0) return;
  buttons.pop();
  renderMapCanvas();
  renderButtonList();
  if (buttons.length === 0) document.getElementById('startLearnBtn').disabled = true;
}

function clearAllButtons() {
  buttons = [];
  renderMapCanvas();
  renderButtonList();
  document.getElementById('startLearnBtn').disabled = true;
}

function deleteButton(idx) {
  buttons.splice(idx, 1);
  renderMapCanvas();
  renderButtonList();
  if (buttons.length === 0) document.getElementById('startLearnBtn').disabled = true;
}

function renameButton(idx, name) {
  buttons[idx].name = name;
}

function renderMapCanvas() {
  const c = document.getElementById('mapCanvas');
  const ctx = c.getContext('2d');
  if (blueprintData) ctx.putImageData(blueprintData, 0, 0);
  // Grid overlay
  ctx.strokeStyle = 'rgba(0,222,255,0.04)';
  ctx.lineWidth = 0.5;
  for (let x = 0; x < canvasW; x += 24) { ctx.beginPath(); ctx.moveTo(x,0); ctx.lineTo(x,canvasH); ctx.stroke(); }
  for (let y = 0; y < canvasH; y += 24) { ctx.beginPath(); ctx.moveTo(0,y); ctx.lineTo(canvasW,y); ctx.stroke(); }
  // Markers
  buttons.forEach((b, i) => drawMarker(ctx, b.x, b.y, i + 1, false, false, false));
}

function drawMarker(ctx, x, y, num, isCurrent, isDone, isSkipped) {
  const r = 16;
  ctx.save();
  if (isCurrent) {
    const t = Date.now() / 250;
    const gr = r + 10 + Math.sin(t) * 6;
    const grad = ctx.createRadialGradient(x, y, r - 2, x, y, gr);
    grad.addColorStop(0, 'rgba(233,69,96,0.55)');
    grad.addColorStop(1, 'rgba(233,69,96,0)');
    ctx.fillStyle = grad;
    ctx.beginPath(); ctx.arc(x, y, gr, 0, Math.PI*2); ctx.fill();
    ctx.fillStyle = '#e94560';
    ctx.strokeStyle = '#ff8a80';
    ctx.lineWidth = 3;
  } else if (isDone) {
    ctx.fillStyle = 'rgba(0,214,143,0.85)';
    ctx.strokeStyle = '#00ffaa';
    ctx.lineWidth = 2;
  } else if (isSkipped) {
    ctx.fillStyle = 'rgba(100,100,100,0.7)';
    ctx.strokeStyle = '#888';
    ctx.lineWidth = 2;
  } else {
    ctx.fillStyle = 'rgba(59,130,246,0.8)';
    ctx.strokeStyle = '#93c5fd';
    ctx.lineWidth = 2;
  }
  ctx.beginPath(); ctx.arc(x, y, r, 0, Math.PI*2); ctx.fill(); ctx.stroke();
  ctx.fillStyle = '#fff';
  ctx.font = 'bold 11px Inter,sans-serif';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';
  ctx.fillText(num, x, y + 1);
  ctx.restore();
}

function renderButtonList() {
  const list = document.getElementById('buttonList');
  document.getElementById('btnCount').textContent = buttons.length + ' button' + (buttons.length !== 1 ? 's' : '') + ' mapped';
  if (buttons.length === 0) {
    list.innerHTML = '<div style="text-align:center;padding:20px;color:var(--text2);font-size:0.85em;">Click on the remote image to mark buttons</div>';
    return;
  }
  list.innerHTML = buttons.map((b, i) => `
    <div class="mapped-btn">
      <div class="num">${i+1}</div>
      <input type="text" value="${escHtml(b.name)}" onchange="renameButton(${i},this.value)" onfocus="highlightMarker(${i})" onblur="renderMapCanvas()">
      <button class="del-btn" onclick="deleteButton(${i})" title="Remove">&#x2716;</button>
    </div>
  `).join('');
}

function highlightMarker(idx) {
  renderMapCanvas();
  const c = document.getElementById('mapCanvas');
  const ctx = c.getContext('2d');
  const b = buttons[idx];
  drawMarker(ctx, b.x, b.y, idx + 1, true, false, false);
}

// ===== STEP 3: LEARNING =====
function beginLearning() {
  isLearning = true;
  curBtnIdx = 0;
  attempts = [];
  results = new Array(buttons.length).fill(null).map(() => ({
    name: '', protocol: '', code: '', bits: 0, verified: false, skipped: false, attemptCodes: []
  }));
  // Copy names
  buttons.forEach((b, i) => results[i].name = b.name);
  updateLearningUI();
  startAnim();
}

function onIRSignal(data) {
  if (!isLearning || curBtnIdx >= buttons.length) return;

  // Flash effect
  const flash = document.getElementById('signalFlash');
  flash.classList.add('active');
  setTimeout(() => flash.classList.remove('active'), 200);

  attempts.push({ protocol: data.protocol, code: data.code, bits: data.bits });
  results[curBtnIdx].attemptCodes.push(data.code);
  updateAttemptsUI();

  if (attempts.length >= MAX_ATT) {
    checkVerification();
  }
}

function checkVerification() {
  const allMatch = attempts.every(a =>
    a.protocol === attempts[0].protocol && a.code === attempts[0].code
  );
  const r = results[curBtnIdx];
  if (allMatch) {
    r.verified = true;
    r.protocol = attempts[0].protocol;
    r.code = attempts[0].code;
    r.bits = attempts[0].bits;
    document.getElementById('verifyStatus').className = 'verify-status verified';
    document.getElementById('verifyStatus').innerHTML = '&#x2705; Verified! All 3 readings match.';
    showToast(buttons[curBtnIdx].name + ' verified!');
    setTimeout(() => moveToNext(), 1200);
  } else {
    document.getElementById('verifyStatus').className = 'verify-status mismatch';
    document.getElementById('verifyStatus').innerHTML = '&#x26A0; Mismatch! Readings differ. Try again or skip.';
    showToast('Readings do not match. Retry or skip.', true);
  }
}

function moveToNext() {
  curBtnIdx++;
  attempts = [];
  if (curBtnIdx >= buttons.length) {
    isLearning = false;
    stopAnim();
    goToStep(4);
  } else {
    updateLearningUI();
  }
}

function skipCurrentButton() {
  results[curBtnIdx].skipped = true;
  showToast(buttons[curBtnIdx].name + ' skipped');
  moveToNext();
}

function retryCurrentButton() {
  attempts = [];
  updateLearningUI();
}

function stopLearning() {
  isLearning = false;
  stopAnim();
  // Mark remaining as skipped
  for (let i = curBtnIdx; i < buttons.length; i++) {
    if (!results[i].verified) results[i].skipped = true;
  }
  goToStep(4);
}

function updateLearningUI() {
  if (curBtnIdx >= buttons.length) return;
  const b = buttons[curBtnIdx];
  document.getElementById('curBtnName').textContent = b.name;
  document.getElementById('curBtnProg').textContent = 'Button ' + (curBtnIdx + 1) + ' of ' + buttons.length;
  const done = results.filter(r => r.verified || r.skipped).length;
  const pct = buttons.length > 0 ? Math.round((done / buttons.length) * 100) : 0;
  document.getElementById('progressFill').style.width = pct + '%';
  document.getElementById('progressText').textContent = done + ' / ' + buttons.length + ' buttons completed';
  document.getElementById('verifyStatus').className = 'verify-status pending';
  document.getElementById('verifyStatus').innerHTML = '&#x23F3; Awaiting 3 readings to verify...';
  updateAttemptsUI();
}

function updateAttemptsUI() {
  for (let i = 0; i < MAX_ATT; i++) {
    const el = document.getElementById('att' + i);
    if (i < attempts.length) {
      el.className = 'attempt-row success';
      el.querySelector('.attempt-info').innerHTML =
        '<span class="code-val">' + attempts[i].protocol + ' 0x' + attempts[i].code + '</span> (' + attempts[i].bits + ' bits)';
      el.querySelector('.attempt-icon').textContent = '\u2705';
    } else if (i === attempts.length) {
      el.className = 'attempt-row active';
      el.querySelector('.attempt-info').textContent = 'Point remote at sensor and press the button...';
      el.querySelector('.attempt-icon').textContent = '';
    } else {
      el.className = 'attempt-row waiting';
      el.querySelector('.attempt-info').textContent = 'Waiting...';
      el.querySelector('.attempt-icon').textContent = '';
    }
  }
}

// Learning canvas animation
function startAnim() { if (!animId) animLoop(); }
function stopAnim() { if (animId) { cancelAnimationFrame(animId); animId = null; } }
function animLoop() {
  renderLearnCanvas();
  animId = requestAnimationFrame(animLoop);
}

function renderLearnCanvas() {
  const c = document.getElementById('learnCanvas');
  if (c.width !== canvasW || c.height !== canvasH) { c.width = canvasW; c.height = canvasH; }
  const ctx = c.getContext('2d');
  if (blueprintData) ctx.putImageData(blueprintData, 0, 0);
  // Grid
  ctx.strokeStyle = 'rgba(0,222,255,0.04)';
  ctx.lineWidth = 0.5;
  for (let x = 0; x < canvasW; x += 24) { ctx.beginPath(); ctx.moveTo(x,0); ctx.lineTo(x,canvasH); ctx.stroke(); }
  for (let y = 0; y < canvasH; y += 24) { ctx.beginPath(); ctx.moveTo(0,y); ctx.lineTo(canvasW,y); ctx.stroke(); }
  // Markers
  buttons.forEach((b, i) => {
    const isCur = i === curBtnIdx;
    const done = results[i] && results[i].verified;
    const skip = results[i] && results[i].skipped;
    drawMarker(ctx, b.x, b.y, i + 1, isCur, done, skip);
  });
  // Draw button name label for current
  if (curBtnIdx < buttons.length) {
    const b = buttons[curBtnIdx];
    const ctx2 = ctx;
    ctx2.save();
    ctx2.font = 'bold 12px Inter,sans-serif';
    ctx2.textAlign = 'center';
    const w = ctx2.measureText(b.name).width + 16;
    const lx = b.x;
    const ly = b.y - 28;
    ctx2.fillStyle = 'rgba(233,69,96,0.9)';
    ctx2.beginPath();
    ctx2.roundRect(lx - w/2, ly - 10, w, 20, 6);
    ctx2.fill();
    ctx2.fillStyle = '#fff';
    ctx2.fillText(b.name, lx, ly + 4);
    ctx2.restore();
  }
}

// ===== STEP 4: RESULTS =====
function showResults() {
  const learned = results.filter(r => r.verified).length;
  const skipped = results.filter(r => r.skipped).length;
  const total = results.length;

  document.getElementById('statsRow').innerHTML = `
    <div class="stat-card"><div class="stat-val blue">${total}</div><div class="stat-label">Total</div></div>
    <div class="stat-card"><div class="stat-val green">${learned}</div><div class="stat-label">Learned</div></div>
    <div class="stat-card"><div class="stat-val orange">${skipped}</div><div class="stat-label">Skipped</div></div>
  `;

  const tbody = document.getElementById('resultsBody');
  tbody.innerHTML = results.map((r, i) => `
    <tr>
      <td>${i + 1}</td>
      <td><strong>${escHtml(r.name)}</strong></td>
      <td>${r.verified ? r.protocol : '-'}</td>
      <td class="code-cell">${r.verified ? '0x' + r.code : '-'}</td>
      <td>${r.verified ? r.bits : '-'}</td>
      <td>${r.verified ? '<span class="badge badge-green">Verified</span>' :
           r.skipped ? '<span class="badge badge-orange">Skipped</span>' :
           '<span class="badge badge-red">Failed</span>'}</td>
    </tr>
  `).join('');
}

function downloadCSV() {
  let csv = 'Button Number,Button Name,Protocol,IR Code,Bits,Status,Attempt 1,Attempt 2,Attempt 3\n';
  results.forEach((r, i) => {
    const status = r.verified ? 'Verified' : r.skipped ? 'Skipped' : 'Failed';
    const a = r.attemptCodes || [];
    csv += `${i+1},"${r.name}",${r.verified ? r.protocol : ''},${r.verified ? '0x'+r.code : ''},${r.verified ? r.bits : ''},${status},${a[0]||''},${a[1]||''},${a[2]||''}\n`;
  });
  const blob = new Blob([csv], {type: 'text/csv'});
  const url = URL.createObjectURL(blob);
  const a = document.createElement('a');
  a.href = url;
  a.download = 'ir_remote_buttons_' + new Date().toISOString().slice(0,10) + '.csv';
  a.click();
  URL.revokeObjectURL(url);
  showToast('CSV downloaded!');
}

function downloadJSON() {
  const data = results.filter(r => r.verified).map((r, i) => ({
    button: i + 1,
    name: r.name,
    protocol: r.protocol,
    code: '0x' + r.code,
    bits: r.bits
  }));
  const blob = new Blob([JSON.stringify(data, null, 2)], {type: 'application/json'});
  const url = URL.createObjectURL(blob);
  const a = document.createElement('a');
  a.href = url;
  a.download = 'ir_remote_buttons_' + new Date().toISOString().slice(0,10) + '.json';
  a.click();
  URL.revokeObjectURL(url);
  showToast('JSON downloaded!');
}

function startOver() {
  buttons = [];
  results = [];
  attempts = [];
  curBtnIdx = 0;
  isLearning = false;
  uploadedImg = null;
  blueprintData = null;
  resetUpload();
  renderButtonList();
  goToStep(1);
}

// ===== UTILITIES =====
function showToast(msg, isError) {
  const t = document.getElementById('toast');
  t.textContent = msg;
  t.className = 'toast' + (isError ? ' error' : '') + ' show';
  setTimeout(() => t.classList.remove('show'), 2500);
}

function escHtml(s) {
  const d = document.createElement('div');
  d.textContent = s;
  return d.innerHTML;
}

// Polyfill roundRect for older browsers
if (!CanvasRenderingContext2D.prototype.roundRect) {
  CanvasRenderingContext2D.prototype.roundRect = function(x, y, w, h, r) {
    if (typeof r === 'number') r = [r, r, r, r];
    this.moveTo(x + r[0], y);
    this.lineTo(x + w - r[1], y);
    this.quadraticCurveTo(x + w, y, x + w, y + r[1]);
    this.lineTo(x + w, y + h - r[2]);
    this.quadraticCurveTo(x + w, y + h, x + w - r[2], y + h);
    this.lineTo(x + r[3], y + h);
    this.quadraticCurveTo(x, y + h, x, y + h - r[3]);
    this.lineTo(x, y + r[0]);
    this.quadraticCurveTo(x, y, x + r[0], y);
    this.closePath();
  };
}

// Init
connectWS();
</script>
</body>
</html>
)rawliteral";

#endif
