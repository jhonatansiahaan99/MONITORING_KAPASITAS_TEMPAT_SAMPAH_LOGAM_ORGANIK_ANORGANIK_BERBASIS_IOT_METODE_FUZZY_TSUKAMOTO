<?php
// koneksi database
include 'koneksi.php';

// menangkap data yang di kirim dari form
$edit_ukuran = $_POST['edit_ukuran_anorganik'];


// menginput data ke database
mysqli_query($koneksi, "UPDATE tbl_anorganik set UKURAN='$edit_ukuran' where ID_SAMPAH='1' ");

// mengalihkan halaman kembali ke index.php
header("location:index.php");
