<?php
   include("connect.php");
   	
   $link=Connection();

	if (isset($_GET["temp1"])) {
		$temp=$_GET["temp1"];
	}

	if (isset($_GET["hum1"])) {
		$hum=$_GET["hum1"];
	}

	if (isset($_GET["heat1"])) {
		$heat=$_GET["heat1"];
	}

	//$temp=25.23;
	//$hum=42.15;
	//$heat=28.12;
	$query = "INSERT INTO temperature_values (temperature, humidity, heat_index) 
		VALUES (".$temp.",".$hum.",".$heat.")"; 
   	
   	mysql_query($query,$link);
		mysql_close($link);

   	// header("Location: index.php");
?>
