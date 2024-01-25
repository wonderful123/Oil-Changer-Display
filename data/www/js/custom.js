// WebSocket setup
const ws = new WebSocket(`ws://${window.location.hostname}/ws`);
const outputDiv = document.getElementById('output');

ws.addEventListener('open', () => printMessage('Connected.'));
ws.addEventListener('error', e => printMessage(`Error: ${e}`));
ws.addEventListener('message', e => processMessage(e.data));
ws.addEventListener('close', e => printMessage(`Closed. Code=${e.code}, Reason=${e.reason}`));

function processMessage(data) {
  if (isJSON(data)) {
    const payload = JSON.parse(data);
    if ('current' in payload && 'voltage' in payload) {
      document.getElementById('currentValue').textContent = payload.current;
      document.getElementById('voltageValue').textContent = payload.voltage;
    }
  } else {
    printMessage(`Received: ${data}`);
  }
}

function printMessage(message) {
  const newMessage = document.createElement('p');
  newMessage.textContent = message;
  outputDiv.appendChild(newMessage);
}

function isJSON(str) {
  try { JSON.parse(str); return true; } catch { return false; }
}

function sendMessage() {
  const message = document.getElementById('input').value;
  ws.send(message);
  printMessage(`Sent: ${message}`);
}

function setDeviceValues() {
  const voltage = document.getElementById('setVoltage').value;
  const current = document.getElementById('setCurrent').value;
  const payload = {};

  if (voltage) payload.setVoltage = parseFloat(voltage);
  if (current) payload.setCurrent = parseFloat(current);

  if (Object.keys(payload).length > 0) {
    ws.send(JSON.stringify(payload));
    printMessage(`Sent values: ${JSON.stringify(payload)}`);
  } else {
    printMessage('No values to set.');
  }
}
