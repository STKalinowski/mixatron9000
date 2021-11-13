"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();
$(document).ready(function() {
	sendCommand("get_mix");

	// // sendCommand drinks are defined in udp.h
	$('#modeNone').click(function(){
		sendCommand("pump_none");
	});
	$('#modeDrink1').click(function(){
		sendCommand("pump_drink1");
	});
	$('#modeDrink2').click(function(){
		sendCommand("pump_drink2");
	});
	$('#modeDrink3').click(function(){
		sendCommand("pump_drink3");
	});
	$('#modeDrink4').click(function(){
		sendCommand("pump_drink4");
	});

	socket.on('commandReply', function(result) {
		handleCommand(result);
		var newDiv = $('<div></div>').text(result);
		$('#messages').append(newDiv);
		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
	});
	
});

function sendCommand(message) {
	socket.emit('mixatron', message);
};

function handleCommand(command) {
	switch(command.action) {
		case "mix":
			$('#modeid').text(command.payload);
			break;
	}
}

