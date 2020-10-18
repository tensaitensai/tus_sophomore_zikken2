<?php
/////////////////
// sample8.php //
/////////////////

$pdo = new PDO('sqlite:vending.db');
$stmt = $pdo->prepare("SELECT * FROM items");
$stmt->execute();

$rows = $stmt->fetchALL();

foreach ($rows as $row) {
    echo $row['id'];
    echo ", ";
    echo $row['name'];
    echo ",";
    echo $row['price'];
    echo " JPY<br>";
}
