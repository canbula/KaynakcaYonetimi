#!/usr/bin/env python
# -*- coding: utf-8 -*-
#  

import mechanize
from xml.dom.minidom import parseString
import sys
import sqlite3 as lite
import re

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
			givenname = givenname.replace(" ", "")
			surname = removetags(dom.getElementsByTagName('surname')[i].toxml())
			if i > 0:
				authors = authors + ', ' + givenname + ' ' + surname
			else:
				authors = givenname + ' ' + surname
		if len(dom.getElementsByTagName('conference')) > 0:
			if len(dom.getElementsByTagName('proceedings_title')) > 0:
				journal = removetags(dom.getElementsByTagName('proceedings_title')[0].toxml())
			else:
				journal = removetags(dom.getElementsByTagName('title')[0].toxml())
				title = removetags(dom.getElementsByTagName('title')[1].toxml())
			volume = ''
			issue = ''
			itemnumber = ''
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
		if len(dom.getElementsByTagName('resource')) > 0:
			link = removetags(dom.getElementsByTagName('resource')[0].toxml())
		else:
			link = ''
		subject = ''
		title = title[0].upper() + title[1:].lower()
		con = None
		con = lite.connect('db/Kaynakca.db')
		with con:
			cur = con.cursor()
			cur.execute("INSERT OR REPLACE INTO paper_retrieve VALUES ('"+doi+"','"+title+"','"+authors+"','"+journal+"','"+volume+"','"+issue+"','"+firstpage+"','"+lastpage+"','"+published+"','"+link+"','"+subject+"');")
		con.close()
def main():
	DOIsearch(sys.argv[1])
	return 0

if __name__ == '__main__':
	main()

