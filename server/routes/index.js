var express = require('express');
var router = express.Router();

var status = true;

/* GET home page. */
router.get('/', function(req, res, next) {
  	res.render('index', { title: 'Express' });
  	// buttons add
});

router.get('/data', function(req, res, next) {

  	res.send(status);

});

router.post('/', function(req, res, next) {
	
	var light = req.body.light;
	// render template
	res.send();

});

module.exports = router;
