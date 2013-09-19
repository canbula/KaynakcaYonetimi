#!/usr/bin/php
<?php
/*
    This file is part of KaynakcaYonetimi.

    KaynakcaYonetimi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    KaynakcaYonetimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with KaynakcaYonetimi.  If not, see <http://www.gnu.org/licenses/>.
*/
$srcauthor = $argv[1];
$srctitle = $argv[2];
$booktosearch = $srctitle." by ".$srcauthor;
$booktosearch = str_replace(" ","+",$booktosearch);
$apirequest = "http://isbndb.com/api/books.xml?access_key=QHS9SJ4R&results=subjects&index1=combined&value1=".$booktosearch;
$apiresponse = @simplexml_load_file($apirequest) or die();

$dbpath = dirname(__FILE__)."/../db/Kaynakca.db";
$db = new SQLite3($dbpath);
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
