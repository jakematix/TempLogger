<?php

	function Connection(){
		$server="server_adderss";
		$user="user_name";
		$pass="password";
		$db="environment_data";
	   	
		$connection = mysql_connect($server, $user, $pass);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}
		
		mysql_select_db($db) or die( 'MySQL ERROR: '. mysql_error() );

		return $connection;
	}
?>
