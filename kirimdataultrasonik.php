<?php

//include koneksi
include "koneksi.php";
date_default_timezone_set("Asia/Jakarta");
$jam = date('H');

//baca data yang dikirim oleh nodemcu
$nilai_logam = isset($_GET['kapasitas_logam']) ? $_GET['kapasitas_logam'] : ''; //"sensor" diambil dari arduino parameter yang ada di variabel link di arduino
$nilai_organik = isset($_GET['kapasitas_organik']) ? $_GET['kapasitas_organik'] : ''; //"kode" diambil dari arduino parameter yang ada di variabel link di arduino
$nilai_anorganik = isset($_GET['kapasitas_anorganik']) ? $_GET['kapasitas_anorganik'] : ''; //"kode" diambil dari arduino parameter yang ada di variabel link di arduino

//update data di database (tabel sensor)
$simpan_logam = mysqli_query($koneksi, "UPDATE tbl_logam set SAMPAH_LOGAM='$nilai_logam', WAKTU='$jam' where ID_SAMPAH='1' ");
$simpan_anorganik = mysqli_query($koneksi, "UPDATE tbl_anorganik set SAMPAH_ANORGANIK='$nilai_anorganik', WAKTU='$jam' where ID_SAMPAH='1' ");
$simpan_organik = mysqli_query($koneksi, "UPDATE tbl_organik set SAMPAH_ORGANIK='$nilai_organik', WAKTU='$jam' where ID_SAMPAH='1' ");
