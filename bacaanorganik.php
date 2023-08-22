<?php

//include koneksi
include "koneksi.php";


$sql = mysqli_query($koneksi, "SELECT * from tbl_anorganik");
$data = mysqli_fetch_array($sql);
$Ukurananorganik = $data['UKURAN'];


//Berikan response
echo $Ukurananorganik;
