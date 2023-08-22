<script type="text/javascript" src="plugins/jquery/jquery.min.js"></script>
<script type="text/javascript" src="plugins/jquery/jquery.js"></script>

<?php
//baca status terakhir led dan servo
include "koneksi.php";

$sql_logam = mysqli_query($koneksi, "SELECT * FROM tbl_logam");
$data_logam = mysqli_fetch_array($sql_logam);

$sql_anorganik = mysqli_query($koneksi, "SELECT * FROM tbl_anorganik");
$data_anorganik = mysqli_fetch_array($sql_anorganik);

$sql_organik = mysqli_query($koneksi, "SELECT * FROM tbl_organik");
$data_organik = mysqli_fetch_array($sql_organik);

//ambil hasil ultrasonik
$Sampah_logam = $data_logam['SAMPAH_LOGAM'];

//ambil hasil ultrasonik
$Sampah_anorganik = $data_anorganik['SAMPAH_ANORGANIK'];

//ambil hasil ultrasonik
$Sampah_organik = $data_organik['SAMPAH_ORGANIK'];

?>


<script type="text/javascript">
    //function menampilkan ultrasonik
    $(document).ready(function() {
        setInterval(function() {
            $("#ceksensor_logam").load('cekultrasonik_logam.php');
        }, 1000);
    });
    //function menampilkan ultrasonik
    $(document).ready(function() {
        setInterval(function() {
            $("#ceksensor_organik").load('cekultrasonik_organik.php');
        }, 1000);
    });
    //function menampilkan ultrasonik
    $(document).ready(function() {
        setInterval(function() {
            $("#ceksensor_anorganik").load('cekultrasonik_anorganik.php');
        }, 1000);
    });
</script>
<div class="container-fluid">
    <div class="row">


        <div class="col-md-12">
            <div class="card">
                <div class="card-header p-2">
                    <ul class="nav nav-pills">

                        <div class="btn btn-primary">UKURAN TEMPAT SAMPAH LOGAM: </div>

                    </ul>
                    <form method="post" action="tambah_logam.php">

                        <tr>
                            <td> INPUTAN UKURAN TEMPAT SAMPAH</td>
                            <td><input type="text" name="edit_ukuran_logam"></td>
                            <td><input type="submit" value="Ubah Ukuran"></td>
                        </tr>

                    </form>
                    <ul class="nav nav-pills">

                        <div class="btn btn-primary">UKURAN TEMPAT SAMPAH ORGANIK : </div>

                    </ul>
                    <form method="post" action="tambah_organik.php">

                        <tr>
                            <td> INPUTAN UKURAN TEMPAT SAMPAH</td>
                            <td><input type="text" name="edit_ukuran_organik"></td>
                            <td><input type="submit" value="Ubah Ukuran"></td>
                        </tr>

                    </form>
                    <ul class="nav nav-pills">

                        <div class="btn btn-primary">UKURAN TEMPAT SAMPAH ANORGANIK : </div>

                    </ul>
                    <form method="post" action="tambah_anorganik.php">

                        <tr>
                            <td> INPUTAN UKURAN TEMPAT SAMPAH</td>
                            <td><input type="text" name="edit_ukuran_anorganik"></td>
                            <td><input type="submit" value="Ubah Ukuran"></td>
                        </tr>

                    </form>
                </div><!-- /.card-header -->
                <div class="card-body">
                    <div class="tab-content">
                        <div class="active tab-pane" id="activity">
                            <table class="table">
                                <thead>
                                    <tr>
                                        <th scope="col">
                                            <!-- //card -->
                                            <div class="card" style="width: 18rem;">
                                                <div class="card-header">
                                                    Tempat Sampah Logam
                                                </div>
                                                <div class="card-body">
                                                    <h2> <span id="ceksensor_logam"></span></h2>
                                                </div>
                                            </div>
                                            <!-- card -->
                                        </th>
                                        <th scope="col">
                                            <!-- //card -->
                                            <div class="card" style="width: 18rem;">
                                                <div class="card-header">
                                                    Tempat Sampah Organik
                                                </div>
                                                <div class="card-body">
                                                    <h2><span id="ceksensor_organik"></span></h2>
                                                </div>
                                            </div>
                                            <!-- card -->
                                        </th>
                                        <th scope="col">
                                            <!-- //card -->
                                            <div class="card" style="width: 18rem;">
                                                <div class="card-header">
                                                    Tempat Sampah Anorganik
                                                </div>
                                                <div class="card-body">
                                                    <h2><span id="ceksensor_anorganik"></span></h2>
                                                </div>
                                            </div>
                                            <!-- card -->
                                        </th>

                                    </tr>
                                </thead>

                            </table>

                        </div>
                        <!-- /.tab-pane -->
                    </div>
                    <!-- /.tab-content -->
                </div><!-- /.card-body -->
            </div>
            <!-- /.nav-tabs-custom -->
        </div>
        <!-- /.col -->
    </div>
    <!-- /.row -->
</div><!-- /.container-fluid -->