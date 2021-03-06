<?php
	/********************************************************************
	 * Photo Album v1.0
	 * Written by: Robbie Hott
	 * http://www.robbiehott.com
	 * (c) 2005
	 *
	 * This code may be shared and updated for free, as long as you do not
	 * claim it as your own and leave this comment in tact.
	 *
	 * DO NOT EDIT THIS FILE
	 ********************************************************************/

function getDirectories($dir) {
	// Open a known directory, and proceed to read its contents
	// Returns only directories
	$files = array();
	if (is_dir($dir)) {
	   if ($dh = opendir($dir)) {
	       while (($file = readdir($dh)) !== false) {
	           if ($file != '..' && $file != '.' && is_dir($dir . "/" . $file)) {
			array_push($files, $file);
		   }
	       }
	       closedir($dh);
	   }
	}
	return $files;
}

function getImages($dir) {
	// Open a known directory, and proceed to read its contents
	$files = array();
	if (is_dir($dir)) {
	   if ($dh = opendir($dir)) {
	       while (($file = readdir($dh)) !== false) {
	           if ($file != '..' && $file != '.')
			array_push($files, $file);
	       }
	       closedir($dh);
	   }
	}
	return $files;
}

function getFirstImage($dir) {
	// Open a known directory, and proceed to read its contents
	if (is_dir($dir)) {
	   if ($dh = opendir($dir)) {
	       while (($file = readdir($dh)) !== false) {
	           if ($file != '..' && $file != '.') {
			closedir($dh);
			return $file;
		   }
	       }
	       closedir($dh);
	   }
	}
	return "";
}

function randomImage($dir) {
	// Open a known directory, and proceed to read its contents
	$files = array();
	if (is_dir($dir)) {
	   if ($dh = opendir($dir)) {
	       while (($file = readdir($dh)) !== false) {
	           if ($file != '..' && $file != '.')
			array_push($files, $file);
	       }
	       closedir($dh);
	   }
	   return $dir.$files[array_rand($files)];
	}
	return "";
}

	
function print_album_list($location) {
	$albumlist = getDirectories($location);
	foreach($albumlist as $albumentry) {
			echo "<a href=\"?album=$albumentry\">$albumentry</a><br/>";
	}
}

function print_albums($location, $max) {
	$albumlist = getDirectories($location);
	$i = 0;

	echo "<center><table class=\"phototable\">";
		
	foreach ($albumlist as $albumentry) {
		if ($max != -1 && $max-- <= 0)
			break;
		$image = getFirstImage($location . "/" . $albumentry);
		if ($i == 0)
			echo "<tr>";
				
		echo "<td align=\"center\"><p>
			<a href=\"?album=$albumentry\">
			
			<img src=\"image.php?i=$location/$albumentry/$image&type=thumbnail\"
				border=\"0\" alt=\"$albumentry\"><br/>
			$albumentry</a></p><br/>
			
			     </td>";
		$i = ($i + 1) % 4;

		if ($i == 0)
			echo "</tr>";
	}

	if ($i != 0)
		echo "</tr>";
	echo "</table></center>";

	
}

function print_album_contents($location, $album) {
	// read in array and process album
	$imlist = getImages($location."/".$album);
	$i = 0;

	echo "<center><table class=\"phototable\">";
	foreach ($imlist as $image) {
		$imagettl = explode(".", $image);
		$imagename = $imagettl[0];
		if ($i == 0)
			echo "<tr>";
			
		echo "<td align=\"center\"><p>
			<a href=\"$PHP_ROOT?album=$album&image=$image\">
			<img src=\"image.php?i=$location/$album/$image&type=thumbnail\"
				border=\"0\" alt=\"$imagename\"><br/>
			$imagename</a></p><br/>
			
		      </td>";
		$i = ($i + 1) % 4;
		if ($i == 0)
			echo "</tr>";
	}

	if ($i != 0)
		echo "</tr>";
	echo "</table></center>";
}


		
?>


