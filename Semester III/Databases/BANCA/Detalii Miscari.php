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
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
  }

.centertable {
    position: absolute;
    top: 30%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
</style>';

$conn = sqlsrv_connect($serverName, $connection);
if(!$conn)
    die(print_r(sqlsrv_errors(), true));

// Build the SELECT query
$query = "SELECT * FROM Miscari WHERE valoare BETWEEN 500 AND 1000 ORDER BY scop, valoare DESC;";

// Execute the query
$result = sqlsrv_query($conn, $query);
echo "<br>";
echo "<h2 class = 'center'>Acestea sunt detaliile mișcărilor cu valoare între 500 și
1000 ordonat crescător după scop și descrescător după valoare:</h2>";
echo "<br>";

echo '<table class = "centertable">';
echo '<tr><th>Numar Card</th><th>Data miscarii</th><th>Valoarea miscarii</th><th>Scopul miscarii</th></tr>';

while ($row = sqlsrv_fetch_array($result, SQLSRV_FETCH_ASSOC)) {
    echo '<tr>';
    echo '<td>' . $row['NRCARD'] . '</td>';
    $date_string = $row['DATA_ORA']->format('d-M-Y');
        $date = new DateTime($date_string);
    echo '<td>' . $date->format("d-M-Y") . '</td>';
    echo '<td>' . $row['VALOARE'] . '</td>';
    echo '<td>' . $row['SCOP'] . '</td>';
    echo '</tr>';
}

echo '</table>';
echo '<br>';

echo "<button onclick='history.back()' class= 'center1'>Revenire</button>";

// Close the connection
sqlsrv_close($conn);