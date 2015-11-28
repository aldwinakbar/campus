<?php
session_start();
//Connect to the DB
include "../database/connection.php";

//Add Data Produksi Mineral
if ($_POST[prs] == adata){

	$nama_perusahaan = htmlspecialchars($_POST[nama_perusahaan], ENT_QUOTES);
	$komoditas = htmlspecialchars($_POST[komoditas], ENT_QUOTES);
	$tahun = $_POST[tahun];
	$nilai = $_POST[nilai];
	mysql_query("INSERT INTO produksi_mineral(nama_perusahaan, komoditas, tahun, nilai, satuan)
	VALUES('$nama_perusahaan', '$komoditas', $tahun, $nilai, 'kg')");
	header('location:home.php?menu=main');
}

//Edit Data Produksi Mineral
elseif ($_POST[prs] == edata){
	$nama_perusahaan = htmlspecialchars($_POST[nama_perusahaan], ENT_QUOTES);
	$komoditas = htmlspecialchars($_POST[komoditas], ENT_QUOTES);
	$tahun = $_POST[tahun];
	$nilai = $_POST[nilai];
	$backmenu = $_POST[menu];
	$page = $_POST[page];
	mysql_query("UPDATE produksi_mineral SET nama_perusahaan='$nama_perusahaan', komoditas='$komoditas', tahun=$tahun, nilai=$nilai WHERE id='$_POST[id]'");
	header('location:home.php?menu='.$backmenu.'&page='.$page.'');
}

//Delete Data Produksi Mineral
elseif ($_GET[deldata] == yes){
	
	$backmenu = $_GET[backmenu];
	$page = $_GET[page];
	mysql_query("DELETE FROM produksi_mineral WHERE id='$_GET[id]'");
	header('location:home.php?menu='.$backmenu.'&page='.$page.'');
}

//Add Lokasi Pertambangan
elseif ($_POST[prs] == apeta){

	$name = htmlspecialchars($_POST[name], ENT_QUOTES);
	$lat = $_POST[lat];
	$lon = $_POST[lon];
	mysql_query("INSERT INTO lokasi_tambang(name, lat, lon)
	VALUES('$name', $lat, $lon)");
	header('location:home.php?menu=peta');
}

//Edit Lokasi Pertambangan
elseif ($_POST[prs] == epeta){
	$name = htmlspecialchars($_POST[name], ENT_QUOTES);
	$lat = $_POST[lat];
	$lon = $_POST[lon];
	$backmenu = $_POST[menu];
	$page = $_POST[page];
	mysql_query("UPDATE lokasi_tambang SET name='$name', lat=$lat, lon=$lon WHERE id='$_POST[id]'");
	header('location:home.php?menu='.$backmenu.'&page='.$page.'');
}

//Delete Lokasi Pertambangan
elseif ($_GET[delpeta] == yes){
	
	$backmenu = $_GET[backmenu];
	$page = $_GET[page];
	mysql_query("DELETE FROM lokasi_tambang WHERE id='$_GET[id]'");
	header('location:home.php?menu='.$backmenu.'&page='.$page.'');
}

//Add User Administrator
elseif ($_POST[prs] == auser){

	// add htmlspecialchars to change single and double qoute into html special char
	$user = htmlspecialchars($_POST[id_user], ENT_QUOTES);
	$namalengkap = htmlspecialchars($_POST[nama_lengkap], ENT_QUOTES);
	
	//encryption method 
	$password = sha1(md5($_POST[password]));
	$salt = "bYU1hg32fclr" ;
	$pass = md5($salt.$password);
	
	mysql_query("INSERT INTO user(id_user, password, nama_lengkap, email, level)
	VALUES('$user', '$pass', '$namalengkap', '$_POST[email]', '$_POST[level]')");
	header('location:index.php');
}

?>
