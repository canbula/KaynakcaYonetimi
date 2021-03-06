#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#    This file is part of KaynakcaYonetimi.
#
#    KaynakcaYonetimi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    KaynakcaYonetimi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with KaynakcaYonetimi.  If not, see <http://www.gnu.org/licenses/>.
#

import mechanize
from xml.dom.minidom import parseString
import sys
import sqlite3 as lite
import re
import os

TAGS = re.compile(r'<[^>]+>')

def removetags(text):
	return TAGS.sub('',text)

def DOIsearch(DOInumber):
	br = mechanize.Browser()
	br.open("http://www.crossref.org/guestquery/")
	br.select_form(name="form5")
	br["doi"] = DOInumber
	br["restype"] = ["unixref"]
	response = br.submit()
	content = response.get_data()
	br.close()
	contents = content.split('<doi_records>')
	if len(contents) > 1:
		contents = contents[1].split('</doi_records>')
		dom = parseString(contents[0])
		doi = removetags(dom.getElementsByTagName('doi')[0].toxml())
		title = removetags(dom.getElementsByTagName('title')[0].toxml())
		for i in range(len(dom.getElementsByTagName('given_name'))):
			givenname = removetags(dom.getElementsByTagName('given_name')[i].toxml())
			givenname = givenname.replace(". ", ".")
			surname = removetags(dom.getElementsByTagName('surname')[i].toxml())
			if i > 0:
				authors = authors + ', ' + givenname + ' ' + surname
			else:
				authors = givenname + ' ' + surname
				refid = surname.lower()
		if len(dom.getElementsByTagName('conference')) > 0:
			if len(dom.getElementsByTagName('proceedings_title')) > 0:
				journal = removetags(dom.getElementsByTagName('proceedings_title')[0].toxml())
			else:
				journal = removetags(dom.getElementsByTagName('title')[0].toxml())
				title = removetags(dom.getElementsByTagName('title')[1].toxml())
		else:
			journal = removetags(dom.getElementsByTagName('full_title')[0].toxml())
		if len(dom.getElementsByTagName('volume')) > 0:
			volume = removetags(dom.getElementsByTagName('volume')[0].toxml())
		else:
			volume = ''
		if len(dom.getElementsByTagName('issue')) > 0:
			issue = removetags(dom.getElementsByTagName('issue')[0].toxml())
		else:
			issue = ''
		if len(dom.getElementsByTagName('item_number')) > 0:
			itemnumber = removetags(dom.getElementsByTagName('item_number')[0].toxml())
		else:
			itemnumber = ''
		if len(dom.getElementsByTagName('first_page')) > 0:
			firstpage = removetags(dom.getElementsByTagName('first_page')[0].toxml())
		else:
			firstpage = ''
		if len(dom.getElementsByTagName('last_page')) > 0:
			lastpage = removetags(dom.getElementsByTagName('last_page')[0].toxml())
		else:
			lastpage = ''
		if firstpage == '':
			firstpage = itemnumber
		if len(dom.getElementsByTagName('month')) > 0:
			month = removetags(dom.getElementsByTagName('month')[0].toxml())
			month = month.zfill(2)
		else:
			month = '00'
		if len(dom.getElementsByTagName('year')) > 0:
			year = removetags(dom.getElementsByTagName('year')[0].toxml())
		else:
			year = ''
		published = year + "/" + month
		refid = refid + year
		if len(dom.getElementsByTagName('resource')) > 0:
			link = removetags(dom.getElementsByTagName('resource')[0].toxml())
		else:
			link = ''
		subject = ''
		title = title[0].upper() + title[1:].lower()
		dbpath = os.path.dirname(os.path.abspath(__file__))+"/../db/Kaynakca.db"
		con = None
		con = lite.connect(dbpath)
		with con:
			cur = con.cursor()
			cur.execute("INSERT OR REPLACE INTO paper_retrieve VALUES (?,?,?,?,?,?,?,?,?,?,?,?);",(doi,title,authors,journal,volume,issue,firstpage,lastpage,published,link,subject,refid))
		con.close()
def main():
	DOIsearch(sys.argv[1])
	return 0

if __name__ == '__main__':
	main()

