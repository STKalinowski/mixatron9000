"use strict";

var fs   = require('fs');
var socketio = require('socket.io');
var io;

var dgram = require('dgram');
var PORT = 12345;
var HOST = '192.168.7.2';
var client;

exports.listen = function(server) {
	io = socketio.listen(server);
	io.set('log level 1');

	io.sockets.on('connection', function(socket) {
		handleCommand(socket);
	});
};

function handleCommand(socket) {
	// Pased string of comamnd to relay
	socket.on('mixatron', function(data) {
		// Info for connecting to the local process via UDP
		var buffer = new Buffer(data);

		var client = dgram.createSocket('udp4');
		client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
			if (err) 
				throw err;
		});

		client.on('listening', function () {
			var address = client.address();
		});

		// Handle an incoming message over the UDP from the local application.
		client.on('message', function (message, remote) {
			var reply = message.toString('utf8')
			reply = reply.split(" ");
			const command = {
				action: reply[1],
				payload: reply[2]
			}
			socket.emit('commandReply', command);
		});

		client.on("UDP Client: close", function() {
			client.close();
			console.log("closed");
		});
		client.on("UDP Client: error", function(err) {
			console.log("error: ",err);
		});
	});
};