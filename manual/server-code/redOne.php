<?php
			
	sleep(20);
	
	$fp = @fopen('output.txt', 'r');
		
    // Add each line to an array
    if ($fp) {
       $array = explode("\n", fread($fp, filesize('output.txt')));
    }

    foreach ($array as $value) {
    	if ( $value == "true" ) {
    	
			$file = fopen("led.json", "w") or die("can't open file");
			fwrite($file, '{"ledState": "one"}');
			fclose($file);
			
			file_get_contents('http://martijnnieuwenhuizen.nl/get-up-stand-up/redTwo.php');
        	
    	}
        	
    }

?>