// WebSocket setup with reconnection
let ws;
let reconnectInterval = 1000; // Time to wait before attempting to reconnect
const websocketOutputDiv = document.getElementById('websocket-output');

function connectWebSocket() {
  ws = new WebSocket(`ws://${window.location.hostname}/ws`);

  ws.addEventListener('open', () => printMessage('Connected.'));
  ws.addEventListener('error', e => printMessage(`Error: ${e.message}`));
  ws.addEventListener('message', e => processMessage(e.data));
  ws.addEventListener('close', e => {
    printMessage(`Closed. Code=${e.code}, Reason=${e.reason}`);
    setTimeout(connectWebSocket, reconnectInterval); // Attempt to reconnect
  });
}

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

function ansiToHtml(text) {
  return text
    .replace(/\033\[34m/g, '<span style="color: blue;">') // Blue for DEBUG
    .replace(/\033\[32m/g, '<span style="color: green;">') // Green for INFO
    .replace(/\033\[33m/g, '<span style="color: yellow;">') // Yellow for WARN
    .replace(/\033\[31m/g, '<span style="color: red;">') // Red for ERROR
    .replace(/\033\[0m/g, '</span>'); // Reset to default color
}

function printMessage(message) {
  const newMessage = document.createElement('p');
  const htmlMessage = ansiToHtml(message); // Convert ANSI codes to HTML
  newMessage.innerHTML = htmlMessage; // Use innerHTML since we're now working with HTML content
  websocketOutputDiv.appendChild(newMessage);

  // Scroll to the new message
  websocketOutputDiv.scrollTop = websocketOutputDiv.scrollHeight;
}

function isJSON(str) {
  try {
    JSON.parse(str);
    return true;
  } catch {
    return false;
  }
}

document.addEventListener('DOMContentLoaded', function () {
  const inputElement = document.getElementById('input');
  inputElement.addEventListener('keypress', function (e) {
    if (e.key === 'Enter') {
      e.preventDefault(); // Prevent the default action to stop from submitting
      sendMessage();
    }
  });
});

function sendMessage() {
  const message = document.getElementById('input').value;
  if (message.trim() !== '') { // Check if message is not just whitespace
    ws.send(message);
    printMessage(`Sent: ${message}`);
    document.getElementById('input').value = ''; // Clear the input after sending
  }
}

function setDeviceValues() {
  const voltage = document.getElementById('setVoltage').value;
  const current = document.getElementById('setCurrent').value;
  const payload = {};

  if (voltage) payload.voltage = parseFloat(voltage);
  if (current) payload.current = parseFloat(current);

  if (Object.keys(payload).length > 0) {
    ws.send(JSON.stringify(payload));
    printMessage(`Sent values: ${JSON.stringify(payload)}`);
  } else {
    printMessage('No values to set.');
  }
}

// Initialize WebSocket connection
connectWebSocket();
