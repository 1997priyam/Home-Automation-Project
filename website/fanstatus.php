<?php


$servername = "localhost";
$username = "test";
$password = "test";
$dbname = "priyam";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "select info from status order by id desc limit 1";

$result = mysqli_query($conn, $sql);
$row=mysqli_fetch_row($result);

if ($row[0]==1)
{
echo "FAN ON";

}

else
{
echo "FAN OFF";
}



$conn->close();
?>