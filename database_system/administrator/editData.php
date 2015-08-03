
		<div class="container">
			
		<?php  include "../database/connection.php";
		$page = $_GET['page'];
		$id   = $_GET['id'];
		$queryData=mysql_query("SELECT * FROM produksi_mineral WHERE id = $id");
		$fetch=mysql_fetch_array($queryData);
		if ($_GET['edit'] == 'yes'){$status = 'edata';}
		else { $status = 'adata';}
		?>
		
		
		<div class="col-md-4">
			<form role="form" method="POST" action="proses.php" >
				<div class="form-group">
					<label for="nama_perusahaan">Nama Perusahaan</label>
					<input type="text" class="form-control" name="nama_perusahaan" value="<?php echo $fetch[nama_perusahaan] ?>" placeholder="Nama Perusahaan">
				</div>
				
				<div class="form-group">
					<label for="komoditas">Komoditas</label>
					<input type="text" class="form-control" name="komoditas" value="<?php echo $fetch[komoditas] ?>" placeholder="Jenis Komoditas">
				</div>
				
				<div class="form-group">
					<label for="tahun">Tahun</label>
					<input type="text" class="form-control" name="tahun" value="<?php echo $fetch[tahun] ?>" placeholder="Tahun Pemasukan">
				</div>
				
				<div class="form-group">
					<label for="nilai">Nilai</label>
					<input type="text" class="form-control" name="nilai" value="<?php echo $fetch[nilai] ?>" placeholder="Besar Berat Komoditas dalam Kg">
				</div>
				<input type="hidden" name="prs" value="<?php echo $status ?>">
				<input type="hidden" name="id" value="<?php echo $id ?>">
				<input type="hidden" name="page" value="<?php echo $page ?>">
				<input type="hidden" name="menu" value="<?php echo $_GET['backmenu'] ?>">
				<button type="submit" class="btn btn-primary">Masukan Data</button>
			</form>
		</div>
	</div>

