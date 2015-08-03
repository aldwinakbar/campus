
		<div class="container">
			
		<?php  include "../database/connection.php";
		$page = $_GET['page'];
		$id   = $_GET['id'];
		$queryData=mysql_query("SELECT * FROM lokasi_tambang WHERE id = $id");
		$fetch=mysql_fetch_array($queryData);
		if ($_GET['edit'] == 'yes'){$status = 'epeta';}
		else { $status = 'apeta';}
		?>
		
		
		<div class="col-md-4">
			<form role="form" method="POST" action="proses.php" >
				<div class="form-group">
					<label for="nama_perusahaan">Nama</label>
					<input type="text" class="form-control" name="name" value="<?php echo $fetch[name] ?>" placeholder="Nama">
				</div>
				
				<div class="form-group">
					<label for="komoditas">Latitude</label>
					<input type="text" class="form-control" name="lat" value="<?php echo $fetch[lat] ?>" placeholder="Latitude">
				</div>
				
				<div class="form-group">
					<label for="tahun">Longitude</label>
					<input type="text" class="form-control" name="lon" value="<?php echo $fetch[lon] ?>" placeholder="Longitude">
				</div>
				
				<input type="hidden" name="prs" value="<?php echo $status ?>">
				<input type="hidden" name="id" value="<?php echo $id ?>">
				<input type="hidden" name="page" value="<?php echo $page ?>">
				<input type="hidden" name="menu" value="<?php echo $_GET['backmenu'] ?>">
				<button type="submit" class="btn btn-primary">Masukan Data</button>
			</form>
		</div>
	</div>

