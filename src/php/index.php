







<?php
header('Access-Control-Allow-Origin: *');
?>
<?php
$light = $_GET['light'];
if($light == "blue") {
  $file = fopen("light.json", "w") or die("can't open file");
  fwrite($file, '{"light": "blue"}');
  fclose($file);
} 
else if ($light == "red") {
  $file = fopen("light.json", "w") or die("can't open file");
  fwrite($file, '{"light": "red"}');
  fclose($file);
}
else if ($light == "green") {
  $file = fopen("light.json", "w") or die("can't open file");
  fwrite($file, '{"light": "green"}');
  fclose($file);
}



?>




<html>
  <head>      
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <title>LED for ESP8266</title>
   
    <link rel="stylesheet" href="style.css">

  </head>
  <body>
    <section>
      <h2>Martijn</h2>
      <a href="?light=red" class="">Turn red</a>
      <a href="?light=green" class="">Turn green</a>
      <a href="?light=blue" class="">Turn blue</a>
    </section>

    <section>
      <h2>Dylan</h2>
      <a href="http://dylanvens.com/iot/?light=on" class="d_on">Turn On</a>
      <a href="http://dylanvens.com/iot/?light=off" class="d_off">Turn Off</a>
    </section>

    <section>
      <h2>Raymond</h2>
      <a href="http://raymondkorrel.nl/iot/index.php?light=on" class="r_on">Turn On</a>
      <a href="http://raymondkorrel.nl/iot/index.php?light=off" class="r_off">Turn Off</a>
    </section>
      

      <?php 
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      // Waarde wegschrijven naar bestand
      $data = $_POST["light"];

      // Push data to text file
      file_put_contents("output.txt", $data . "\n", FILE_APPEND);

    } else  {
        // Open the file
        $fp = @fopen('output.txt', 'r');

        // Add each line to an array
        if ($fp) {
           $array = explode("\n", fread($fp, filesize('output.txt')));
        }

        foreach ($array as $value) {
            ?> <p class="bar"> <?php echo $value; ?></p> <?php
        };
    }
?>
        
  </body>
  <script>
    (function(){

    'use strict';

    function Loader() {

        var _this = this;

        _this.load = function(method, url, data, contentType) {

            return new Promise(function(resolve, reject) {

                var xhr = new XMLHttpRequest();
                xhr.open(method, url, true);

                xhr.onload = function() {

                    if (this.status >= 200 && this.status < 300) {
                        
                        resolve(JSON.parse(xhr.response));
                    
                    } else {
                        
                        var error = {
                            status: this.status,
                            message: xhr.statusText
                        };

                        reject(error);    
                    }

                }    

                xhr.send();
            
            });

        }

    }

    window.Loader = Loader;

}());
  </script>
  <script>
    var dOn = document.querySelector('.d_on');
    var dOff = document.querySelector('.d_off');
    var rOn = document.querySelector('.r_on');
    var rOff = document.querySelector('.r_off');

    
    function changeState(e) {
      e.preventDefault();
      var _url = e.target.href;

      var _buttonLoader = new Loader();

      _buttonLoader.load('GET', _url);

    }

    dOn.addEventListener('click', changeState, true);
    dOff.addEventListener('click', changeState, true);
    rOn.addEventListener('click', changeState, true);
    rOff.addEventListener('click', changeState, true);



  </script>

</html>