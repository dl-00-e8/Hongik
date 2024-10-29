CREATE TABLE client(
    cid varchar(20) NOT NULL,
    cname varchar(10) NOT NULL,
    age int,
    grade varchar(10) NOT NULL,
    job varchar(20),
    savings int,
    PRIMARY KEY (cid)
)