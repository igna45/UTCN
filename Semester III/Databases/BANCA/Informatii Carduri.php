<?php
echo '<style>
.center1 {
  position: absolute;
  top: 20%;
  left: 50%;
  transform: translate(-50%, -50%);
}
</style>';

echo '<style>
.center2 {
  position: absolute;
  top: 35%;
  left: 50%;
  transform: translate(-50%, -50%);
}
</style>';

echo '<br>';
echo "<form action='' method='post' class='center1'>";
echo "  <label for='categorie'><h2> Alege categoria cardului:</h2></label>";
echo "  <select name='categorie' id='categorie'>";
echo "    <option value='debit'>Debit</option>";
echo "    <option value='credit'>Credit</option>";
echo "  </select>";
echo "  <input type='submit' value='Submit'>";
echo "</form>";

if(isset($_POST['categorie']) && $_POST['categorie'] == 'debit') {
    header('Location: Carduri Debit.php');
    exit;
}
elseif(isset($_POST['categorie']) && $_POST['categorie'] == 'credit') {
    header('Location: Carduri Credit.php');
    exit;
}


echo '<br>';

echo "<button onclick='history.back()' class='center2'>Revenire</button>";

?>