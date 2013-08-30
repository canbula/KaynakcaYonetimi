#!/usr/bin/php
<?php
$srcauthor = $argv[1];
$srctitle = $argv[2];
$booktosearch = $srctitle." by ".$srcauthor;
$booktosearch = str_replace(" ","+",$booktosearch);
$apirequest = "http://isbndb.com/api/books.xml?access_key=QHS9SJ4R&results=subjects&index1=combined&value1=".$booktosearch;
$apiresponse = @simplexml_load_file($apirequest) or die();

$db = new SQLite3('db/Kaynakca.db');
$dbauthortitle = md5($srcauthor.$srctitle);
foreach($apiresponse->BookList->BookData as $books) {
	$book["isbn"] = $books["isbn"];
	$title = $books->Title;
	$titlelong = $books->TitleLong;
	$book["title"] = ($titlelong=="") ? ucwords(strtolower($title)) : ucwords(strtolower($titlelong));
	$book["authors"] = $books->AuthorsText;
	$book["publisher"] = $books->PublisherText;
	if(substr(trim($book["authors"]),-1)==",") {
		$book["authors"] = substr(trim($book["authors"]),0,-1);
	}
	$stmt = $db->prepare('INSERT OR REPLACE INTO findisbn VALUES (?,?,?,?,?)');
	$stmt->bindValue(1,$dbauthortitle,SQLITE3_TEXT);
	$stmt->bindValue(2,$book["isbn"],SQLITE3_TEXT);
	$stmt->bindValue(3,$book["authors"],SQLITE3_TEXT);
	$stmt->bindValue(4,$book["publisher"],SQLITE3_TEXT);
	$stmt->bindValue(5,$book["title"],SQLITE3_TEXT);
	$stmt->execute();
}

?>
