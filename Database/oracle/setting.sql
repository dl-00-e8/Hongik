CREATE TABLE Boats(
    bid int not null,
    name varchar(10) not null,
    color varchar(10) not null,
    PRIMARY KEY (bid)
)

CREATE TABLE Reserve(
    rid int not null,
    bid int not null,
    PRIMARY KEY (rid)
)

INSERT INTO Boats (bid, name, color) VALUES 
(1, 'hi', 'red');

INSERT INTO Boats (bid, name, color) VALUES 
(2, 'bye', 'red');

INSERT INTO Boats (bid, name, color) VALUES 
(3, 'hi', 'green');

INSERT INTO Boats (bid, name, color) VALUES 
(4, 'test', 'green');

INSERT INTO Reserve (rid, bid) VALUES
(1, 1);

INSERT INTO Reserve (rid, bid) VALUES
(2, 1);

INSERT INTO Reserve (rid, bid) VALUES
(3, 2);

INSERT INTO Reserve (rid, bid) VALUES
(4, 3);

INSERT INTO Reserve (rid, bid) VALUES
(5, 4);

INSERT INTO Reserve (rid, bid) VALUES
(6, 4);

