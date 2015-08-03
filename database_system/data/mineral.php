<?php
   include "../database/connection.php";

    $myquery = "SELECT  nama_perusahaan, komoditas, satuan, tahun, nilai/1000 as nilai FROM  produksi_mineral";
    $query = mysql_query($myquery);
    
    if ( ! $query ) {
        echo mysql_error();
        die;
    }
    
    $data = array();
    
    for ($x = 0; $x < mysql_num_rows($query); $x++) {
        $data[] = mysql_fetch_assoc($query);
    }
    
    echo json_encode($data);     
     
    mysql_close($server);
?>
