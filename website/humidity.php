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

$sql = "INSERT INTO statusd (infod) VALUES (1)";


if ($conn->query($sql) === TRUE) {
    echo "";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
sleep(6);

$sql1 = "select humidity from dht11 order by id desc limit 1";

$result = mysqli_query($conn, $sql1);
$row=mysqli_fetch_row($result);

echo "Humidity is $row[0] percent";

$sql2 = "INSERT INTO statusd (infod) VALUES (2)";
if ($conn->query($sql2) === TRUE) {
    echo "";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>