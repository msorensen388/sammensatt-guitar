

// the value here doesnt matter, only to skip every other message
var value = 0;


function anything() {
	
	var a = arrayfromargs(messagename, arguments);
	value++;
	
	
	// make sure we never hit the int max
	if (value == 100) {
		value = 0;
	}
	
	post(value);
		
	if (value % 2 === 0) {
		post(a[0]);
		outlet(0, a[0]);
	}
	
}
