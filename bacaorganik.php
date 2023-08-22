<?php

//include koneksi
include "koneksi.php";


$sql = mysqli_query($koneksi, "SELECT * from tbl_organik");
$data = mysqli_fetch_array($sql);
$Ukuranorganik = $data['UKURAN'];


//Berikan response
echo $Ukuranorganik;
