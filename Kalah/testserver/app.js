var net = require('net');
var process = require('process');

var client = new net.Socket();
var counter = 0;

var timewatcher;

function post() {
  client.write(counter.toString());
}

function sendMessage(msg) {
  client.write(msg);
  clearTimeout();
}

client.on('data', function(data) {
  var lines = data.toString().split('\n');
  for(line_idx in lines) {
    var line = lines[line_idx];
    if(!line) continue;
    console.log('[SERVER MESSAGE] ' + line);
    if(line.toString().includes('INFO')) {
        client.write('READY\n');
    }

    var patt = /^(\d+\s+)*\d+|P$/;
    var res = patt.exec(line.toString().trim());
    if(res) {
      client.write('OK\n');
    }

    if((line.toString().includes('INFO') && line.split(" ")[4] == 'F') || res) {
      console.log("Please enter your moves:");
    } else if(line.toString().includes('WINNER') || line.toString().includes("LOSER")) {
      console.log('GAME OVER');
      clearTimeout(timewatcher);
      client.destroy();
    }
  }
});

client.on('close', function() {
	console.log('Connection closed');
  client.destroy();
  process.exit();
});

client.on('broadcast', function(data) {
  console.log('Received broadcasted message: ' + data);
});

client.connect(5000, '127.0.0.1', function() {
	console.log('Connected');
});

process.stdin.resume();
process.stdin.setEncoding('utf8');
var util = require('util');

process.stdin.on('data', function (text) {
  //console.log('received data:', util.inspect(text));
  client.write(text);
  if (text === 'quit\n') {
    done();
  }
});

function done() {
  console.log('Now that process.stdin is paused, there is nothing more to do.');
  process.exit();
}
