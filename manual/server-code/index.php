<?php

// Parts of the code from http://blog.nyl.io/esp8266-led-arduino/
	
	$counterSet = false;

	if ($_SERVER['REQUEST_METHOD'] === 'POST') {
			
		// init
	    $data = $_POST["sitting"];
	    $file = fopen("data.json", "w") or die("can't open file");
	    file_put_contents("output.txt", $data . "\n");
	
		if ($data == "true"){
				
			if ( $counterSet === true ) {
	        		
				fwrite($file, '{"sitting": "true"}');
				fclose($file);
	        	
	        } else {	
		        	
				fwrite($file, '{"sitting": "true"}');
				fclose($file);
		
				file_get_contents('http://martijnnieuwenhuizen.nl/get-up-stand-up/redOne.php');	
				
				$counterSet === true;
		        	
	        }
		
		} else if ($data == "false") {
		
			// Set All lights to green
			fwrite($file, '{"sitting": "false"}');
			fclose($file);
			
			$file = fopen("led.json", "w") or die("can't open file");
			fwrite($file, '{"ledState": "false"}');
			fclose($file);
			
		}
	
	}

?>

<html>
  <head>      
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <title>Get Up Stand Up</title>
   
    <link rel="stylesheet" href="style.css">

  </head>
  <body>
  
		<?php 
			// Open the file
			$fp = @fopen('output.txt', 'r');
			$title = "Get up Stand Up";
		
	        // Add each line to an array
	        if ($fp) {
	           $array = explode("\n", fread($fp, filesize('output.txt')));
	        }
	
	        foreach ($array as $value) {
	        	if ( $value == "true" ) {
	        	
	        		$status = "Sitting";
		        	
	        	} else if ( $value == "false" ) {
		        	
					$status = "Standing";		        	
		        	
	        	}
	    
	        };

		?>
		
		<header>
			<h1><?php echo $title ?></h1>			
		</header>
		
		<main>
			
			<?php  if ($status == "Sitting") { ?>
				
				<h2>You Go!</h2>	
				<p>Just take a break in <span class="counter-down">60</span> minutes</p>
				
			<?php } else  { ?>
				
				<h2>Movement is always better than Work!</h2>
				<p>You're heaving a break for <span class="counter-up">0</span> minutes</p>
				
			<?php } ?>
			
		</main>
		
		<script src="script.js"></script>	
	               
  </body>
</html>

// Settings dynamisch maken

Historty in de interface