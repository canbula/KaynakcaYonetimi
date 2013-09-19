CREATE TABLE "book_retrieve" (
    "isbn" TEXT NOT NULL,
    "title" TEXT,
    "authors" TEXT,
    "publisher" TEXT,
    "subject" TEXT,
    "cover1" TEXT,
    "cover2" TEXT,
    "cover3" TEXT,
    "cover4" TEXT,
    "cover5" TEXT,
    "cover6" TEXT,
    "refid" TEXT
);
CREATE TABLE "books" (
    "isbn" TEXT NOT NULL,
    "title" TEXT,
    "authors" TEXT,
    "publisher" TEXT,
    "subject" TEXT,
    "refid" TEXT,
    "star" TEXT,
    "color" TEXT
);
CREATE TABLE "documents" (
    "id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE,
    "name" TEXT,
    "desc" TEXT,
    "star" TEXT
);
CREATE TABLE "files" (
    "id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE,
    "name" TEXT,
    "desc" TEXT,
    "star" TEXT
);
CREATE TABLE "finddoi" (
    "authortitle" TEXT NOT NULL,
    "doi" TEXT,
    "ref" TEXT,
    "title" TEXT
);
CREATE TABLE "findisbn" (
    "authortitle" TEXT NOT NULL,
    "isbn" TEXT,
    "authors" TEXT,
    "publisher" TEXT,
    "title" TEXT
);
CREATE TABLE "listrefs" (
    "listid" INTEGER,
    "number" TEXT,
    "type" TEXT,
    "isbndoi" TEXT
);
CREATE TABLE "lists" (
    "id" Integer Primary Key Autoincrement  NOT NULL,
    "name" TEXT,
    "desc" TEXT,
    "style" TEXT
);
CREATE TABLE "paper_retrieve" (
    "doi" TEXT NOT NULL,
    "title" TEXT,
    "authors" TEXT,
    "journal" TEXT,
    "volume" TEXT,
    "issue" TEXT,
    "firstpage" TEXT,
    "lastpage" TEXT,
    "published" TEXT,
    "link" TEXT,
    "subject" TEXT,
    "refid" TEXT
);
CREATE TABLE "papers" (
    "doi" TEXT NOT NULL,
    "title" TEXT,
    "authors" TEXT,
    "journal" TEXT,
    "volume" TEXT,
    "issue" TEXT,
    "firstpage" TEXT,
    "lastpage" TEXT,
    "published" TEXT,
    "link" TEXT,
    "subject" TEXT,
    "refid" TEXT,
    "star" TEXT,
    "color" TEXT
);
CREATE TABLE "todos" (
    "id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE,
    "date" TEXT,
    "title" TEXT,
    "details" TEXT
);
CREATE UNIQUE INDEX "bookisbn" ON "books" ("isbn" ASC);
CREATE UNIQUE INDEX "doi" on "paper_retrieve" ("doi" ASC);
CREATE UNIQUE INDEX "isbn" ON "book_retrieve" ("isbn" ASC);
CREATE UNIQUE INDEX "paperdoi" ON "papers" ("doi" ASC);
