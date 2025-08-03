outlets = 8;

var knobValues = [0, 0, 0, 0];

function Button() {
	outlet(7, "bang");
}

function Rotary(v) {
	var values = arrayfromargs(arguments);
	
	outlet(values[0] - 1, values[1]);
}

function Angle(v) {
	var values = arrayfromargs(arguments);
	outlet(4, values[0]);
	outlet(5, values[1]);
	outlet(6, values[2]);
}