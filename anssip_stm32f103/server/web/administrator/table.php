
    	<div class="container">
			<table class="table table-hover">
			<!--we create here table heading-->
				
					<?php
				
					if($table_selection == main){
						
						echo "
					<thead>
					<tr>
						<th>No</th>
						<th>Nama</th>
						<th>UID</th>
						<th>Waktu</th>	
					</tr>
				</thead>
 
				<tbody> ";
					//set up mysql connection
					$whereValue = 'no > 0';
					
					include "../database/connection.php";
					//number of results to show per page
					$rec_limit = 50;
 
					
					/* Get total number of records */
					$sql    = "SELECT count(no) FROM class_log where $whereValue ";
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
					$sql = "SELECT * FROM class_log where $whereValue $sortValue LIMIT $offset, $rec_limit ";
					$retval = mysql_query($sql, $conn);
					$totalPage = ceil($rec_count / $rec_limit);
					if (!$retval) {
						die('Could not get data: ' . mysql_error());
					}
					
					//we loop through each records
					$numData = $offset +1;
					
					while ($row = mysql_fetch_array($retval, MYSQL_ASSOC)) {
					$card_now = $row['card_uid'];
					$name_id_ret = mysql_query("SELECT * FROM user_uid where uid='$card_now'", $conn);
					$name_id_val = mysql_fetch_array($name_id_ret);
						
						//populate and display results data in each row
						echo '<tr>';
						echo '<td>' . $numData. '</td>';
						echo '<td>' . $name_id_val['name']. '</td>';
						echo '<td>' . $row['card_uid'] . '</td>';
						echo '<td>' . $row['timestamp'] . '</td>';
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
				}
				
				else if ($table_selection == uid){
					echo "
					<thead>
					<tr>
						<th>No</th>
						<th>Nama</th>
						<th>UID</th>
					</tr>
				</thead>
 
				<tbody>";
					
					
					//set up mysql connection
					$whereValue = 'no > 0';
					
					include "../database/connection.php";
					//number of results to show per page
					$rec_limit = 50;
 
					
					/* Get total number of records */
					$sql    = "SELECT count(no) FROM user_uid where $whereValue ";
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
					$sql = "SELECT * FROM user_uid where $whereValue $sortValue LIMIT $offset, $rec_limit ";
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
						echo '<td>' . $row['uid'] . '</td>';
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
					}
					?>
				</tbody>
			</table>
		</div>
	
       
