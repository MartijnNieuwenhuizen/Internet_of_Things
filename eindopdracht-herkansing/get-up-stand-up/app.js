var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var fs = require('file-system');

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

// React a post on the "/"
app.post('/', function (req, res) {

  // init
  var statusData;
  var historyData;
  var postData = Object.keys(req.body)[0]; // data from the ESP
  // var postData = "standing"; // data from the ESP
  var statusPath = "./public/data/ledStatus.json"; // path to the ledStatus.json
  var historyPath = "./public/data/history.json"; // path to the history.json

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
      console.log(statusData);
    } else {

      readFile(historyPath, function (err, gotHistoryData) {
        if (err) { 
          console.log(err); 
        }
        historyData = JSON.parse(gotHistoryData);
        var newInsert = {
          status: postData,
          time: timeNow,
          date: dateNow
        }
        console.log(historyData.length);
        historyData.push(newInsert);
        console.log(historyData.length);
      
        statusData[0].status = postData;
        statusData[0].time = timeNow;
        statusData[0].date = dateNow;

        // Write the new data
        var writeStatusData = JSON.stringify(statusData);
        writeFile(statusPath, writeStatusData);

        var writeHistoryData = JSON.stringify(historyData);
        writeFile(historyPath, writeHistoryData);

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
