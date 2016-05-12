var express = require('express');
var fs = require('file-system');
var router = express.Router();

function readFile(filename, callback) {
  	fs.readFile(filename, function (err, data) {
    	if(err) {
      		callback(err);
      		return;
    	}
    	try {
      		callback(null, data);
    	} catch(exception) {
      		callback(exception);
    	}
  	});
}

/* GET home page. */
router.get('/', function(req, res, next) {

	var historyData;
	var filePath = "public/data/history.json";

	readFile(filePath, function (err, data) {
	  	if (err) { 
	  		console.log(err); 
	  	}

	  	// Get Data
	  	historyData = JSON.parse(data);

	  	// Render Template
	  	res.render('index', { title: 'Get-up Stand-up' });

	});

});

module.exports = router;
