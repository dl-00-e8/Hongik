CREATE TABLE Artists
	(name varchar(20) NOT NULL,
	birthplace varchar(100),
	age int,
	art_style varchar(100),
	PRIMARY KEY (name))
	
CREATE TABLE Works
	(title varchar(20) NOT NULL,
	artist_name varchar(20) NOT NULL,
	made_at date,
	price int NOT NULL,
	PRIMARY KEY (title),
	FOREIGN KEY (artist_name)
		REFERENCES Artists(name))
	
CREATE Table Work_type
	(type_name varchar(20) NOT NULL,
	PRIMARY KEY (type_name))

CREATE Table Work_ref
	(title varchar(20) NOT NULL,
	type_name varchar(20) NOT NULL,
	PRIMARY KEY (title, type_name),
	FOREIGN KEY (title)
		REFERENCES Works(title),
	FOREIGN KEY (type_name)
		REFERENCES Work_type(type_name))
		
CREATE Table Customers
	(name varchar(20) NOT NULL,
	address varchar(255),
	total_spent_amount int,
	PRIMARY KEY (name))
	
CREATE Table Customer_artist_ref
	(customer_name varchar(20) NOT NULL,
	artist_name varchar(20) NOT NULL,
	PRIMARY KEY (customer_name, artist_name),
	FOREIGN KEY (customer_name)
		REFERENCES Customers(name),
	FOREIGN KEY (artist_name)
		REFERENCES Artists(name))
		
CREATE Table Customer_type_ref
	(cusotomer_name varchar(20) NOT NULL,
	type_name varchar(20) NOT NULL,
	PRIMARY KEY (customer_name, type_name),
	FOREIGN KEY (customer_name)
		REFERENCES Customers(name),
	FOREIGN KEY (type_name)
		REFERENCES Work_type(type_name))

INSERT INTO "public"."artists" ("name", "birthplace", "age", "art_style") VALUES
('지코', '강원도', 33, '힙함'),
('아이유', '경기도', 30, '감각적임'),
('지드래곤', '서울특별시', 35, '트렌디함');

INSERT INTO "public"."customer_artist_ref" ("customer_name", "artist_name") VALUES
('HWANG', '아이유'),
('HWANG', '지드래곤'),
('LEE', '지코'),
('LEE', '아이유'),
('YANG', '지코'),
('YANG', '아이유');

INSERT INTO "public"."customers" ("name", "address", "total_spent_amount") VALUES
('HWANG', '경기도', 5000000),
('KIM', '충청남도', 35000),
('LEE', '서울특별시', 21800000),
('NAM', '부산광역시', 7000000),
('YANG', '인천광역시', 1800000);

INSERT INTO "public"."work_ref" ("title", "type_name") VALUES
('잔소리', '초상화'),
('삐딱하게', '초상화'),
('삐딱하게', '19세기'),
('좋은 날', '피카소'),
('터프 쿠키', '정물화'),
('터프 쿠키', '초상화'),
('터프 쿠키', '피카소'),
('Good Boy', '초상화'),
('Good Boy', '피카소'),
('그XX', '정물화');

INSERT INTO "public"."work_type" ("type_name") VALUES
('정물화'),
('초상화'),
('피카소'),
('19세기');

INSERT INTO "public"."works" ("title", "artist_name", "made_at", "price") VALUES
('잔소리', '아이유', '2012-01-01', 10028402),
('삐딱하게', '지드래곤', '2015-02-01', 300000),
('좋은 날', '아이유', '2010-01-01', 1000000),
('터프 쿠키', '지코', '2015-01-01', 200830),
('Good Boy', '지드래곤', '2020-12-21', 40000000),
('그XX', '지드래곤', '2019-08-21', 5000000);