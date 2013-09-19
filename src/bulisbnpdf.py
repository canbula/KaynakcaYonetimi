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

import sys
from pyPdf import PdfFileWriter, PdfFileReader
import subprocess
import re
import os

def PDFtara(srcfile):
	if srcfile.lower()[-3:] == "pdf":
		srcinput = PdfFileReader(file(srcfile, "rb"))
		if srcinput.getDocumentInfo().author:
			authors = srcinput.getDocumentInfo().author.split(',')
			author = max(authors[0].split(), key=len)
			titlewords = srcinput.getDocumentInfo().title
			title1 = max(titlewords.split(), key=len)
			title2 = max(titlewords.replace(title1,'').split(), key=len)
			titlewords.replace(title2,'')
			title3 = max(titlewords.replace(title2,'').replace(title1,'').split(), key=len)
			command = "pdf2txt -p 1 "+srcfile
			process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=None, shell=True)
			output = process.communicate()
			m = re.search(r'((\d{9}|\d{12})[\d|X])\b', output[0])
			if m:
				print 'isbn:'+m.group()
			else:
				print 'meta:'+author.lower() + ';' + title1.lower() + ' ' + title2.lower() + ' ' + title3.lower()
		else:
			command = "pdf2txt -p 1 "+srcfile
			process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=None, shell=True)
			output = process.communicate()
			m = re.search(r'((\d{9}|\d{12})[\d|X])\b', output[0])
			if m:
				print 'isbn:'+m.group()
			else:
				contentlines = output[0].split('\n')
				rawcontents = 'raw:'
				for i in range(0,min(20,len(contentlines)),1):
					if contentlines[i] != "":
  						rawcontents = rawcontents+contentlines[i].replace(':',' ')+';'
  				print rawcontents
	
def main():
	PDFtara(sys.argv[1])
	return 0

if __name__ == '__main__':
	main()

