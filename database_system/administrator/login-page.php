<?php
ob_start();
session_start();


include "../database/connection.php";

$password = sha1(md5($_POST[password]));
$salt = "bYU1hg32fclr" ;
$pass = md5($salt.$password);
$id_user = $_POST[id_user];
$login=mysql_query("SELECT * FROM user WHERE id_user='$id_user' AND password='$pass'");
$find=mysql_num_rows($login);
$o=mysql_fetch_array($login);
 
 
echo "<html> 
<head> 
	<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' /> 
	<title>Administration Panel</title> 
<link rel='stylesheet' id='login-css'  href='css/login.css' type='text/css' media='all' />

</head> 
<body class='login'> 
<div id='login'><h1><a href='#'><span>Administration Panel</span></a></h1> ";


if ($_GET['userLogin'] == 'false'){
	echo ("<center><font color=\"red\"><h2>Salah Password dan atau Username!</h2></font><br></center>");
	}


echo "
<form method=\"POST\" action=\"login.php\">
	<p> 
		<label>Username<br> 
		<input type='text' name='id_user' id='user_login' class='input' value='' size='20' tabindex='10' /></label> 
	</p> 
	<p> 
		<label>Password<br> 
		<input type='password' name='password' id='user_pass' class='input' value='' size='20' tabindex='20'></label> 
	</p> 
	<p class='forgetmenot'><label>Don't Forget to Logout</label></p> 
	<p class='submit'> 
		<input type='submit' name='submit' id='submit' class='button-primary' value='Log In' tabindex='100'> 
	</p> 
	<input type=\"hidden\" name=\"acs\" value=\"yes\">
</form> 
 

 
 
	</div> 
 
 
</html> ";
	
?>
