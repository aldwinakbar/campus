<?php
//Start session
session_start();

 
//Check whether the session variable SESS_MEMBER_ID is present or not
if(!isset($_SESSION['sess_user_id']) || (trim($_SESSION['sess_user_id']) == '')) {
	header("location: login-page.php");
	exit();
}
include "../database/connection.php";
$login=mysql_query("SELECT * FROM user WHERE id_user='$_SESSION[sess_user_id]'");
$o=mysql_fetch_array($login);

if ($o[level] != 'admin'){
	header("location: login-page.php");
	exit();
}

if($_GET[menu] == NULL){
	header("location: home.php?menu=main");
}

if ($_GET[logout] == true){	session_unset(); session_destroy(); header("location: login-page.php");}
?>

<!DOCTYPE html>

<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
    <title>Proyek SBD | Administrator</title>
    <link href="../css/bootstrap.min.css" rel="stylesheet">
    <link href="../css/font-awesome.min.css" rel="stylesheet">
    <link href="../css/prettyPhoto.css" rel="stylesheet">
    <link href="../css/animate.css" rel="stylesheet">
    <link href="../css/main.css" rel="stylesheet">
        
    <link rel="shortcut icon" href="../images/ico/favicon.ico">
    <link rel="apple-touch-icon-precomposed" sizes="144x144" href="../images/ico/apple-touch-icon-144-precomposed.png">
    <link rel="apple-touch-icon-precomposed" sizes="114x114" href="../images/ico/apple-touch-icon-114-precomposed.png">
    <link rel="apple-touch-icon-precomposed" sizes="72x72" href="../images/ico/apple-touch-icon-72-precomposed.png">
    <link rel="apple-touch-icon-precomposed" href="../images/ico/apple-touch-icon-57-precomposed.png">
</head><!--/head-->
<body>
    <header class="navbar navbar-inverse navbar-fixed-top wet-asphalt" role="banner">
        <div class="container">
            <div class="navbar-header">
                <a class="navbar-brand" href="home.php?menu=main"><img src="../images/logo.png" alt="logo"></a>
            </div>
            <div class="collapse navbar-collapse">
                <ul class="nav navbar-nav navbar-right">
					 
                    <li <?php  if ($_GET[menu] == add){ echo " class=\"active\"";} ?> ><a href="home.php?menu=add">Add Data</a></li>
                    <li <?php  if ($_GET[menu] == addpeta){ echo " class=\"active\"";} ?> ><a href="home.php?menu=addpeta">Add Lokasi</a></li>
                    <li <?php  if ($_GET[menu] == perusahaan){ echo " class=\"active\"";} ?> ><a href="home.php?menu=perusahaan">Perusahaan</a></li>
                    <li <?php  if ($_GET[menu] == komoditas){ echo " class=\"active\"";} ?> ><a href="home.php?menu=komoditas">Komoditas</a></li>
                    <li <?php  if ($_GET[menu] == tahun){ echo " class=\"active\"";} ?> ><a href="home.php?menu=tahun">Tahun</a></li>
                    <li <?php  if ($_GET[menu] == nilai){ echo " class=\"active\"";} ?> ><a href="home.php?menu=nilai">Nilai</a></li>
                    <li <?php  if ($_GET[menu] == peta){ echo " class=\"active\"";} ?> ><a href="home.php?menu=peta">Peta</a></li>
                    <li><a href="home.php?logout=true">Logout</a></li>
                </ul>
            </div>
        </div>
    </header><!--/header-->

    <section id="title" class="green-sea">
        <div class="container">
            <div class="row">
                <div class="col-sm-6">
                    <h1>Welcome back, <?php echo $o[nama_lengkap] ;?></h1>
                    
                  
    <?php 
    if ($_GET[menu] == main){	echo "<p>Selamat datang, pada menu utama ini semua data disortir sesuai ID-nya</p>";}
    if ($_GET[menu] == perusahaan){	echo "<p>Selamat datang, pada menu admin ini semua data disortir sesuai nama perusahaan-nya</p>";}
    if ($_GET[menu] == komoditas){	echo "<p>Selamat datang, pada menu admin ini semua data disortir sesuai komoditas-nya</p>";}
    if ($_GET[menu] == tahun){	echo "<p>Selamat datang, pada menu admin ini semua data disortir sesuai tahun-nya</p>";}
    if ($_GET[menu] == nilai){	echo "<p>Selamat datang, pada menu admin ini semua data disortir sesuai jumlah produksinya</p>";}
    if ($_GET[menu] == peta){	echo "<p>Selamat datang, pada menu admin ini terdapat semua lokasi pertambangan mineral</p>";}
    if ($_GET[menu] == addpeta){	echo "<p>Disini, anda dapat menambahkan data lokasi baru tempat pertambangan</p>";}
    if ($_GET[menu] == editpeta){	echo "<p>Disini, anda dapat mengedit data lokasi pertambangan yang anda pilih</p>";}
    if ($_GET[menu] == add){	echo "<p>Disini, anda dapat menambahkan data baru mengenai hasil produksi</p>";}
    if ($_GET[menu] == edit){	echo "<p>Disini, anda dapat mengedit data hasil produksi yang anda pilih</p>";}
     ?>               
                </div>
            </div>
        </div>
    </section><!--/#title-->     

    <section id="services" class="clouds">
    <?php if ($_GET[menu] == main){
	$sortValue  = 'ORDER BY id ASC';
	include "table.php";			
	}
	elseif ($_GET[menu] == perusahaan){
	$sortValue  = 'ORDER BY nama_perusahaan ASC';
	include "table.php";		
	}
	elseif ($_GET[menu] == komoditas){
	$sortValue  = 'ORDER BY komoditas ASC';	
	include "table.php";	
	}
	elseif ($_GET[menu] == tahun){
	$sortValue  = 'ORDER BY tahun ASC';	
	include "table.php";	
	}
	elseif ($_GET[menu] == nilai){
	$sortValue  = 'ORDER BY nilai DESC';	
	include "table.php";	
	}
	
	elseif ($_GET[menu] == peta){
	include "peta.php";	
	}
	
	elseif ($_GET[menu] == addpeta){
	include "editPeta.php";	
	}
	
	elseif ($_GET[menu] == editpeta){
	include "editPeta.php";	
	}
	
	elseif ($_GET[menu] == add){
	include "editData.php";
	}
	
	elseif ($_GET[menu] == edit){
	include "editData.php";
	}
	?>
    </section><!--/#services-->

    <footer id="footer" class="midnight-blue">
        <div class="container">
            <div class="row">
                <div class="col-sm-6">
                    &copy; 2014 <a target="_blank" href="http://127.0.0.1/" title="Proyek SBD 2014">Proyek SBD</a>. All Rights Reserved.
                </div>
            </div>
        </div>
    </footer><!--/#footer-->

    <script src="js/jquery.js"></script>
    <script src="js/bootstrap.min.js"></script>
    <script src="js/jquery.prettyPhoto.js"></script>
    <script src="js/main.js"></script>
</body>
</html>
