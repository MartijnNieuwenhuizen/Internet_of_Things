var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var fs = require('file-system');
var timeout = require('connect-timeout');
var router = express.Router();

var routes = require('./routes/index');
var users = require('./routes/users');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', routes);
app.use('/users', users);
app.use('/users', routes);

// The post requests for the Led States
var ESPPath = "./public/data/ledState.json";
var settingPath = "./public/data/setting.json";
var togglePath = "./public/data/toggle.json";

function writeFile(filename, data) {
  fs.writeFile(filename, data);
}
app.post('/active', function(req, res) {
  
  var espData = '{"ledState":"false"}';
  writeFile(ESPPath, espData);

});
app.post('/stateOne', function(req, res) {
  
  var espData = '{"ledState":"one"}';
  writeFile(ESPPath, espData);

});
app.post('/stateTwo', function(req, res) {
  
  var espData = '{"ledState":"two"}';
  writeFile(ESPPath, espData);

});
app.post('/stateThree', function(req, res) {
  
  var espData = '{"ledState":"three"}';
  writeFile(ESPPath, espData);

});

app.post('/on', function(req, res) {
  
  var toggle = '{"status":"on"}';
  writeFile(togglePath, toggle);

  var espData = '{"ledState":"false"}';
  writeFile(ESPPath, espData);

});
app.post('/off', function(req, res) {
  
  var toggle = '{"status":"off"}';
  writeFile(togglePath, toggle);

  var espData = '{"ledState":"off"}';
  writeFile(ESPPath, espData);

});

// POST request for the user settings
app.post('/setting', function(req, res) {
  
  var receivedData = req._parsedUrl.query;
  var amount = receivedData.slice(receivedData.indexOf("=")+1, receivedData.length);
  var sendData = {
    "setting": amount
  }

  writeFile(settingPath, JSON.stringify(sendData));

});

// React a post on the "/"
app.post('/', function (req, res) {

  // init
  var statusData;
  var historyData;
  var postData = Object.keys(req.body)[0]; // data from the ESP
  // var postData = "standing"; // data from the ESP
  var statusPath = "./public/data/ledStatus.json"; // path to the ledStatus.json
  var historyPath = "./public/data/history.json"; // path to the history.json
  var ESPPath = "./public/data/ledState.json"; // path to the ledState (false, blink, ledOne, ledTwo, ledThree)
  var settingPath = "./public/data/setting.json"; // path to the set user setting (default is 90)

  // function to read a file
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
  // function to write a file
  function writeFile(filename, data) {
    fs.writeFile(filename, data);
  }

  // Action
  // Call the read file function
  readFile(statusPath, function (err, gotStatusData) {
    if (err) { 
      console.log(err); 
    }

    // Get the time
    var d = new Date();
    var timeNow = d.getHours() + ":" + d.getMinutes();
    var dateNow = d.getFullYear() + "/" + d.getMonth()+1 + "/" + d.getDate();

    // Get the data
    statusData = JSON.parse(gotStatusData);
    if ( postData == statusData[0].status ) {

      // Don't know if shomething needs to happen!
      // Let the loop of the Led run! --> But only Once!!!!


    } else {

      readFile(historyPath, function (err, gotHistoryData) {
        if (err) { 
          console.log(err); 
        }
        historyData = JSON.parse(gotHistoryData);

        var oldTime = statusData[0].dataCalc;
        var newTime = Date.parse(d);

        // Calculate the time between the change in minutes
        var newHour = timeNow.slice(0, 2);
        var newMin = timeNow.slice(3, 5);
        var oldHour = statusData[0].time.slice(0, 2);
        var oldMin = statusData[0].time.slice(3, 5);
        var differanceInMin = ((newHour - oldHour) * 60) + (newMin - oldMin);

        // check if the time you worked was longer than the maximum time, set by the user
        readFile(settingPath, function (err, setting) {
          if (err) { 
            console.log(err); 
          }
          
          var userDiff = JSON.parse(setting);
          var durToLong = false;

          if ( differanceInMin > setting.setting ) {
            durToLong = true;
          }

          var newInsert = {
            status: postData,
            time: timeNow,
            date: dateNow,
            duration: differanceInMin,
            toLong: durToLong
          }

          historyData.push(newInsert);
          
          statusData[0].status = postData;
          statusData[0].time = timeNow;
          statusData[0].date = dateNow;

          // Write the new data
          var writeStatusData = JSON.stringify(statusData);
          writeFile(statusPath, writeStatusData);

          var writeHistoryData = JSON.stringify(historyData);
          writeFile(historyPath, writeHistoryData);

          if ( postData == "sitting" ) {

            var espData = '{"ledState":"blink"}';
            writeFile(ESPPath, espData);
          
          } else {
            var espData = '{"ledState":"false"}';
            writeFile(ESPPath, espData);
          }

        });

      });

    }

  });

  res.send('Got a POST request');

});

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  var err = new Error('Not Found');
  err.status = 404;
  next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
  app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
      message: err.message,
      error: err
    });
  });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
  res.status(err.status || 500);
  res.render('error', {
    message: err.message,
    error: {}
  });
});


module.exports = app;
