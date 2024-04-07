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
    top: 36%;
    left: 50%;
    transform: translate(-50%, -50%);
  }

.centertable {
    position: absolute;
    top: 23%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
</style>';

$conn = sqlsrv_connect($serverName, $connection);
if(!$conn)
    die(print_r(sqlsrv_errors(), true));

// Build the SELECT query
$query = "select min(valoare) as 'Valoare minima', max(valoare) as 'Valoare maxima', avg(valoare) as 'Valoare medie'
from [BANCA].[dbo].[miscari]
where nrcard IN( select nrcard from [BANCA].[dbo].[carduri] where nrcont 
IN(select nrcont from [BANCA].[dbo].[conturi] where idpers 
IN(select idpers from [BANCA].[dbo].[Persoane] where data_nasterii BETWEEN '01-Jan-1998' AND '31-Dec-1998')))
AND data_ora BETWEEN convert(date, '01-Jan-2021') AND convert(date, '31-Dec-2022');";

// Execute the query
$result = sqlsrv_query($conn, $query);


echo "<br>";
echo "<h2 class = 'center'>Pentru persoanele născute în anul 1998 valoarea minimă,
medie și maximă cheltuită cu carduri în anii 2022 și 2021:</h2>";
echo "<br>";

echo '<table class = "centertable">';
echo '<tr><th>Valoare minima</th><th>Valoare maxima</th><th>Valoare medie</th></tr>';

while ($row = sqlsrv_fetch_array($result, SQLSRV_FETCH_ASSOC)) {
    echo '<tr>';
    echo '<td>' . $row['Valoare minima'] . '</td>';
    echo '<td>' . $row['Valoare maxima'] . '</td>';
    echo '<td>' . $row['Valoare medie'] . '</td>';
    echo '</tr>';
}

echo '</table>';
echo '<br>';
echo "<button onclick='history.back()' class = 'center1'>Revenire</button>";

// Close the connection
sqlsrv_close($conn);