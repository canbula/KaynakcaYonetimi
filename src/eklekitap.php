#!/usr/bin/php
<?php
$isbn=$argv[1];
$apirequest = "http://isbndb.com/api/books.xml?access_key=QHS9SJ4R&results=subjects&index1=isbn&value1=".$isbn;
$apiresponse = @simplexml_load_file($apirequest) or die();
$book["isbn"] = $apiresponse->BookList[0]->BookData[0]['isbn'];
if($book["isbn"] == "") {
	$apirequest = "http://isbndb.com/api/books.xml?access_key=QHS9SJ4R&results=subjects&index1=combined&value1=".$isbn;
	$apiresponse = @simplexml_load_file($apirequest) or die();
	$book["isbn"] = $apiresponse->BookList[0]->BookData[0]['isbn'];
}
$title = $apiresponse->BookList[0]->BookData[0]->Title;
$titlelong = $apiresponse->BookList[0]->BookData[0]->TitleLong;
$book["title"] = ($titlelong=="") ? ucwords(strtolower($title)) : ucwords(strtolower($titlelong));
$book["authors"] = $apiresponse->BookList[0]->BookData[0]->AuthorsText;
$book["publisher"] = $apiresponse->BookList[0]->BookData[0]->PublisherText;
$subjects = $apiresponse->BookList[0]->BookData[0]->Subjects;
$book["subject"] = "";
foreach ($subjects->Subject as $subjects) {
	$book["subject"] = $book["subject"].$subjects.", ";
}
if(substr(trim($book["authors"]),-1)==",") {
	$book["authors"] = substr(trim($book["authors"]),0,-1);
}

$authors = explode(",", $book["authors"]);
$authornames  = explode(' ',$authors[0]);
$refidlength = 0;
$book["refid"] = "";
foreach ($authornames as $name) {
	if (strlen($name) > $refidlength) {
		$refidlength = strlen($name);
		$book["refid"] = strtolower($name);
	}
}
$book["refid"] = preg_replace("/[^A-Za-z0-9 ]/", '', $book["refid"]).strtolower(str_replace(" ","",$book["title"]));

if(substr(trim($book["subject"]),-1)==",") {
	$book["subject"] = substr(trim($book["subject"]),0,-1);
}

$jsonurl1 = "https://ajax.googleapis.com/ajax/services/search/images?v=1.0&q=".$book["isbn"];
$titlesearch = str_replace(" ","+",$book["title"]);
$jsonurl2 = "https://ajax.googleapis.com/ajax/services/search/images?v=1.0&q=".$titlesearch;
$googleresult1 = json_decode(file_get_contents($jsonurl1), true);
$googleresult2 = json_decode(file_get_contents($jsonurl2), true);
$book["cover"][1] = $googleresult1['responseData']['results'][0]['tbUrl'];
$book["cover"][2] = $googleresult1['responseData']['results'][1]['tbUrl'];
$book["cover"][3] = $googleresult1['responseData']['results'][2]['tbUrl'];
$book["cover"][4] = $googleresult2['responseData']['results'][0]['tbUrl'];
$book["cover"][5] = $googleresult2['responseData']['results'][1]['tbUrl'];
$book["cover"][6] = $googleresult2['responseData']['results'][2]['tbUrl'];

for($i=1;$i<=6;$i++) {
	file_put_contents("resource/bookcovers/".$book["isbn"].".".$i.".jpeg",file_get_contents($book["cover"][$i]));
}

$db = new SQLite3('db/Kaynakca.db');
$stmt = $db->prepare('INSERT OR REPLACE INTO book_retrieve VALUES (?,?,?,?,?,?,?,?,?,?,?,?)');
$stmt->bindValue(1,$book["isbn"],SQLITE3_TEXT);
$stmt->bindValue(2,$book["title"],SQLITE3_TEXT);
$stmt->bindValue(3,$book["authors"],SQLITE3_TEXT);
$stmt->bindValue(4,$book["publisher"],SQLITE3_TEXT);
$stmt->bindValue(5,$book["subject"],SQLITE3_TEXT);
$stmt->bindValue(6,$book["cover"][1],SQLITE3_TEXT);
$stmt->bindValue(7,$book["cover"][2],SQLITE3_TEXT);
$stmt->bindValue(8,$book["cover"][3],SQLITE3_TEXT);
$stmt->bindValue(9,$book["cover"][4],SQLITE3_TEXT);
$stmt->bindValue(10,$book["cover"][5],SQLITE3_TEXT);
$stmt->bindValue(11,$book["cover"][6],SQLITE3_TEXT);
$stmt->bindValue(12,$book["refid"],SQLITE3_TEXT);
$stmt->execute();

?>
