<?php
			
	sleep(60);
	
	$fp = @fopen('output.txt', 'r');
		
    if ($fp) {
       $array = explode("\n", fread($fp, filesize('output.txt')));
    }

    foreach ($array as $value) {
    	if ( $value == "true" ) {
    	
			$file = fopen("led.json", "w") or die("can't open file");
			fwrite($file, '{"ledState": "three"}');
			fclose($file);
        	
    	}	
    }

?>