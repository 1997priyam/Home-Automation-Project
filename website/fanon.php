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

$sql = "INSERT INTO status (info) VALUES (1)";


if ($conn->query($sql) === TRUE) {
    echo "Fan on";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>