<!DOCTYPE html>
<title>SPDS</title>

<head>
<link href="./resources/colours.css" rel="stylesheet" type="text/css">
<style>
.reveal-if-active {
  opacity: 0;
  max-height: 0;
  overflow: hidden;
  font-size: 16px;
  -webkit-transform: scale(0.8);
          transform: scale(0.8);
  transition: 0.5s;
}
.reveal-if-active label {
  display: block;
  margin: 0 0 3px 0;
}
input[type="radio"]:checked ~ .reveal-if-active, input[type="checkbox"]:checked ~ .reveal-if-active {
  opacity: 1;
  max-height: 100px;
  padding: 10px 20px;
  -webkit-transform: scale(1);
          transform: scale(1);
  overflow: visible;
}
</style>

<script>

</script>
</head>

<H1>Advance Monitoring and Control</H1>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
  <p>Do you want to change the passcode of the SPDS?</p>

  <input type="radio" id="pass-no" name="pass-yes-no" value="no" checked required>
  <label>No</label>

  <div>
  <input type="radio" id="pass-yes" name="pass-yes-no" value="yes" required>
  <label>Yes</label>
  <div class="reveal-if-active">
    <label for="newpass">Enter the desired passscode (must be 6 numbers):</label>
    <input type="text" id="newpass" name="passcode" class="require-if-active" data-require-pair="#pass-yes" >
    <input type="submit">
  </div>
  </div>
</form>
<?php
  $code = "";
  if ($_SERVER["REQUEST_METHOD"] == "POST") {
   $response = $_POST["pass-yes-no"];
   if ($response == "yes"){
    $code = str_replace('.','',$_POST["passcode"]);
    if( (strlen($code)==6)&&(is_numeric($code)) ){
     `sudo python /var/www/html/scripts/serial_control.py S $code`;
    }else{
     echo "Invalid Passcode";
    }
   }
  }
?>

<br><br>
<p>The weight inside the SPDS is currently:</p>
<?php
  `sudo python /var/www/html/scripts/serial_control.py W`;
  $weight = `sudo python /var/www/html/scripts/serial_control.py W`;
  echo $weight;
?>

<br>
<a href="./index.php">Return to Home Page</a>
