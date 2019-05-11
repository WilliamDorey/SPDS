<!DOCTYPE html>

<title>Secure Parcel Deposit Station</title>
<head>
<link href="./resources/colours.css" rel="stylesheet" type="text/css">

<style>
div.gallery {
 border: 1px solid #ccc;
}

div.gallery:hover {
 border: 1px solid #777;
}

div.gallery img {
 width: 100%;
 height: auto;
}

div.desc {
 padding: 15px;
 text-align: center;
}

* {
 box-sizing: border-box;
}

.responsive {
 padding: 0 6px;
 float: left;
 width: 600px;
}

@media only screen and (max-width: 700px) {
 .responsive {
   width: 49.99999%;
   margin: 6px 0;
 }
}

@media only screen and (max-width: 500px) {
 .responsive {
  width: 100%;
 }
}
</style>

</head>

<h1>Archive</h1>
<div>
 <h2>
 <?php
  $day   = htmlspecialchars($_POST["day"]);
  $month = htmlspecialchars($_POST["month"]);
  $year  = htmlspecialchars($_POST["year"]);
  $date  = `echo $day"-"$month"-"$year`;
  echo "Activity from ", $date,":";
 ?>
 </h2>
 <body>

 <?php
  $filepath = `echo -n "./archive/"$date"/"`;
  $files = scandir($filepath);
  foreach($files as $file) {
   if($file !== "." && $file !== "..") {
    echo '<div class="responsive">';
    echo '<div class="gallery>';
    echo '<a target="_blank" href="',$filepath,'/',$file,'">';
    echo '<img src="',$filepath,'/',$file,'" alt="',$file,'" width="600" height="400" >';
    echo '</a>';
    echo '<div class="desc">',$file,'</div>';
    echo '</div>';
    echo '</div>';
   }
  }
 ?>
 </body>
</div>
