
    	<div class="container">
			<table class="table table-hover">
			<!--we create here table heading-->
				<thead>
					<tr>
						<th>No</th>
						<th>Nama</th>
						<th>Latitude</th>
						<th>Longitude</th>				
						<th>Option</th>
					</tr>
				</thead>
 
				<tbody>
					<?php
					//set up mysql connection
					$whereValue = 'id > 0';
					
					include "../database/connection.php";
					//number of results to show per page
					$rec_limit = 50;
 
					
					/* Get total number of records */
					$sql    = "SELECT count(id) FROM lokasi_tambang where $whereValue ";
					$retval = mysql_query($sql, $conn);
					if (!$retval) {
						die('Could not get data: ' . mysql_error());
					}
 
					$row       = mysql_fetch_array($retval, MYSQL_NUM);
					$rec_count = $row[0]; /* Get total number of records */
					/* Get total number of records */
 
 
					//######### if there's get method ###########
					if (isset($_GET{'page'})) { //get the current page
						$page   = $_GET{'page'};
						$offset = $rec_limit * ($page - 1);
					}
					else {
						
						$page   = 1;
						$offset = $rec_limit * ($page - 1);
						
						}
					//######### if there's get method ###########
										

					//we set the specific query to display in the table
					$sql = "SELECT * FROM lokasi_tambang where $whereValue LIMIT $offset, $rec_limit ";
					$retval = mysql_query($sql, $conn);
					$totalPage = ceil($rec_count / $rec_limit);
					if (!$retval) {
						die('Could not get data: ' . mysql_error());
					}
					
					//we loop through each records
					$numData = $offset +1;
					while ($row = mysql_fetch_array($retval, MYSQL_ASSOC)) {
						
						//populate and display results data in each row
						echo '<tr>';
						echo '<td>' . $numData . '</td>';
						echo '<td>' . $row['name'] . '</td>';
						echo '<td>' . $row['lat'] . '</td>';
						echo '<td>' . $row['lon'] . '</td>';
						echo "<td><a href=\"home.php?menu=editpeta&edit=yes&id=$row[id]&page=$page&backmenu=$_GET[menu]\">Edit</a> | 
							  <a href=\"proses.php?id=$row[id]&delpeta=yes&page=$page&backmenu=$_GET[menu]\">Delete</a></td>";
						$numData++;
					}
 
					echo '</tr>';
					echo '</tbody>';
					echo '</table>';
					//we display here the pagination
								
					echo "<center>
					<ul class=\"pagination \"> ";
					if ( $page == 1){
						echo "	<li class=\"disabled\"><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=1\">First</a></li>";}
					else
						echo "	<li><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=1\">First</a></li>";
					
					for ($i=1;$i<=$totalPage;$i++)
					{
							if ( $page == $i){
								echo "<li class=\"active\"><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=$i\">$i</a></li>";	}
							else{
								echo "<li><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=$i\">$i</a></li>";}
					}
					
					if ( $page == $totalPage){
						echo "	<li class=\"disabled\"><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=$totalPage\">Last</a></li>";}
					else
						echo "	<li><a href=\"$_PHP_SELF?menu=$_GET[menu]&page=$totalPage\">Last</a></li>";
					
					echo "
					</ul>
					</center>";
					
					mysql_close($conn);
					?>
				</tbody>
			</table>
		</div>
	
       
