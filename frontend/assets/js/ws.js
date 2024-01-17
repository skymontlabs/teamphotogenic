// Assuming `ws` is your WebSocket object
var ws = new WebSocket('ws://your-websocket-url');

// Set the binary data type to arraybuffer for easier handling
ws.binaryType = 'arraybuffer';

// Define the onmessage event handler
ws.onmessage = function(event) {
    // Check if the received data is binary
    if (event.data instanceof ArrayBuffer) {
        // Create a new DataView for the ArrayBuffer
        var dataView = new DataView(event.data);

        // Process the binary data
        // For example, reading the first 32-bit integer from the buffer
        var firstInt = dataView.getInt32(0);

        console.log("Received binary data: First 32-bit integer is " + firstInt);

        // Add more processing as needed, depending on your data structure
    } else {
        // Handle non-binary message (optional)
        console.log("Received non-binary message:", event.data);
    }
};

// Error handling
ws.onerror = function(error) {
    console.error("WebSocket Error:", error);
};

// Open the WebSocket connection
ws.onopen = function(event) {
    console.log("WebSocket connection established");
};

function readMessage() {
	switch (m) {
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}
}


function getSeed(dview) {
	//seed = 
	// show password if needed,
}


function endTest() {

}

function resTest() {

}

