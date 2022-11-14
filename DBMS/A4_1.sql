
-- creating tables for the database
create table Borrower(
    RollNo int,
    Name VARCHAR(20),
    DOI DATE,
    BookName VARCHAR(40),
    Status VARCHAR(1)
);

create table Fine (RollNo INT, Dated DATE, Amount INT);

delimiter // 
-- creating the procedure for returning the book 
create procedure return_Book(IN roll_no INT, IN name_of_book VARCHAR(20))

BEGIN 
declare date_of_issue DATE;
declare fineAmt int default -1;
declare days int;
declare act_rollNo int;
declare pre_status VARCHAR(1);
-- custom exception with sql state 43250 
declare exit handler for SQLSTATE '43250' 
begin
select "Book was previously returned, inconsistent data found" as Exception;
end;

-- custom exception with sql state 43251
declare exit handler for SQLSTATE '43251'
begin 
select "This roll number did not issue the book which they are trying to return" as Exception;
end;

-- default exception
declare exit handler for not found 
begin
select "Book with the given name not found" as Exception;
end;

select DOI into date_of_issue from Borrower where BookName = name_of_book;
select RollNo into act_rollNo from Borrower where BookName = name_of_book;
select Status into pre_status from Borrower where BookName = name_of_book;

IF(pre_status = "R") THEN SIGNAL SQLSTATE '43250';
END IF;

IF(roll_no != act_rollNo) THEN SIGNAL SQLSTATE '43251';
END IF;
-- calculating the number of days between date of issue and current date
set days = DATEDIFF(CURDATE(), date_of_issue);

IF (days > 15 and days < 30) THEN
set fineAmt = days * 5;
ELSEIF (days > 30) THEN
set fineAmt = (days -30) * 50 + 150;
END IF;

IF(fineAmt != -1) THEN 
insert into Fine values (roll_no, CURDATE(), fineAmt);
update Borrower set Status = "R" where RollNo = roll_no;
select fineAmt as "Fine to be paid";

ELSE
update Borrower set Status = "R" where RollNo = roll_no;
select "No fine to be paid! :)" as "Message";
END IF;
END;
// 
delimiter;