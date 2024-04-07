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
echo "  <label for='categorie'><h2>Alege tipul cardului:</h2></label>";
echo "  <select name='tip' id='tip'>";
echo "    <option value='Visa'>Visa</option>";
echo "    <option value='Mastercard'>Mastercard</option>";
echo "  </select>";
echo "  <input type='submit' value='Submit'>";
echo "</form>";

if(isset($_POST['tip']) && $_POST['tip'] == 'Visa') {
    header('Location: Titulari Visa.php');
    exit;
}
elseif(isset($_POST['tip']) && $_POST['tip'] == 'Mastercard') {
    header('Location: Titulari Mastercard.php');
    exit;
}


echo '<br>';

echo "<button onclick='history.back()' class='center2'>Revenire</button>";

?>