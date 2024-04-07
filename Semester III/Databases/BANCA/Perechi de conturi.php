<?php
$serverName = "LAPTOP-U2KQG36R\SQLEXPRESS";
$database = "BANCA";
$uid = "";
$pass = "";

$connection = [
    "Database"=>$database,
    "Uid"=> $uid,
    "PWD"=>$pass
];

echo '<style>
table {
    border-collapse: collapse;
}

  .center {
    text-align: center;
  }

table, th, td {
    border: 1px solid black;
}

th, td {
    padding: 10px;
    text-align: left;
}

th {
    background-color: #dddddd;
}

tr:nth-child(even) {
    background-color: #f2f2f2;
}

.center1 {
    position: absolute;
    top: 45%;
    left: 50%;
    transform: translate(-50%, -50%);
  }

.centertable {
    position: absolute;
    top: 28%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
</style>';


$conn = sqlsrv_connect($serverName, $connection);
if(!$conn)
    die(print_r(sqlsrv_errors(), true));

// Build the SELECT query
$query = "SELECT DISTINCT
CASE 
    WHEN a.nrcont < b.nrcont THEN a.nrcont
    ELSE b.nrcont
END AS 'Cont1',
CASE
    WHEN a.nrcont > b.nrcont THEN a.nrcont
    ELSE b.nrcont
END AS 'Cont2'
FROM Conturi a
JOIN Conturi b ON a.idpers = b.idpers
WHERE a.nrcont != b.nrcont";

// Execute the query
$result = sqlsrv_query($conn, $query);


echo "<br>"; 
echo "<h2 class = 'center'>Acestea sunt perechi de conturi care corespund aceleiași
persoane:</h2>";
echo "<br>";

echo '<table class = "centertable">';
echo '<tr><th>Cont1</th><th>Cont2</th></tr>';

while ($row = sqlsrv_fetch_array($result, SQLSRV_FETCH_ASSOC)) {
    echo '<tr>';
    echo '<td class = "center">' . $row['Cont1'] . '</td>';
    echo '<td class = "center">' . $row['Cont2'] . '</td>';
    echo '</tr>';
}

echo '</table>';
echo '<br>';
echo "<button onclick='history.back()' class = 'center1'>Revenire</button>";

// Close the connection
sqlsrv_close($conn);