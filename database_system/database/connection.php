<?php
$server = "localhost";
$username = "root";
$password = "hermanudin";
$database = "proyek_akhir";
$conn = @mysql_connect($server,$username,$password) or die("Epic Fail on Connection");
mysql_query("SET NAMES 'utf8'");
mysql_select_db($database, $conn) or die("There are no such thing as the database");
?>
