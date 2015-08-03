<!DOCTYPE html>
 
<html lang="en">
<head>
	<meta charset="utf-8">
	<meta content="width=device-width, initial-scale=1.0" name="viewport">
	<meta content="" name="description">
	<meta content="" name="author">
	<link href="" rel="shortcut icon">
 
	<title>Add User</title><!-- Bootstrap core CSS -->
	<link rel="stylesheet" href="css/bootstrap.min.css">
	<link rel="stylesheet" href="css/bootstrap-table.css">
</head>
 
<body>
	<div class="container">
		<div class="well">
			<h2>Add User</h2>
		</div>
 
		<div class="well">
		

<?php

echo "
<form method=\"POST\" action=\"proses.php\">
<table class=hovertable>
	<tr>
		<td>Username </td><td>: <input type=\"text\" name=\"id_user\"></td>
	</tr>
	<tr>
		<td>Password </td><td>: <input type=\"text\" name=\"password\"></td>
	</tr>
	<tr>
		<td>Nama Lengkap </td><td>: <input type=\"text\" name=\"nama_lengkap\" size=\"30\"></td>
	</tr>
	<tr>
		<td>E-mail </td><td>: <input type=\"text\" name=\"email\" size=\"30\"></td>
	</tr>
	<tr><td></td><td><select name=\"level\"><option value=\"0\" selected>- Choose a level -</option>
			<option value=\"user\">User</option>
			<option value=\"admin\">Administrator</option>
			</select></td></tr>
	<tr>
		<td colspan=\"2\"><input type=\"submit\" name=\"Agree\"> <input type=\"button\" value=\"Salah\" onclick=\"self.history.back()\"></td>
	</tr>
</table>
<input type=\"hidden\" name=\"prs\" value=\"auser\">
</form>";

?>

			
		</div>
	</div>
	<script src="js/jquery.min.js"></script>
<script src="js/bootstrap.min.js"></script>
<script src="js/bootstrap-table.js"></script>
</body>
</html>



