var countDown = document.querySelector(".counter-down");
var countUp = document.querySelector(".counter-up");
var count;

if ( countUp ) {

	count = 0;

	setInterval(function() {
		count = count +1;
		countUp.innerHTML = count;
	}, 1000);
	
}
if ( countDown ) {
	
	count = 60;

	setInterval(function() {
		count = count - 1;
		countDown.innerHTML = count;
	}, 1000);
	
}