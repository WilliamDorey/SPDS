<!DOCTYPE html>
<title>SPDS</title>

<head>
<link href="./resources/colours.css" rel="stylesheet" type="text/css">
<style>
.center {
  display: block;
  margin-left: auto;
  margin-right: auto;
}

</style>
</head>

<body>
<h1>Monitoring</h1>
<p>Welcome to the monitoring screen. From here you can obtain the current weight of any objects in the container and obtain the most current image of the container via the remote camera.</p>
<div>
<h2>Archive</h2>
<p>Select a specific date from the drop down menus below. <br>Once you press "Submit", your browser will be redirected to a gallery of images from that day. </p>
<form class="sub" action="./archive.php" method="post">
  Select a date:
  <select name="day">
    <option value="01">01</option>
    <option value="02">02</option>
    <option value="03">03</option>
    <option value="04">04</option>
    <option value="05">05</option>
    <option value="06">06</option>
    <option value="07">07</option>
    <option value="08">08</option>
    <option value="09">09</option>
    <option value="10">10</option>
    <option value="11">11</option>
    <option value="12">12</option>
    <option value="13">13</option>
    <option value="14">14</option>
    <option value="15">15</option>
    <option value="16">16</option>
    <option value="17">17</option>
    <option value="18">18</option>
    <option value="19">19</option>
    <option value="20">20</option>
    <option value="21">21</option>
    <option value="22">22</option>
    <option value="23">23</option>
    <option value="24">24</option>
    <option value="25">25</option>
    <option value="26">26</option>
    <option value="27">27</option>
    <option value="28">28</option>
    <option value="29">29</option>
    <option value="30">30</option>
    <option value="31">31</option>
  </select>
  <select name="month">
    <option value="01">January</option>
    <option value="02">February</option>
    <option value="03">March</option>
    <option value="04">April</option>
    <option value="05">May</option>
    <option value="06">June</option>
    <option value="07">July</option>
    <option value="08">August</option>
    <option value="09">September</option>
    <option value="10">October</option>
    <option value="11">November</option>
    <option value="12">December</option>
  </select>
  <select name="year">
    <option value="2019">2019</option>
  </select>
  <input type="submit">
</form>
<?php
  $date = `date`;
  echo "The current date is ", $date;
?>
</div>

<div>
<h2>Weight</h2>
<p>The current weight of items inside the SPDS is:<p>
</div>

<div>
  <h2>Location Check</h2>
  <p>This image is taken whenever the archive of pictures is updated. It is not triggered by the motion sensor.<br>To view activity caught by the motion sensor, use the "Archive" section above.<br>To update the archive, as well as the image below will be updated every 10 minutes.</p>
  <img src="archive/live.jpg" width="1280" height="720" class="center">
</div>

<a href="./Advanced.php">Advanced Feature Controls</a>
</body>
