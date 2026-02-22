#ifndef MACRO_PAGE_H
#define MACRO_PAGE_H

#include <Arduino.h>

const char MACRO_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IR Macro Sequences</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap');
*{margin:0;padding:0;box-sizing:border-box;}
:root{
  --bg:#0a0a16;--card:#141428;--card2:#1a1a35;
  --accent:#f59e0b;--accent2:#d97706;
  --text:#eee;--text2:#888;
  --green:#00d68f;--blue:#3b82f6;--orange:#f59e0b;--red:#ef4444;
  --cyan:#00deff;--pink:#ec4899;--purple:#a855f7;
  --border:rgba(255,255,255,0.06);
  --glow:rgba(245,158,11,0.35);
}
body{font-family:'Inter',sans-serif;background:var(--bg);color:var(--text);min-height:100vh;overflow-x:hidden;}
.bg-pattern{position:fixed;top:0;left:0;width:100%;height:100%;
  background:radial-gradient(ellipse at 30% 30%,rgba(245,158,11,0.07) 0%,transparent 50%),
  radial-gradient(ellipse at 70% 70%,rgba(217,119,6,0.06) 0%,transparent 50%),
  radial-gradient(ellipse at 50% 50%,rgba(0,222,255,0.04) 0%,transparent 60%);
  pointer-events:none;z-index:0;}
.container{max-width:960px;margin:0 auto;padding:20px;position:relative;z-index:1;}

header{text-align:center;padding:20px 0 10px;}
.back-link{display:inline-flex;align-items:center;gap:6px;color:var(--text2);text-decoration:none;font-size:0.85em;
  padding:6px 14px;border-radius:8px;border:1px solid var(--border);transition:all 0.3s;margin-bottom:12px;}
.back-link:hover{color:var(--accent);border-color:var(--accent);}
header h1{font-size:2em;font-weight:700;
  background:linear-gradient(135deg,var(--orange),var(--pink),var(--cyan));
  -webkit-background-clip:text;-webkit-text-fill-color:transparent;margin-bottom:6px;}
header p{color:var(--text2);font-size:0.9em;}

/* Cards */
.card{background:var(--card);border:1px solid var(--border);border-radius:16px;padding:20px;margin-bottom:18px;
  backdrop-filter:blur(10px);}
.card-title{font-size:1.1em;font-weight:600;margin-bottom:14px;display:flex;align-items:center;gap:10px;}
.card-title .icon{font-size:1.3em;}

/* Two-panel layout */
.panels{display:grid;grid-template-columns:1fr 1fr;gap:18px;margin-bottom:18px;}
@media(max-width:700px){.panels{grid-template-columns:1fr;}}

/* Button picker */
.picker-list{display:flex;flex-direction:column;gap:8px;max-height:400px;overflow-y:auto;padding-right:4px;}
.picker-list::-webkit-scrollbar{width:5px;}
.picker-list::-webkit-scrollbar-track{background:transparent;}
.picker-list::-webkit-scrollbar-thumb{background:var(--accent);border-radius:4px;}
.picker-item{display:flex;align-items:center;justify-content:space-between;padding:10px 14px;
  border-radius:10px;background:var(--card2);border:1px solid var(--border);cursor:pointer;transition:all 0.2s;}
.picker-item:hover{border-color:var(--accent);background:rgba(245,158,11,0.08);}
.picker-item .btn-name{font-weight:500;font-size:0.95em;}
.picker-item .btn-proto{font-size:0.75em;color:var(--text2);background:rgba(255,255,255,0.05);
  padding:2px 8px;border-radius:4px;}
.picker-item .add-btn{width:28px;height:28px;border-radius:8px;border:1px solid var(--accent);
  background:rgba(245,158,11,0.1);color:var(--accent);font-size:1.1em;cursor:pointer;
  display:flex;align-items:center;justify-content:center;transition:all 0.2s;}
.picker-item .add-btn:hover{background:var(--accent);color:#000;}

/* Sequence builder */
.sequence-list{display:flex;flex-direction:column;gap:6px;min-height:120px;padding:6px;
  border:2px dashed var(--border);border-radius:12px;transition:border-color 0.3s;}
.sequence-list.drag-over{border-color:var(--accent);background:rgba(245,158,11,0.03);}
.sequence-list.empty-state::after{content:'Click + on buttons to add them here';display:flex;
  align-items:center;justify-content:center;height:100px;color:var(--text2);font-size:0.85em;font-style:italic;}
.seq-item{display:flex;align-items:center;gap:10px;padding:10px 12px;border-radius:10px;
  background:var(--card2);border:1px solid var(--border);cursor:grab;transition:all 0.25s;position:relative;}
.seq-item:active{cursor:grabbing;}
.seq-item.dragging{opacity:0.5;transform:scale(0.96);}
.seq-item.playing{border-color:var(--green);box-shadow:0 0 15px rgba(0,214,143,0.3);
  animation:playGlow 0.6s ease;}
.seq-item.played{border-color:rgba(0,214,143,0.3);opacity:0.7;}
@keyframes playGlow{0%{transform:scale(1);}30%{transform:scale(1.02);}100%{transform:scale(1);}}
.seq-num{width:24px;height:24px;border-radius:6px;background:var(--accent);color:#000;font-weight:700;
  font-size:0.75em;display:flex;align-items:center;justify-content:center;flex-shrink:0;}
.seq-info{flex:1;min-width:0;}
.seq-name{font-weight:500;font-size:0.9em;white-space:nowrap;overflow:hidden;text-overflow:ellipsis;}
.seq-detail{font-size:0.72em;color:var(--text2);}
.seq-delay{display:flex;align-items:center;gap:4px;}
.seq-delay input{width:65px;padding:4px 6px;border-radius:6px;border:1px solid var(--border);
  background:var(--card);color:var(--text);font-size:0.8em;text-align:center;}
.seq-delay input:focus{outline:none;border-color:var(--accent);}
.seq-delay label{font-size:0.72em;color:var(--text2);}
.seq-actions{display:flex;gap:4px;}
.seq-actions button{width:26px;height:26px;border-radius:6px;border:1px solid var(--border);
  background:transparent;color:var(--text2);cursor:pointer;display:flex;align-items:center;
  justify-content:center;font-size:0.8em;transition:all 0.2s;}
.seq-actions button:hover{color:var(--text);border-color:var(--text2);}
.seq-actions .move-up:hover,.seq-actions .move-down:hover{border-color:var(--blue);color:var(--blue);}
.seq-actions .remove:hover{border-color:var(--red);color:var(--red);}

/* Controls bar */
.controls{display:flex;gap:10px;flex-wrap:wrap;align-items:center;margin-bottom:18px;}
.ctrl-btn{padding:10px 20px;border-radius:10px;border:1px solid var(--border);background:var(--card);
  color:var(--text);font-weight:600;font-size:0.9em;cursor:pointer;display:inline-flex;align-items:center;
  gap:8px;transition:all 0.3s;font-family:'Inter',sans-serif;}
.ctrl-btn:hover{transform:translateY(-2px);}
.ctrl-btn.play{background:linear-gradient(135deg,#065f46,#064e3b);border-color:rgba(0,214,143,0.3);color:var(--green);}
.ctrl-btn.play:hover{box-shadow:0 5px 20px rgba(0,214,143,0.2);}
.ctrl-btn.play:disabled{opacity:0.4;cursor:not-allowed;transform:none;}
.ctrl-btn.stop{background:linear-gradient(135deg,#7f1d1d,#5a1a1a);border-color:rgba(239,68,68,0.3);color:var(--red);}
.ctrl-btn.stop:hover{box-shadow:0 5px 20px rgba(239,68,68,0.2);}
.ctrl-btn.loop{background:linear-gradient(135deg,#1e3a5f,#162d4a);border-color:rgba(59,130,246,0.3);color:var(--blue);}
.ctrl-btn.loop:hover{box-shadow:0 5px 20px rgba(59,130,246,0.2);}
.ctrl-btn.loop.active{border-color:var(--blue);box-shadow:0 0 12px rgba(59,130,246,0.3);}
.ctrl-btn.clear-seq{background:linear-gradient(135deg,#4a1a1a,#3a1111);border-color:rgba(239,68,68,0.2);color:var(--red);}

/* Global delay */
.global-delay{display:flex;align-items:center;gap:8px;margin-left:auto;}
.global-delay label{font-size:0.8em;color:var(--text2);white-space:nowrap;}
.global-delay input{width:80px;padding:6px 8px;border-radius:8px;border:1px solid var(--border);
  background:var(--card);color:var(--text);font-size:0.85em;text-align:center;}
.global-delay input:focus{outline:none;border-color:var(--accent);}

/* Progress bar */
.progress-bar{width:100%;height:6px;background:var(--card2);border-radius:3px;margin:10px 0;overflow:hidden;display:none;}
.progress-bar.active{display:block;}
.progress-fill{height:100%;background:linear-gradient(90deg,var(--green),var(--cyan));border-radius:3px;
  transition:width 0.3s ease;width:0%;}

/* Run log */
.run-log{max-height:200px;overflow-y:auto;font-size:0.8em;margin-top:10px;padding:10px;
  background:var(--card2);border-radius:10px;border:1px solid var(--border);}
.run-log::-webkit-scrollbar{width:4px;}
.run-log::-webkit-scrollbar-thumb{background:var(--accent);border-radius:4px;}
.log-entry{padding:4px 0;border-bottom:1px solid var(--border);display:flex;gap:8px;align-items:center;}
.log-entry:last-child{border-bottom:none;}
.log-entry .log-step{color:var(--accent);font-weight:600;min-width:30px;}
.log-entry .log-name{flex:1;}
.log-entry .log-status{font-weight:500;}
.log-entry .log-status.ok{color:var(--green);}
.log-entry .log-status.fail{color:var(--red);}
.log-entry .log-status.skip{color:var(--text2);}

/* Saved macros */
.macro-save-row{display:flex;gap:8px;margin-bottom:12px;}
.macro-save-row input{flex:1;padding:8px 12px;border-radius:8px;border:1px solid var(--border);
  background:var(--card2);color:var(--text);font-size:0.9em;}
.macro-save-row input:focus{outline:none;border-color:var(--accent);}
.macro-save-row button{padding:8px 16px;border-radius:8px;border:1px solid var(--accent);
  background:rgba(245,158,11,0.1);color:var(--accent);font-weight:600;cursor:pointer;transition:all 0.2s;
  font-family:'Inter',sans-serif;}
.macro-save-row button:hover{background:var(--accent);color:#000;}
.saved-macros{display:flex;flex-direction:column;gap:6px;}
.saved-macro{display:flex;align-items:center;justify-content:space-between;padding:10px 14px;
  border-radius:10px;background:var(--card2);border:1px solid var(--border);transition:all 0.2s;}
.saved-macro:hover{border-color:var(--accent);}
.saved-macro .macro-info{flex:1;}
.saved-macro .macro-name{font-weight:500;font-size:0.95em;}
.saved-macro .macro-meta{font-size:0.72em;color:var(--text2);}
.saved-macro .macro-actions{display:flex;gap:6px;}
.saved-macro .macro-actions button{padding:6px 12px;border-radius:6px;border:1px solid var(--border);
  background:transparent;color:var(--text2);font-size:0.78em;cursor:pointer;transition:all 0.2s;
  font-family:'Inter',sans-serif;}
.saved-macro .macro-actions .load-btn:hover{border-color:var(--blue);color:var(--blue);}
.saved-macro .macro-actions .del-btn:hover{border-color:var(--red);color:var(--red);}

.empty-msg{text-align:center;color:var(--text2);font-size:0.85em;padding:30px;font-style:italic;}

/* Animations */
@keyframes slideIn{from{opacity:0;transform:translateY(-10px);}to{opacity:1;transform:translateY(0);}}
</style>
</head>
<body>
<div class="bg-pattern"></div>
<div class="container">
  <header>
    <a href="/" class="back-link">&#x2190; Back to Decoder</a>
    <h1>&#x1F3AC; Macro Sequences</h1>
    <p>Build and play automated IR button sequences</p>
  </header>

  <!-- Panels: Picker + Sequence Builder -->
  <div class="panels">
    <!-- Left: Button Picker -->
    <div class="card">
      <div class="card-title"><span class="icon">&#x1F4E6;</span> Saved Buttons</div>
      <div id="pickerList" class="picker-list">
        <div class="empty-msg">No saved buttons found.<br>Decode and save buttons first.</div>
      </div>
    </div>

    <!-- Right: Sequence Builder -->
    <div class="card">
      <div class="card-title"><span class="icon">&#x1F4CB;</span> Sequence <span id="seqCount" style="font-size:0.7em;color:var(--text2);font-weight:400;margin-left:auto;">0 steps</span></div>
      <div id="sequenceList" class="sequence-list empty-state"></div>
    </div>
  </div>

  <!-- Controls -->
  <div class="card">
    <div class="card-title"><span class="icon">&#x1F3AE;</span> Playback Controls</div>
    <div class="controls">
      <button class="ctrl-btn play" id="playBtn" onclick="playSequence()" disabled>&#x25B6; Play</button>
      <button class="ctrl-btn stop" id="stopBtn" onclick="stopSequence()" style="display:none;">&#x25A0; Stop</button>
      <button class="ctrl-btn loop" id="loopBtn" onclick="toggleLoop()">&#x1F501; Loop</button>
      <button class="ctrl-btn clear-seq" onclick="clearSequence()">&#x1F5D1; Clear</button>
      <div class="global-delay">
        <label>Default Delay:</label>
        <input type="number" id="globalDelay" value="500" min="50" max="10000" step="50"> 
        <label>ms</label>
      </div>
    </div>
    <div class="progress-bar" id="progressBar"><div class="progress-fill" id="progressFill"></div></div>
    <div id="runLog" class="run-log" style="display:none;"></div>
  </div>

  <!-- Save / Load Macros -->
  <div class="card">
    <div class="card-title"><span class="icon">&#x1F4BE;</span> Saved Macros</div>
    <div class="macro-save-row">
      <input type="text" id="macroName" placeholder="Macro name..." maxlength="40">
      <button onclick="saveMacro()">Save Current</button>
    </div>
    <div id="savedMacros" class="saved-macros">
      <div class="empty-msg">No saved macros yet</div>
    </div>
  </div>
</div>

<script>
// State
let savedButtons = [];
let sequence = [];
let isPlaying = false;
let loopMode = false;
let stopRequested = false;

// ICON MAP (same as remote page)
const ICON_MAP = {
  'power':'\u23FB','on':'\u23FB','off':'\u23FB','standby':'\u23FB',
  'vol':'\u{1F50A}','volume':'\u{1F50A}','mute':'\u{1F507}',
  'ch':'\u{1F4FA}','channel':'\u{1F4FA}',
  'up':'\u2B06','down':'\u2B07','left':'\u2B05','right':'\u27A1',
  'ok':'\u2714','enter':'\u2714','select':'\u2714',
  'menu':'\u2630','home':'\u{1F3E0}','back':'\u21A9',
  'play':'\u25B6','pause':'\u23F8','stop':'\u23F9','rec':'\u23FA',
  'next':'\u23ED','prev':'\u23EE','ff':'\u23E9','rew':'\u23EA',
  '0':'0\uFE0F\u20E3','1':'1\uFE0F\u20E3','2':'2\uFE0F\u20E3','3':'3\uFE0F\u20E3',
  '4':'4\uFE0F\u20E3','5':'5\uFE0F\u20E3','6':'6\uFE0F\u20E3','7':'7\uFE0F\u20E3',
  '8':'8\uFE0F\u20E3','9':'9\uFE0F\u20E3',
  'input':'\u{1F504}','source':'\u{1F504}','hdmi':'\u{1F5B5}',
  'red':'\u{1F534}','green':'\u{1F7E2}','yellow':'\u{1F7E1}','blue':'\u{1F535}',
  'info':'\u2139','guide':'\u{1F4D6}','exit':'\u274C','sleep':'\u{1F319}'
};
function getIcon(name){
  const n=name.toLowerCase();
  for(const[k,v]of Object.entries(ICON_MAP)){if(n.includes(k))return v;}
  return '\u{1F4E1}';
}

// Load saved buttons
async function loadButtons(){
  try{
    const r=await fetch('/api/buttons');
    savedButtons=await r.json();
    renderPicker();
  }catch(e){console.error('Failed to load buttons',e);}
}

function renderPicker(){
  const el=document.getElementById('pickerList');
  if(!savedButtons.length){
    el.innerHTML='<div class="empty-msg">No saved buttons found.<br>Decode and save buttons first.</div>';
    return;
  }
  el.innerHTML=savedButtons.map((b,i)=>`
    <div class="picker-item" onclick="addToSequence(${i})">
      <span style="font-size:1.2em;margin-right:6px;">${getIcon(b.name)}</span>
      <span class="btn-name" style="flex:1">${b.name}</span>
      <span class="btn-proto">${b.protocol}</span>
      <button class="add-btn" title="Add to sequence">+</button>
    </div>
  `).join('');
}

// Sequence management
function addToSequence(btnIdx){
  if(isPlaying)return;
  const b=savedButtons[btnIdx];
  const delay=parseInt(document.getElementById('globalDelay').value)||500;
  sequence.push({name:b.name,protocol:b.protocol,code:b.code,bits:b.bits,delay:delay,btnIdx:btnIdx});
  renderSequence();
  updatePlayBtn();
}

function removeFromSequence(idx){
  if(isPlaying)return;
  sequence.splice(idx,1);
  renderSequence();
  updatePlayBtn();
}

function moveStep(idx,dir){
  if(isPlaying)return;
  const newIdx=idx+dir;
  if(newIdx<0||newIdx>=sequence.length)return;
  [sequence[idx],sequence[newIdx]]=[sequence[newIdx],sequence[idx]];
  renderSequence();
}

function clearSequence(){
  if(isPlaying)return;
  sequence=[];
  renderSequence();
  updatePlayBtn();
}

function updatePlayBtn(){
  document.getElementById('playBtn').disabled=sequence.length===0;
}

function renderSequence(){
  const el=document.getElementById('sequenceList');
  document.getElementById('seqCount').textContent=sequence.length+' step'+(sequence.length!==1?'s':'');
  if(!sequence.length){
    el.className='sequence-list empty-state';
    el.innerHTML='';
    return;
  }
  el.className='sequence-list';
  el.innerHTML=sequence.map((s,i)=>`
    <div class="seq-item" id="seq-${i}" draggable="true" ondragstart="dragStart(event,${i})" ondragover="dragOver(event)" ondrop="drop(event,${i})" ondragend="dragEnd(event)">
      <span class="seq-num">${i+1}</span>
      <span style="font-size:1.1em;">${getIcon(s.name)}</span>
      <div class="seq-info">
        <div class="seq-name">${s.name}</div>
        <div class="seq-detail">${s.protocol} | 0x${s.code} | ${s.bits}bit</div>
      </div>
      <div class="seq-delay">
        <label>Delay</label>
        <input type="number" value="${s.delay}" min="50" max="30000" step="50"
          onchange="sequence[${i}].delay=parseInt(this.value)||500" onclick="event.stopPropagation()">
        <label>ms</label>
      </div>
      <div class="seq-actions">
        <button class="move-up" onclick="moveStep(${i},-1)" title="Move up">&#x25B2;</button>
        <button class="move-down" onclick="moveStep(${i},1)" title="Move down">&#x25BC;</button>
        <button class="remove" onclick="removeFromSequence(${i})" title="Remove">&#x2715;</button>
      </div>
    </div>
  `).join('');
}

// Drag & drop reorder
let dragIdx=null;
function dragStart(e,idx){if(isPlaying){e.preventDefault();return;}dragIdx=idx;e.target.classList.add('dragging');}
function dragOver(e){e.preventDefault();}
function drop(e,targetIdx){
  e.preventDefault();
  if(dragIdx===null||dragIdx===targetIdx)return;
  const item=sequence.splice(dragIdx,1)[0];
  sequence.splice(targetIdx,0,item);
  dragIdx=null;
  renderSequence();
}
function dragEnd(e){e.target.classList.remove('dragging');dragIdx=null;}

// Playback
async function playSequence(){
  if(isPlaying||!sequence.length)return;
  isPlaying=true;
  stopRequested=false;
  document.getElementById('playBtn').style.display='none';
  document.getElementById('stopBtn').style.display='inline-flex';
  document.getElementById('progressBar').classList.add('active');
  const logEl=document.getElementById('runLog');
  logEl.style.display='block';
  logEl.innerHTML='';

  do{
    for(let i=0;i<sequence.length;i++){
      if(stopRequested)break;
      const s=sequence[i];
      const pct=((i+1)/sequence.length*100).toFixed(1);
      document.getElementById('progressFill').style.width=pct+'%';

      // Highlight current
      const seqEl=document.getElementById('seq-'+i);
      if(seqEl)seqEl.classList.add('playing');

      // Send IR
      let success=false;
      try{
        const r=await fetch('/api/send',{method:'POST',headers:{'Content-Type':'application/json'},
          body:JSON.stringify({protocol:s.protocol,code:s.code,bits:s.bits})});
        const d=await r.json();
        success=d.success;
      }catch(e){success=false;}

      // Log
      const entry=document.createElement('div');
      entry.className='log-entry';
      entry.innerHTML=`<span class="log-step">#${i+1}</span><span class="log-name">${getIcon(s.name)} ${s.name}</span><span class="log-status ${success?'ok':'fail'}">${success?'Sent':'Failed'}</span>`;
      logEl.appendChild(entry);
      logEl.scrollTop=logEl.scrollHeight;

      // Animate
      if(seqEl){seqEl.classList.remove('playing');seqEl.classList.add('played');}

      // Wait for delay (unless last step and not looping)
      if(i<sequence.length-1||loopMode){
        await sleep(s.delay);
      }
    }
    // Reset played states for loop
    if(loopMode&&!stopRequested){
      document.querySelectorAll('.seq-item.played').forEach(e=>e.classList.remove('played'));
    }
  }while(loopMode&&!stopRequested);

  finishPlayback();
}

function stopSequence(){
  stopRequested=true;
}

function finishPlayback(){
  isPlaying=false;
  document.getElementById('playBtn').style.display='inline-flex';
  document.getElementById('stopBtn').style.display='none';
  document.getElementById('progressFill').style.width='100%';
  document.querySelectorAll('.seq-item.playing,.seq-item.played').forEach(e=>{
    e.classList.remove('playing','played');
  });
  setTimeout(()=>{
    document.getElementById('progressBar').classList.remove('active');
    document.getElementById('progressFill').style.width='0%';
  },800);
}

function toggleLoop(){
  loopMode=!loopMode;
  const btn=document.getElementById('loopBtn');
  btn.classList.toggle('active',loopMode);
  btn.innerHTML=loopMode?'\u{1F501} Loop ON':'\u{1F501} Loop';
}

function sleep(ms){return new Promise(r=>setTimeout(r,ms));}

// Save / Load macros (localStorage)
function saveMacro(){
  const nameEl=document.getElementById('macroName');
  const name=nameEl.value.trim();
  if(!name){nameEl.focus();return;}
  if(!sequence.length){alert('Build a sequence first');return;}
  const macros=JSON.parse(localStorage.getItem('ir_macros')||'[]');
  // Check for duplicate name
  const existIdx=macros.findIndex(m=>m.name===name);
  if(existIdx>=0){
    if(!confirm('Overwrite existing macro "'+name+'"?'))return;
    macros[existIdx]={name:name,steps:JSON.parse(JSON.stringify(sequence)),created:Date.now()};
  }else{
    macros.push({name:name,steps:JSON.parse(JSON.stringify(sequence)),created:Date.now()});
  }
  localStorage.setItem('ir_macros',JSON.stringify(macros));
  nameEl.value='';
  renderSavedMacros();
}

function loadMacro(idx){
  if(isPlaying)return;
  const macros=JSON.parse(localStorage.getItem('ir_macros')||'[]');
  if(!macros[idx])return;
  sequence=JSON.parse(JSON.stringify(macros[idx].steps));
  renderSequence();
  updatePlayBtn();
}

function deleteMacro(idx){
  const macros=JSON.parse(localStorage.getItem('ir_macros')||'[]');
  if(!macros[idx])return;
  if(!confirm('Delete macro "'+macros[idx].name+'"?'))return;
  macros.splice(idx,1);
  localStorage.setItem('ir_macros',JSON.stringify(macros));
  renderSavedMacros();
}

function renderSavedMacros(){
  const macros=JSON.parse(localStorage.getItem('ir_macros')||'[]');
  const el=document.getElementById('savedMacros');
  if(!macros.length){
    el.innerHTML='<div class="empty-msg">No saved macros yet</div>';
    return;
  }
  el.innerHTML=macros.map((m,i)=>{
    const stepCount=m.steps.length;
    const totalDelay=m.steps.reduce((a,s)=>a+s.delay,0);
    return `
      <div class="saved-macro">
        <div class="macro-info">
          <div class="macro-name">\u{1F3AC} ${m.name}</div>
          <div class="macro-meta">${stepCount} steps &bull; ~${(totalDelay/1000).toFixed(1)}s total delay</div>
        </div>
        <div class="macro-actions">
          <button class="load-btn" onclick="loadMacro(${i})">Load</button>
          <button class="del-btn" onclick="deleteMacro(${i})">Delete</button>
        </div>
      </div>`;
  }).join('');
}

// Apply global delay to all steps
document.getElementById('globalDelay').addEventListener('change',function(){
  const d=parseInt(this.value)||500;
  sequence.forEach(s=>s.delay=d);
  renderSequence();
});

// Init
loadButtons();
renderSavedMacros();
</script>
</body>
</html>
)rawliteral";

#endif
