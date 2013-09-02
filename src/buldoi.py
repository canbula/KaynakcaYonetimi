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
import sys
import sqlite3 as lite
import hashlib
from tidylib import tidy_document
from BeautifulSoup import BeautifulSoup
import re

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
	soup = BeautifulSoup(content)
	text_parts = soup.findAll(text=True)
	content = ''.join(text_parts)
	newcontent = content.split('&#160;')
	authortitle = srcauthor + srctitle
	authortitle = hashlib.md5(authortitle).hexdigest()
	con = None
	con = lite.connect('db/Kaynakca.db')
	renewquery = "DELETE FROM finddoi WHERE authortitle = '%s';" % authortitle.strip()
	con.execute(renewquery)
	for content in newcontent:
		if "dx.doi.org" in content:
			doi = re.search(r'\b(10[.][0-9]{4,}(?:[.][0-9]+)*/(?:(?!["&\'<>])\S)+)\b',content)
			s = ' '.join(content.split())
			output = re.split('http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+',s)
			with con:
				cur = con.cursor()
				cur.execute("INSERT INTO finddoi VALUES (?,?,?,?);",(authortitle,doi.group(),output[0].strip(),output[1].strip()))
	con.close()
def main():
	DOIfind(sys.argv[1],sys.argv[2])
	return 0

if __name__ == '__main__':
	main()

