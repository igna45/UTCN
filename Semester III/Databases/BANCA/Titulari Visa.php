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
    top: 60%;
    left: 50%;
    transform: translate(-50%, -50%);
  }

.centertable {
    position: absolute;
    top: 35%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
</style>';

$conn = sqlsrv_connect($serverName, $connection);
if(!$conn)
    die(print_r(sqlsrv_errors(), true));

// Build the SELECT query
$query = "EXEC GetTip @tip = 'visa';";

// Execute the query
$result = sqlsrv_query($conn, $query);

echo "<br>";
echo "<h2 class = 'center'>Acestia sunt titularii cardurilor de tip VISA:</h2>";
echo "<br>";

echo '<table class = "centertable">';
echo '<tr><th>Nume titulari</th></tr>';

while ($row = sqlsrv_fetch_array($result, SQLSRV_FETCH_ASSOC)) {
    echo '<tr>';
    echo '<td class = "center">' . $row['nume'] . '</td>';
    echo '</tr>';
}

echo '</table>';
echo '<br>';
echo "<button onclick='history.back()' class = 'center1'>Revenire</button>";

// Close the connection
sqlsrv_close($conn);