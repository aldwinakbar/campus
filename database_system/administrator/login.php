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
 
 
 if($find == 0) // User not found. So, redirect to login_form again.
{
    header('Location: login-page.php?userLogin=false');
}
 else {
 session_regenerate_id();
	$_SESSION['sess_user_id'] = $o['id_user'];
	$_SESSION['sess_password'] = $o['password'];
	session_write_close();
	header("location: home.php?menu=main");
}

?>


