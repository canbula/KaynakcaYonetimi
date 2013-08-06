#!/usr/bin/env python
# -*- coding: utf-8 -*-
#  

import mechanize
import sys
import sqlite3 as lite
import hashlib
from tidylib import tidy_document

def DOIfind(srcauthor,srctitle):
	br = mechanize.Browser()
	br.open("http://www.crossref.org/guestquery/")
	br.select_form(name="form2")
	br["auth2"] = srcauthor
	br["atitle2"] = srctitle
	#br["multi_hit"] = ["false"]
	response = br.submit()
	content = response.get_data()
	br.close()
	content = content.split('<!-- ======================================================================== -->')
	lines = content[2].splitlines()
	content = lines[len(lines)-4]
	contents = content.split('<table cellspacing=1 cellpadding=1 width=600 border=0>')
	contents = contents[1].split('</table>')
	content = '<html><body><table cellspacing=1 cellpadding=1 width=600 border=0>' + contents[0] + '</table></body></html>'
	content, errors = tidy_document(content,options={'numeric-entities':1,'output-xhtml':0})
	doinumbers = ''
	doicontent = content.split('dx.doi.org/')
	for i in range(2,len(doicontent),2):
		doinumber = doicontent[i].split('</a>')
		doinumber = doinumber[0]
		if i == 2:
			doinumbers = doinumber
		else:
			doinumbers = doinumbers + ';' + doinumber
	authortitle = srcauthor + srctitle
	authortitle = hashlib.md5(authortitle).hexdigest()
	con = None
	con = lite.connect('db/Kaynakca.db')
	with con:
		cur = con.cursor()
		cur.execute("INSERT OR REPLACE INTO finddoi VALUES (?,?,?);",(authortitle,content,doinumbers))
	con.close()
def main():
	DOIfind(sys.argv[1],sys.argv[2])
	return 0

if __name__ == '__main__':
	main()

