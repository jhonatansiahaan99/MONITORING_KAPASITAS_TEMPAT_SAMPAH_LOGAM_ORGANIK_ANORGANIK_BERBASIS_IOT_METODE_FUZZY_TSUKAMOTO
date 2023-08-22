<?php

//include koneksi
include "koneksi.php";


$sql = mysqli_query($koneksi, "SELECT * from tbl_logam");
$data = mysqli_fetch_array($sql);
$Ukuranlogam = $data['UKURAN'];


//Berikan response
echo $Ukuranlogam;
