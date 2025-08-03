outlets = 7;


var knobValues = [0, 0, 0, 0];

function Rotary(v) {
	var values = arrayfromargs(arguments);
	
	//post(values);
	
	/*var knobIndex = values[0] - 1;
	var newVal = values[1];
	var oldVal = knobValues[knobIndex];*/
	
	
	outlet(values[0] - 1, values[1]);
	/*if (newVal > oldVal) {
		outlet(knobIndex, "inc");
		knobValues[knobIndex] = newVal;
		return;
	} 
	if (newVal < oldVal) {
		outlet(knobIndex, "dec");
		knobValues[knobIndex] = newVal;
		return;
	} */
	
}

function Angle(v) {
	var values = arrayfromargs(arguments);
	outlet(4, values[0]);
	outlet(5, values[1]);
	outlet(6, values[2]);
}