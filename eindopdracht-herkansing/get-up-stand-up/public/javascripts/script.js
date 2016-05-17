function apiCall(url) {

	return new Promise(function(resolve, reject) { // Resolve = .then / Reject = .catch;

		var request = new XMLHttpRequest();

		request.onloadend = function(response) {

			resolve(request.response);

		}

		request.onerror = reject;

		request.open('GET', url, true);
		request.send();

	});

}
function postCall(url) {

	var request = new XMLHttpRequest();
	request.open('POST', url, true);
	request.send();

}

var ledStatePath = 'http://localhost:3000/data/ledState.json';
var historyPath = 'http://localhost:3000/data/history.json';
var settingPath = 'http://localhost:3000/data/setting.json';
var lastChangePath = 'http://localhost:3000/data/ledStatus.json';

function getState() {
	apiCall(ledStatePath).then(function(res) {
		
		var data = JSON.parse(res);
		var checker = false;

		if ( data.ledState == "blink" ) {

			checker = true;

			postCall('http://localhost:3000/active');
			var minHtml = document.querySelector('.working-minutes');
			document.querySelector('.message').classList.add('work');
			document.querySelector('.message').classList.remove('chill');
			
			var counter = setInterval(function() {
				var amount = minHtml.innerHTML;
				minHtml.innerHTML = Number(amount) + 1;
			}, 60000);

			document.querySelector('.workingStatus').innerHTML = "working";

			apiCall(settingPath).then(function(res) {

				var setting = JSON.parse(res);
				var settingNumber = Number(setting.setting);
				var settingNumberSec = (settingNumber * 60) * 1000;
				var stateOne = settingNumberSec / 3
				var stateTwo = settingNumberSec * 2;
				var stateThree = settingNumberSec;

				// var intOne = setInterval

				setTimeout(function() {
					if ( checker = true ) {
						postCall('http://localhost:3000/stateOne');
					}
				}, stateOne);

				setTimeout(function() {
					if ( checker = true ) {
						postCall('http://localhost:3000/stateTwo');
					}
				}, stateTwo);

				setTimeout(function() {
					if ( checker = true ) {
						postCall('http://localhost:3000/stateThree');
					}
				}, stateThree);

			})

		} else if ( data.ledState == "one" || data.ledState == "two" || data.ledState == "three" ) {
			document.querySelector('.workingStatus').innerHTML = "working";
			document.querySelector('.working-minutes').innerHTML = "?";
			document.querySelector('.message').classList.add('work');
			document.querySelector('.message').classList.remove('chill');
		} else {
			clearInterval(counter);
			checker = false;
			document.querySelector('.working-minutes').innerHTML = "?";
			document.querySelector('.workingStatus').innerHTML = "pausing";
			document.querySelector('.message').classList.add('chill');
			document.querySelector('.message').classList.remove('work');
		}

	});	
}

function loadChart() {

    google.charts.load('current', {'packages':['corechart']});
    google.charts.setOnLoadCallback(renderChart);

}

function renderChart() {

	apiCall(historyPath).then(function(res) {
		
		var renderedData = JSON.parse(res);
		var latestTwentyData = res;
		if (renderedData.length > 40 ) {
			latestTwentyData = renderedData.slice(renderedData.length - 40, renderedData.length);	
		}
		
		var historyData = [["Element", "Workingtime", { role: "style" } ]];

		apiCall(settingPath).then(function(res) {
			var userSetting = JSON.parse(res);

			latestTwentyData.forEach(function(item) {
				
				if (item.status == "sitting") {
					var color = "#80EF91";

					if ( item.duration > userSetting.setting ) {
						color = "#F38181";				
					}

					var single = [item.time, item.duration, color];
					historyData.push(single);
				}
				
			});

			var data = google.visualization.arrayToDataTable(historyData);
		    var view = new google.visualization.DataView(data);
		    view.setColumns([0, 1,
		   		{ calc: "stringify",
		     	sourceColumn: 1,
		     	type: "string",
		     	role: "annotation" },
		   		2]);

		    var options = {
		        title: "Your work-time history",
		        width: 1100,
		        height: 500,
		        bar: {groupWidth: "80%"},
		        legend: { position: "none" },
		    };

			var chart = new google.visualization.ColumnChart(document.getElementById('historyg'));
			chart.draw(data, options);
		})
		
	});	

}

function pushUserSettings(e) {

	// get the amount filed in by the user
	var amount = document.querySelector('input[type=number]').value;
	// create the url with amount as query
	var url = "http://localhost:3000/setting" + "?amount=" + amount;
	// make the call
	postCall(url);

	// Show Message
	alert("Work time changed to " + amount);

	toggleMenu();

	e.preventDefault();

}

function setValue() {

	apiCall(settingPath).then(function(res) {
		var data = JSON.parse(res);
		document.querySelector('input[type=number]').value = data.setting;
	});

}

function toggleDeviceState() {

	var status = document.querySelector('.on-off input');
	var innerStatus = document.querySelector('.status');
	
	var toggleUrl;

	if ( status.checked ) {
		toggleUrl = "http://localhost:3000/on";
		innerStatus.innerHTML = "On";
		document.querySelector('main').classList.remove("overlay");
	} else {
		toggleUrl = "http://localhost:3000/off";
		innerStatus.innerHTML = "Off";
		document.querySelector('main').classList.add("overlay");
	}

	postCall(toggleUrl);
}

function toggleMenu() {
	var dropdown = document.querySelector('.settings');
	dropdown.classList.toggle('dropdown');
}

function setEventListeners() {
	var submitButton = document.querySelector('input[type=submit]');
	submitButton.addEventListener('click', pushUserSettings, false);

	var onOffSwitchL = document.querySelector('.on-off label');
	var onOffSwitchI = document.querySelector('.on-off input');
	onOffSwitchL.addEventListener('click', toggleDeviceState, false);
	onOffSwitchI.addEventListener('click', toggleDeviceState, false);

	var settingsButton = document.querySelector('header button');
	settingsButton.addEventListener('click', toggleMenu, false);	
}

function loopTheCalls() {

	var lastChange;

	apiCall(lastChangePath).then(function(res) {
		lastChange = res;
	});

	setInterval(function() {

		apiCall(lastChangePath).then(function(res) {

			if ( res != lastChange ) {

				getState();
				google.charts.setOnLoadCallback(renderChart);
				lastChange = res;

			}

		});
			
	}, 5000);
}

setValue();
loadChart();
getState();
setEventListeners();
loopTheCalls();


// Turn the Application Off!
