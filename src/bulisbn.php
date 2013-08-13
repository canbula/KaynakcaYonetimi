#!/usr/bin/php
<?php
$srcauthor = $argv[1];
$srctitle = $argv[2];
$booktosearch = $srctitle." by ".$srcauthor;
$booktosearch = str_replace(" ","+",$booktosearch);
$apirequest = "http://isbndb.com/api/books.xml?access_key=QHS9SJ4R&results=subjects&index1=combined&value1=".$booktosearch;
$apiresponse = @simplexml_load_file($apirequest) or die();

$i = 0;
$dbcontents = "<html><body><table>";
$dbcontents .= "<tr><th><b>ISBN</b></th><th><b>Kitap Adı / Yazar / Yayıncı</b></th></tr>";
$dbauthortitle = md5($srcauthor.$srctitle);
$dbisbn = "";
$bgcolor[0] = "#dcdcdc";
$bgcolor[1] = "#ededed";
foreach($apiresponse->BookList->BookData as $books) {
	$book["isbn"] = $books["isbn"];
	$title = $books->Title;
	$titlelong = $books->TitleLong;
	$book["title"] = ($titlelong=="") ? ucwords(strtolower($title)) : ucwords(strtolower($titlelong));
	$book["authors"] = $books->AuthorsText;
	$book["publisher"] = $books->PublisherText;
	$subjects = $books->Subjects;
	$book["subject"] = "";
	foreach ($subjects->Subject as $subjects) {
		$book["subject"] = $book["subject"].$subjects.", ";
	}
	if(substr(trim($book["authors"]),-1)==",") {
		$book["authors"] = substr(trim($book["authors"]),0,-1);
	}
	if(substr(trim($book["subject"]),-1)==",") {
		$book["subject"] = substr(trim($book["subject"]),0,-1);
	}
	if($i==0) {
		$dbisbn = $book["isbn"];
	}
	else {
		$dbisbn .= ";".$book["isbn"];
	}
	$k = $i%2;
	$dbcontents .= "<tr>";
	$dbcontents .= "<td rowspan=\"3\" valign=\"top\" bgcolor=\"".$bgcolor[$k]."\">".$book["isbn"]."</td>";
	$dbcontents .= "<td valign=\"top\" bgcolor=\"".$bgcolor[$k]."\">".$book["title"]."</td>";
	$dbcontents .= "</tr>";
	$dbcontents .= "<tr>";
	$dbcontents .= "<td valign=\"top\" bgcolor=\"".$bgcolor[$k]."\">".$book["authors"]."</td>";
	$dbcontents .= "</tr>";
	$dbcontents .= "<tr>";
	$dbcontents .= "<td valign=\"top\" bgcolor=\"".$bgcolor[$k]."\">".$book["publisher"]."</td>";
	$dbcontents .= "</tr>";
	$i++;
}

$dbcontents .= "</table></body></html>";

$db = new SQLite3('db/Kaynakca.db');
$db->exec("INSERT OR REPLACE INTO findisbn VALUES ('".$dbauthortitle."','".$dbcontents."','".$dbisbn."')");

?>
