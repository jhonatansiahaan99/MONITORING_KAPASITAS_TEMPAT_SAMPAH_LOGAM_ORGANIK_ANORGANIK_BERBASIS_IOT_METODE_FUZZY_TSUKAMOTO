<?php
//include koneksi
include "koneksi.php";
$sql = mysqli_query($koneksi, "SELECT * from tbl_organik");
$data = mysqli_fetch_array($sql);
$Nilai_kapasitas_organik = $data['SAMPAH_ORGANIK'];
$Waktu = $data['WAKTU'];
$Ukuran = $data['UKURAN'];


if ($Nilai_kapasitas_organik <= 0) {
    $Miu_organik_rendah = 1;
} else if ($Nilai_kapasitas_organik >= 100) {
    $Miu_organik_rendah = 0;
} else {
    $Miu_organik_rendah = (100 - $Nilai_kapasitas_organik) / (100 - 0); //b-x/b-a

}

if ($Nilai_kapasitas_organik <= 0) {
    $Miu_organik_tinggi = 0;
} else if ($Nilai_kapasitas_organik >= 100) {
    $Miu_organik_tinggi = 1;
} else {
    $Miu_organik_tinggi = ($Nilai_kapasitas_organik - 0) / (100 - 0); //x-a/b-a

}



if ($Waktu <= 6) {
    $Miu_waktu_rendah = 1;
    // var_dump($Miu_waktu_rendah);
} else if ($Waktu >= 24) {
    $Miu_waktu_rendah = 0;
    // var_dump($Miu_waktu_rendah);
} else {
    $Miu_waktu_rendah = (24 - $Waktu) / (24 - 6); //b-x/b-a
    // var_dump($Miu_waktu_rendah);
}

if ($Waktu <= 6) {
    $Miu_waktu_tinggi = 0;
    // var_dump($Miu_waktu_tinggi);
} else if ($Waktu >= 24) {
    $Miu_waktu_tinggi = 1;
    // var_dump($Miu_waktu_tinggi);
} else {
    $Miu_waktu_tinggi = ($Waktu - 6) / (24 - 6); //x-a/b-a
    // var_dump($Miu_waktu_tinggi);
}

$alpha_predikat_1 = min($Miu_organik_rendah, $Miu_waktu_rendah); //penuh
$alpha_predikat_2 = min($Miu_organik_tinggi, $Miu_waktu_rendah); //penuh
$alpha_predikat_3 = min($Miu_organik_rendah, $Miu_waktu_tinggi); //tersedia
$alpha_predikat_4 = min($Miu_organik_tinggi, $Miu_waktu_tinggi); //tersedia

// var_dump("=====");
// var_dump($alpha_predikat_1);
// var_dump($alpha_predikat_2);
// var_dump($alpha_predikat_3);
// var_dump($alpha_predikat_4);


if ($alpha_predikat_1 == 0) { //penuh
    $z1 = $Ukuran;
    // var_dump($z1);
} else if ($alpha_predikat_1 == 1) {
    $z1 = 0;
    // var_dump($z1);
} else {
    $z1 = $Ukuran - ($alpha_predikat_1 * ($Ukuran - 0));
    // var_dump($z1);
}

if ($alpha_predikat_2 == 0) { //penuh
    $z2 = $Ukuran;
    // var_dump($z2);
} else if ($alpha_predikat_2 == 1) {
    $z2 = 0;
    // var_dump($z2);
} else {
    $z2 = $Ukuran - ($alpha_predikat_2 * ($Ukuran - 0));
    // var_dump($z2);
}

if ($alpha_predikat_3 == 0) { //tersedia
    $z3 = 0;
    // var_dump($z3);
} else if ($alpha_predikat_3 == 1) {
    $z3 = $Ukuran;
    // var_dump($z3);
} else {
    $z3 = 0 + ($alpha_predikat_3 * ($Ukuran - 0));
    // var_dump($z3);
}

if ($alpha_predikat_4 == 0) { //tersedia
    $z4 = 0;
    // var_dump($z3);
} else if ($alpha_predikat_4 == 1) {
    $z4 = $Ukuran;
    // var_dump($z3);
} else {
    $z4 = 0 + ($alpha_predikat_4 * ($Ukuran - 0));
    // var_dump($z3);
}

$total_alpha_kali_z = ($alpha_predikat_1 * $z1) + ($alpha_predikat_1 * $z2) + ($alpha_predikat_3 * $z3) + ($alpha_predikat_4 * $z4);
$total_alpha = ($alpha_predikat_1 + $alpha_predikat_2 + $alpha_predikat_3 + $alpha_predikat_4);

$z = $total_alpha_kali_z / $total_alpha;




//uji, apabila nilai_ultrasonik belum ada, maka anggap ultrasonik = 0
if ($z > 5) {
    echo '<img src="images/sampah_bersih.jpg" width="70" height="90" />';
} else {
    echo '<img src="images/sampah_kotor.png" width="70" height="90" />';
}
echo $z;
// echo $nilai_ultrasonik;
